/*
 * File:   TemplateEventChecker.c
 * Author: Gabriel Hugh Elkaim
 *
 * Template file to set up typical EventCheckers for the  Events and Services
 * Framework (ES_Framework) on the Uno32 for the CMPE-118/L class. Note that
 * this file will need to be modified to fit your exact needs, and most of the
 * names will have to be changed to match your code.
 *
 * This EventCheckers file will work with both FSM's and HSM's.
 *
 * Remember that EventCheckers should only return TRUE when an event has occured,
 * and that the event is a TRANSITION between two detectable differences. They
 * should also be atomic and run as fast as possible for good results.
 *
 * This file includes a test harness that will run the event detectors listed in the
 * ES_Configure file in the project, and will conditionally compile main if the macro
 * EVENTCHECKER_TEST is defined (either in the project or in the file). This will allow
 * you to check you event detectors in their own project, and then leave them untouched
 * for your project unless you need to alter their post functions.
 *
 * Created on September 27, 2013, 8:37 AM
 */

/*******************************************************************************
 * MODULE #INCLUDE                                                             *
 ******************************************************************************/

#include "ES_Configure.h"
#include "SensorEventChecker.h"
#include "ES_Events.h"
#include "serial.h"
#include "AD.h"
#include "BattService.h"
#include "SensorService.h"
#include "IO_Ports.h"
#include "ES_Timers.h"
/*******************************************************************************
 * MODULE #DEFINES                                                             *
 ******************************************************************************/
#define BATTERY_DISCONNECT_THRESHOLD 175
#define TRACK_VOLTAGE AD_PORTV3
#define TRACK_THRESH 200
#define TRACK_HYST 60
// for tape sensor testing will only use the frr (front right right) tape sensor
#define ONETAPE
// the tape sensors will be powered by the PIC32 this will control the pins
#define TAPE_READER_POWERPort PORTW
#define TAPE_READER_POWERPin PIN3
// the LEDs need their own pin for power we may change this later
#define TAPE_LEDfrrPort PORTW
#define TAPE_LEDfrrPin PIN4
#ifdef ONETAPE
#define TAPE_LEDfrPort
#define TAPE_LEDfrPin
#define TAPE_LEDflPort
#define TAPE_LEDflPin
#define TAPE_LEDfllPort
#define TAPE_LEDfllPin
#define TAPE_LEDbrPort
#define TAPE_LEDbrPin
#define TAPE_LEDblPort
#define TAPE_LEDblPin
#endif
#define TAPE_VOLTAGEfrr AD_PORTV4
#ifndef ONETAPE
#define TAPE_VOLTAGEfr
#define TAPE_VOLTAGEfl
#define TAPE_VOLTAGEfll
#define TAPE_VOLTAGEbr
#define TAPE_VOLTAGEbl
#endif
#define TAPE_THRESH 60 
// reading voltage
#define TAPE_HYST 15 
#define TAPEfrrBit (0)
#define TAPEfrBit (1)
#define TAPEflBit (2)
#define TAPEfllBit (3)
#define TAPEbrBit (4)
#define TAPEblBit (5)
// Time that is needed for the tape sensor to get a stable reading (in ms)
#define TAPEtime 3
/*******************************************************************************
 * EVENTCHECKER_TEST SPECIFIC CODE                                                             *
 ******************************************************************************/

#define EVENTCHECKER_TEST
#ifdef EVENTCHECKER_TEST
#include <stdio.h>
#define SaveEvent(x)          \
    do                        \
    {                         \
        eventName = __func__; \
        storedEvent = x;      \
    } while (0)

static const char *eventName;
static ES_Event storedEvent;
#endif
// #define DEBUG_PRINT
#ifdef DEBUG_PRINT
#include <stdio.h>
#endif
/*******************************************************************************
 * PRIVATE FUNCTION PROTOTYPES                                                 *
 ******************************************************************************/
/**
 * @Function SetTapeLED(state)
 * @param state true if the LEDs will be turned on 0 if off
 * @return non
 * @brief This function will turn on and off the LEDs for the tape sensor reader
 * @author Cooper Cantrell 5/11/2024 2:19PM
 */
void SetTapeLED(char state)
{
    // assume only use 1 port for all of the LEDS if not will need to change
    uint16_t pattern = 0;
    pattern |= TAPE_LEDfrrPin;
    pattern |= TAPE_READER_POWERPin;
#ifndef ONETAPE
    pattern |= TAPE_LEDfrPin;
    pattern |= TAPE_LEDflPin;
    pattern |= TAPE_LEDfllPin;
    pattern |= TAPE_LEDbrPin;
    pattern |= TAPE_LEDblPin;
#endif
    if (state)
    {
        IO_PortsWritePort(TAPE_LEDfrrPort, pattern);
    }
    else
    {
        IO_PortsWritePort(TAPE_LEDfrrPort, TAPE_READER_POWERPin);
    }
}
/*******************************************************************************
 * PRIVATE MODULE VARIABLES                                                    *
 ******************************************************************************/
enum sensor{NOT_DETECTED,DETECTED};
enum sensor LastTrack = NOT_DETECTED;
enum sensor LastTapefrr = NOT_DETECTED;
#ifndef ONETAPE
enum sensor LastTapefr = NOT_DETECTED;
enum sensor LastTapefl = NOT_DETECTED;
enum sensor LastTapefll = NOT_DETECTED;
enum sensor LastTapebr = NOT_DETECTED;
enum sensor LastTapebl = NOT_DETECTED;
#endif
static enum { OFF,
              ON } TapeLED = OFF;
uint8_t TapeWaiting = FALSE;
uint32_t TapeWaitStart;
uint8_t LEDset = FALSE;
// so the current noise for the tape can be used
uint16_t TapefrrNoise;
#ifndef ONETAPE
uint16_t TapefrNoise;
uint16_t TapeflrNoise;
uint16_t TapefllNoise;
uint16_t TapebrNoise;
uint16_t TapeblNoise;
#endif
// a var to store the reading to
uint16_t TapefrrRead;
#ifndef ONETAPE
uint16_t TapefrRead;
uint16_t TapeflrRead;
uint16_t TapefllRead;
uint16_t TapebrRead;
uint16_t TapeblRead;
#endif
/*******************************************************************************
 * PUBLIC FUNCTIONS                                                            *
 ******************************************************************************/

/**
 * @Function TemplateCheckBattery(void)
 * @param none
 * @return TRUE or FALSE
 * @brief This function is a prototype event checker that checks the battery voltage
 *        against a fixed threshold (#defined in the .c file). Note that you need to
 *        keep track of previous history, and that the actual battery voltage is checked
 *        only once at the beginning of the function. The function will post an event
 *        of either BATTERY_CONNECTED or BATTERY_DISCONNECTED if the power switch is turned
 *        on or off with the USB cord plugged into the Uno32. Returns TRUE if there was an
 *        event, FALSE otherwise.
 * @note Use this code as a template for your other event checkers, and modify as necessary.
 * @author Gabriel H Elkaim, 2013.09.27 09:18
 * @modified Gabriel H Elkaim/Max Dunne, 2016.09.12 20:08 */
uint8_t CheckBattery(void)
{
    static ES_EventTyp_t lastEvent = BATTERY_DISCONNECTED;
    ES_EventTyp_t curEvent;
    ES_Event thisEvent;
    uint8_t returnVal = FALSE;
    uint16_t batVoltage = AD_ReadADPin(BAT_VOLTAGE); // read the battery voltage

    if (batVoltage > BATTERY_DISCONNECT_THRESHOLD)
    { // is battery connected?
        curEvent = BATTERY_CONNECTED;
    }
    else
    {
        curEvent = BATTERY_DISCONNECTED;
    }
    if (curEvent != lastEvent)
    { // check for change from last time
        thisEvent.EventType = curEvent;
        thisEvent.EventParam = batVoltage;
        returnVal = TRUE;
        lastEvent = curEvent; // update history
#ifndef EVENTCHECKER_TEST     // keep this as is for test harness
        PostBattService(thisEvent);
#else
        SaveEvent(thisEvent);
#endif
    }
    return (returnVal);
}

/**
 * @Function CheckTrack(void)
 * @param none
 * @return TRUE or FALSE
 * @brief This function is the event checker that detects if the inductor is
 *      close enough to the track wire by comparing it to a #define in the .c
 * @author Cooper Cantrell 5/8/2024 3:44
 */
uint8_t CheckTrack(void)
{
    // sets up the basic vars that are needed for the I/O of this function
    uint8_t returnVal = FALSE;
    static enum { NOT_DETECTED,
                  DETECTED } CurrentTrack;
    uint16_t TrackVoltage = AD_ReadADPin(TRACK_VOLTAGE);
    // checks to see what the current value is
    if (TrackVoltage > TRACK_THRESH + TRACK_HYST)
    {
        CurrentTrack = DETECTED;
    }
    else if (TrackVoltage < TRACK_THRESH - TRACK_HYST)
    {
        CurrentTrack = NOT_DETECTED;
    }
    // checks if there is a change from current to past and acts properly
    if (CurrentTrack != LastTrack)
    {
        returnVal = TRUE;
        LastTrack = CurrentTrack;
        ES_Event ThisEvent;
        ThisEvent.EventParam = CurrentTrack;
        ThisEvent.EventType = TRACKWIRE;
#ifndef EVENTCHECKER_TEST // keep this as is for test harness
#ifdef DEBUG_PRINT
        printf("\r\n Posting a track wire event");
#endif
        PostSensorService(ThisEvent);
#else
        SaveEvent(ThisEvent);
#endif
    }

    return returnVal;
}

/**
 * @Function CheckTape(void)
 * @param none
 * @return TRUE or FALSE
 * @brief This function is the event checker that detects if there is a change
 *      in tape detetion
 * @author Cooper Cantrell 5/10/2024 12:07
 */
uint8_t CheckTape(void)
{
    // if there is no noise to compare to turn the led off so we can get a noise reading
    if (!TapefrrNoise)
    {
        TapeLED = OFF;
    }

    // event checker setup
    uint8_t returnVal = FALSE;
    uint8_t param = 0;
    static enum sensor CurrentTapefrr;
#ifndef ONETAPE
    static enum sensor CurrentTapefr;
    static enum sensor CurrentTapefl;
    static enum sensor CurrentTapefll;
    static enum sensor CurrentTapebr;
    static enum sensor CurrentTapebl;
#endif
    // the LED will be off and be given LEDTIME
    if (!TapeWaiting)
    {
        TapeWaiting = TRUE;
        TapeWaitStart = ES_Timer_GetTime();
    }
    // writes the output power so that the LEDs will turn on and off (this may be slow if we need to optimize)
    if(!LEDset){
        SetTapeLED(TapeLED);
        LEDset = TRUE;
    }
    // this checks to see if enough time has passed for the reading to be stable
    if (ES_Timer_GetTime() > TapeWaitStart + TAPEtime)
    {
        TapeWaiting = FALSE;
        LEDset = FALSE;
        if (TapeLED) // off is FALSE
        {
            TapefrrRead = AD_ReadADPin(TAPE_VOLTAGEfrr);
#ifndef ONETAPE
            TapefrRead = AD_ReadADPin(TAPE_VOLTAGEfr);
            TapeflrRead = AD_ReadADPin(TAPE_VOLTAGEfl);
            TapefllRead = AD_ReadADPin(TAPE_VOLTAGEfll);
            TapebrRead = AD_ReadADPin(TAPE_VOLTAGEfbr);
            TapeblRead = AD_ReadADPin(TAPE_VOLTAGEfbl);
#endif
        }
        else
        {
            TapefrrNoise = AD_ReadADPin(TAPE_VOLTAGEfrr);
#ifndef ONETAPE
            TapefrNoise = AD_ReadADPin(TAPE_VOLTAGEfr);
            TapeflrNoise = AD_ReadADPin(TAPE_VOLTAGEfl);
            TapefllNoise = AD_ReadADPin(TAPE_VOLTAGEfll);
            TapebrNoise = AD_ReadADPin(TAPE_VOLTAGEfbr);
            TapeblNoise = AD_ReadADPin(TAPE_VOLTAGEfbl);
#endif
        }
        TapeLED = !TapeLED;
        // after the check compare to past values and noise to the thresh and raise events
        //only if has at least 1 of each reading
        if(TapefrrNoise && TapefrrRead){
        if ((TapefrrNoise - TapefrrRead) >= TAPE_THRESH + TAPE_HYST)
        {
            CurrentTapefrr = NOT_DETECTED;
        }

        else if ((TapefrrNoise - TapefrrRead) <= TAPE_THRESH - TAPE_HYST)
        {
            CurrentTapefrr = DETECTED;
        }
#ifndef ONETAPE
        if ((TapefrNoise - TapefrRead) >= TAPE_THRESH + TAPE_HYST)
        {
            CurrentTapefr = NOT_DETECTED;
        }

        else if ((TapefrNoise - TapefrRead) <= TAPE_THRESH - TAPE_HYST)
        {
            CurrentTapefr = DETECTED;
        }
        if ((TapeflNoise - TapeflRead) >= TAPE_THRESH + TAPE_HYST)
        {
            CurrentTapefl = NOT_DETECTED;
        }

        else if ((TapeflNoise - TapeflRead) <= TAPE_THRESH - TAPE_HYST)
        {
            CurrentTapefl = DETECTED;
        }
        if ((TapefllNoise - TapefllRead) >= TAPE_THRESH + TAPE_HYST)
        {
            CurrentTapefll = NOT_DETECTED;
        }

        else if ((TapefllNoise - TapefllRead) <= TAPE_THRESH - TAPE_HYST)
        {
            CurrentTapefll = DETECTED;
        }
        if ((TapebrNoise - TapebrRead) >= TAPE_THRESH + TAPE_HYST)
        {
            CurrentTapebr = NOT_DETECTED;
        }

        else if ((TapebrNoise - TapefbrRead) <= TAPE_THRESH - TAPE_HYST)
        {
            CurrentTapebr = DETECTED;
        }
        if ((TapeblNoise - TapeblRead) >= TAPE_THRESH + TAPE_HYST)
        {
            CurrentTapebl = NOT_DETECTED;
        }

        else if ((TapeblNoise - TapeblRead) <= TAPE_THRESH - TAPE_HYST)
        {
            CurrentTapebl = DETECTED;
        }
#endif
        
        // compare past values with current values
        if (CurrentTapefrr != LastTapefrr)
        {
            returnVal = TRUE;
            param += (CurrentTapefrr << TAPEfrrBit);
            LastTapefrr = CurrentTapefrr;
        }
#ifndef ONETAPE
        if (CurrentTapefr != LastTapefr)
        {
            returnVal = TRUE;
            param += (CurrentTapefr << TAPEfrBit);
            LastTapefr = CurrentTapefr;
        }
        if (CurrentTapefl != LastTapefl)
        {
            returnVal = TRUE;
            param += (CurrentTapefl << TAPEflBit);
            LastTapefl = CurrentTapefl;
        }
        if (CurrentTapefll != LastTapefll)
        {
            returnVal = TRUE;
            param += (CurrentTapefll << TAPEfllBit);
            LastTapefll = CurrentTapefll;
        }
        if (CurrentTapebr != LastTapefbr)
        {
            returnVal = TRUE;
            param += (CurrentTapebr << TAPEbrBit);
            LastTapebr = CurrentTapebr;
        }
        if (CurrentTapebl != LastTapebl)
        {
            returnVal = TRUE;
            param += (CurrentTapebl << TAPEblBit);
            LastTapebl = CurrentTapebl;
        }
#endif
        }
    }
    if (returnVal)
    {
        ES_Event ThisEvent;
        ThisEvent.EventType = TAPE;
        ThisEvent.EventParam = param;
#ifndef EVENTCHECKER_TEST // keep this as is for test harness
            PostSensorService(ThisEvent);
#else
            SaveEvent(ThisEvent);
#endif
    }

return returnVal;
}

/*
 * The Test Harness for the event checkers is conditionally compiled using
 * the EVENTCHECKER_TEST macro (defined either in the file or at the project level).
 * No other main() can exist within the project.
 *
 * It requires a valid ES_Configure.h file in the project with the correct events in
 * the enum, and the correct list of event checkers in the EVENT_CHECK_LIST.
 *
 * The test harness will run each of your event detectors identically to the way the
 * ES_Framework will call them, and if an event is detected it will print out the function
 * name, event, and event parameter. Use this to test your event checking code and
 * ensure that it is fully functional.
 *
 * If you are locking up the output, most likely you are generating too many events.
 * Remember that events are detectable changes, not a state in itself.
 *
 * Once you have fully tested your event checking code, you can leave it in its own
 * project and point to it from your other projects. If the EVENTCHECKER_TEST marco is
 * defined in the project, no changes are necessary for your event checkers to work
 * with your other projects.
 */
#ifdef EVENTCHECKER_TEST
#include <stdio.h>
static uint8_t (*EventList[])(void) = {EVENT_CHECK_LIST};

void PrintEvent(void);

void main(void)
{
    BOARD_Init();
    /* user initialization code goes here */
    AD_Init();
    AD_AddPins(TRACK_VOLTAGE);
    AD_AddPins(TAPE_VOLTAGEfrr);
    ES_Timer_Init();
    // sets the outputs and the pins if we all use th 
    IO_PortsSetPortOutputs(TAPE_LEDfrrPort,0xfff);
    IO_PortsWritePort(TAPE_LEDfrrPort,TAPE_LEDfrrPin);
    
    // Do not alter anything below this line
    int i;

    printf("\r\nEvent checking test harness for %s", __FILE__);

    while (1)
    {
        if (IsTransmitEmpty())
        {
            for (i = 0; i < sizeof(EventList) >> 2; i++)
            {
                if (EventList[i]() == TRUE)
                {
                    PrintEvent();
                    break;
                }
            }
        }
    }
}

void PrintEvent(void)
{
    printf("\r\nFunc: %s\tEvent: %s\tParam: 0x%X", eventName,
           EventNames[storedEvent.EventType], storedEvent.EventParam);
}
#endif