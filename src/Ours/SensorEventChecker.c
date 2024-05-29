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
#include <string.h>
#include "serial.h"
#include "ES_Configure.h"
#include "SensorEventChecker.h"
#include "ES_Events.h"
#include "serial.h"
#include "AD.h"
#include "BattService.h"
#include "SensorService.h"
#include "IO_Ports.h"
#include "ES_Timers.h"
#include "PingSensor.h"
#include <stdlib.h>
/*******************************************************************************
 * MODULE #DEFINES                                                             *
 ******************************************************************************/
// Batt #defines ---------------------------------------------------------------
#define BATTERY_DISCONNECT_THRESHOLD 175
// Track wire #defines ---------------------------------------------------------
#define TRACK_VOLTAGE AD_PORTW4
#define TRACK_THRESH 200
#define TRACK_HYST 60
// Tape #defines ---------------------------------------------------------------
// for tape sensor testing will only use the frr (front right right) tape sensor
#define ONETAPE
// the LEDs need their own pin for power we may change this later
#define TAPE_LEDfrrPort PORTX
#define TAPE_LEDfrrPin PIN5
// #ifndef ONETAPE
// #define TAPE_LEDfrPort PORTX
// #define TAPE_LEDfrPin PIN5
// #define TAPE_LEDflPort PORTX
// #define TAPE_LEDflPin PIN6
// #define TAPE_LEDfllPort PORTX
// #define TAPE_LEDfllPin PIN10
// #define TAPE_LEDbrPort PORTX
// #define TAPE_LEDbrPin PIN8
// #define TAPE_LEDblPort PORTX
// #define TAPE_LEDblPin PIN11


// #define TAPE_LED_BLUE TAPE_LEDbrPort
// #define TAPE_LED_RED TAPE_LEDfrrPort
// #define TAPE_LED_WHITE TAPE_LEDfrPort
// #define TAPE_LED_BLACK TAPE_LEDflPort
// #define TAPE_LED_BROWN TAPE_LEDfllPort
// #define TAPE_LED_GREEN TAPE_LEDblPort

// #endif
#define TAPE_VOLTAGEfrr AD_PORTV4

#define TAPE_VOLTAGEfr AD_PORTV5
#define TAPE_VOLTAGEfl AD_PORTV6
#define TAPE_VOLTAGEfll AD_PORTV7
#define TAPE_VOLTAGEbr AD_PORTV8
#define TAPE_VOLTAGEbl AD_PORTW3


#define TAPE_VOLTAGE_BLUE TAPE_VOLTAGEbr
#define TAPE_VOLTAGE_RED TAPE_VOLTAGEfrr
#define TAPE_VOLTAGE_WHITE TAPE_VOLTAGEfr
#define TAPE_VOLTAGE_BLACK TAPE_VOLTAGEfl
#define TAPE_VOLTAGE_BROWN TAPE_VOLTAGEfll
#define TAPE_VOLTAGE_GREEN TAPE_VOLTAGEbl

#define TAPE_THRESH 400 
// reading voltage
#define TAPE_HYST 50 
/*
#define TAPEfrrBit (0)
#define TAPEfrBit (1)
#define TAPEflBit (2)
#define TAPEfllBit (3)
#define TAPEbrBit (4)
#define TAPEblBit (5)
*/
// Time that is needed for the tape sensor to get a stable reading (in ms)
// Note that the time waited is 1 ms more than this
#define TAPEtime 4
// Beacon #defines -------------------------------------------------------------
#define BEACON_PORT PORTW
#define BEACON_PIN PIN3
// Bumper #defines -------------------------------------------------------------
#define BUMPERfrPORT PORTW
#define BUMPERfrPIN PIN5
#define BUMPERflPORT PORTW
#define BUMPERflPIN PIN4
#define BUMPERbrPORT PORTW
#define BUMPERbrPIN PIN7
#define BUMPERblPORT PORTY
//Pin 6 and 8 is haveing issues and does not work
#define BUMPERblPIN PIN3
//#define BUMPERfrBit (1)
//#define BUMPERflBit (0)
//#define BUMPERbrBit (3)
//#define BUMPERblBit (2)
// for the Ping sensor, most of the work is done in PingSensor.h
#define PING_HYST 32
// this is the number of points in the ping sensor moving avrage bigger is more 
// filter but slower
#define PING_FILTER 9
/*******************************************************************************
 * EVENTCHECKER_TEST SPECIFIC CODE                                                             *
 ******************************************************************************/

//#define EVENTCHECKER_TEST
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
 * PRIVATE MODULE VARIABLES                                                    *
 ******************************************************************************/
enum sensor {
    NOT_DETECTED, DETECTED
};
enum sensor LastTrack = NOT_DETECTED;
enum sensor LastTapefrr = NOT_DETECTED;

enum sensor LastTapefr = NOT_DETECTED;
enum sensor LastTapefl = NOT_DETECTED;
enum sensor LastTapefll = NOT_DETECTED;
enum sensor LastTapebr = NOT_DETECTED;
enum sensor LastTapebl = NOT_DETECTED;

enum sensor LastBeacon = NOT_DETECTED;

enum sensor LastBumpfr = NOT_DETECTED;
enum sensor LastBumpfl = NOT_DETECTED;
enum sensor LastBumpbr = NOT_DETECTED;
enum sensor LastBumpbl = NOT_DETECTED;

uint16_t LastPing = 0;

static enum {
    OFF,
    ON
} TapeLED = OFF;
static uint8_t TapeWaiting = FALSE;
static uint32_t TapeWaitStart;
static uint8_t LEDset = FALSE;
// so the current noise for the tape can be used
uint16_t TapefrrNoise;

uint16_t TapefrNoise;
uint16_t TapeflNoise;
uint16_t TapefllNoise;
uint16_t TapebrNoise;
uint16_t TapeblNoise;

// a var to store the reading to
uint16_t TapefrrRead;

uint16_t TapefrRead;
uint16_t TapeflRead;
uint16_t TapefllRead;
uint16_t TapebrRead;
uint16_t TapeblRead;
// used to store the moving Avrg for the ping sensor
uint16_t PingReadings[PING_FILTER];

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
void SetTapeLED(char state) {
    // assume only use 1 port for all of the LEDS and the track wire 
    // if not will need to change
    uint16_t pattern = 0;
    pattern |= TAPE_LEDfrrPin;
#ifndef ONETAPE
    pattern |= TAPE_LEDfrPin;
    pattern |= TAPE_LEDflPin;
    pattern |= TAPE_LEDfllPin;
    pattern |= TAPE_LEDbrPin;
    pattern |= TAPE_LEDblPin;
#endif
    if (state) {
        IO_PortsClearPortBits(TAPE_LEDfrrPort, pattern);
    } else {
        IO_PortsSetPortBits(TAPE_LEDfrrPort,pattern);
    }
}
/**
 * @Function PingFilter(state)
 * @param The current Reading of the Ping Sensor
 * @return The new moving avg value
 * @brief This Function will return a moving avrage for the ping sensor to 
 * reduce noise
 * @author Cooper Cantrell 5/23/2024 4:09PM
 */
uint16_t PingFilter(uint16_t Reading){
    uint16_t out = 0;
    // This is from stack overflow, hope it works
    //shifts the memory over 1 item  and adds so the avg can me moving
    static uint16_t cursor = 0;
    PingReadings[cursor] = Reading;
    cursor = (++cursor)%PING_FILTER;
    //get the avg of the list
    
    for (size_t i = 0; i < PING_FILTER; i++)
    {
        out += PingReadings[i];
    }
    out /= PING_FILTER;
    return out;
}


/*******************************************************************************
 * PUBLIC FUNCTIONS                                                            *
 ******************************************************************************/

/**
 * @Function SensorInit(void)
 * @param none
 * @return none
 * @brief This function will init all that is needed for the sensor so that in 
 * the main functions only this needs to be called
 * @author Cooper Cantrell 5/13/2024 3:37pm
 */
void SensorInit(void) {
    // for more than 1 sensors ---------------------------------------------------------
    AD_Init();
    ES_Timer_Init();
    // for the ping sensor -----------------------------------------------------
    PINGInit();
    // for the track wire ------------------------------------------------------
    AD_AddPins(TRACK_VOLTAGE);
    // for the tape sensor -----------------------------------------------------
    AD_AddPins(TAPE_VOLTAGEfrr);
    AD_AddPins(TAPE_VOLTAGEfr);
    AD_AddPins(TAPE_VOLTAGEfl);
    AD_AddPins(TAPE_VOLTAGEfll);
    AD_AddPins(TAPE_VOLTAGEbr);
    AD_AddPins(TAPE_VOLTAGEbl);
    // assumes that all tape sensors will use the same port for outputs
    uint16_t TapeOut = TAPE_LEDfrrPin ;
    IO_PortsSetPortOutputs(TAPE_LEDfrrPort, TapeOut);
    // Sets the phototransistor to all of them high
    // for the Beacon ----------------------------------------------------------
    IO_PortsSetPortInputs(BEACON_PORT, BEACON_PIN);
    //for the bumper -----------------------------------------------------------
    // assumes that all bupers will be on the same port for input
    // if not will need to change
    uint16_t BumperIn = BUMPERfrPIN | BUMPERflPIN | BUMPERbrPIN;
    IO_PortsSetPortInputs(BUMPERfrPORT,BumperIn);
    IO_PortsSetPortInputs(BUMPERblPORT,BUMPERblPIN);
    // for the battery reading -------------------------------------------------
    // init the ADPin for the battery
    AD_AddPins(BAT_VOLTAGE);

}

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
uint8_t CheckBattery(void) {
    static ES_EventTyp_t lastEvent = BATTERY_DISCONNECTED;
    ES_EventTyp_t curEvent;
    ES_Event thisEvent;
    uint8_t returnVal = FALSE;
    uint16_t batVoltage = AD_ReadADPin(BAT_VOLTAGE); // read the battery voltage

    if (batVoltage > BATTERY_DISCONNECT_THRESHOLD) { // is battery connected?
        curEvent = BATTERY_CONNECTED;
    } else {
        curEvent = BATTERY_DISCONNECTED;
    }
    if (curEvent != lastEvent) { // check for change from last time
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
uint8_t CheckTrack(void) {
    // sets up the basic vars that are needed for the I/O of this function
    uint8_t returnVal = FALSE;

    static enum {
        NOT_DETECTED,
        DETECTED
    } CurrentTrack;
    uint16_t TrackVoltage = AD_ReadADPin(TRACK_VOLTAGE);
    // checks to see what the current value is
    if (TrackVoltage > TRACK_THRESH + TRACK_HYST) {
        CurrentTrack = DETECTED;
    } else if (TrackVoltage < TRACK_THRESH - TRACK_HYST) {
        CurrentTrack = NOT_DETECTED;
    }
    // checks if there is a change from current to past and acts properly
    if (CurrentTrack != LastTrack) {
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
uint8_t CheckTape(void) {
    // if there is no noise to compare to turn the led off so we can get a noise reading
    if (!TapefrrNoise) {
        TapeLED = OFF;
    }

    // event checker setup
    uint8_t returnVal = FALSE;
    uint8_t param = 0;
    static enum sensor CurrentTapefrr;
    static enum sensor CurrentTapefr;
    static enum sensor CurrentTapefl;
    static enum sensor CurrentTapefll;
    static enum sensor CurrentTapebr;
    static enum sensor CurrentTapebl;
    // the LED will be off and be given LEDTIME
    if (!TapeWaiting) {
        TapeWaiting = TRUE;
        TapeWaitStart = ES_Timer_GetTime();
    }
    // writes the output power so that the LEDs will turn on and off (this may be slow if we need to optimize)
    if (!LEDset) {
        SetTapeLED(TapeLED);
        LEDset = TRUE;
    }
    // this checks to see if enough time has passed for the reading to be stable
    if (ES_Timer_GetTime() > TapeWaitStart + TAPEtime) {
        TapeWaiting = FALSE;
        LEDset = FALSE;
        if (TapeLED) // off is FALSE
        {
            TapefrrRead = AD_ReadADPin(TAPE_VOLTAGEfrr);
            TapefrRead = AD_ReadADPin(TAPE_VOLTAGEfr);
            TapeflRead = AD_ReadADPin(TAPE_VOLTAGEfl);
            TapefllRead = AD_ReadADPin(TAPE_VOLTAGEfll);
            TapebrRead = AD_ReadADPin(TAPE_VOLTAGEbr);
            TapeblRead = AD_ReadADPin(TAPE_VOLTAGEbl);
        } else {
            TapefrrNoise = AD_ReadADPin(TAPE_VOLTAGEfrr);
            TapefrNoise = AD_ReadADPin(TAPE_VOLTAGEfr);
            TapeflNoise = AD_ReadADPin(TAPE_VOLTAGEfl);
            TapefllNoise = AD_ReadADPin(TAPE_VOLTAGEfll);
            TapebrNoise = AD_ReadADPin(TAPE_VOLTAGEbr);
            TapeblNoise = AD_ReadADPin(TAPE_VOLTAGEbl);
        }
        TapeLED = !TapeLED;
        // after the check compare to past values and noise to the thresh and raise events
        //only if has at least 1 of each reading
        if (TapefrrNoise && TapefrrRead) {
            if ((TapefrrNoise - TapefrrRead) >= TAPE_THRESH + TAPE_HYST) {
                CurrentTapefrr = NOT_DETECTED;
            }
            else if ((TapefrrNoise - TapefrrRead) <= TAPE_THRESH - TAPE_HYST) {
                CurrentTapefrr = DETECTED;
            }
            if ((TapefrNoise - TapefrRead) >= TAPE_THRESH + TAPE_HYST) {
                CurrentTapefr = NOT_DETECTED;
            }
            else if ((TapefrNoise - TapefrRead) <= TAPE_THRESH - TAPE_HYST) {
                CurrentTapefr = DETECTED;
            }
            if ((TapeflNoise - TapeflRead) >= TAPE_THRESH + TAPE_HYST) {
                CurrentTapefl = NOT_DETECTED;
            }
            else if ((TapeflNoise - TapeflRead) <= TAPE_THRESH - TAPE_HYST) {
                CurrentTapefl = DETECTED;
            }
            if ((TapefllNoise - TapefllRead) >= TAPE_THRESH + TAPE_HYST) {
                CurrentTapefll = NOT_DETECTED;
            }
            else if ((TapefllNoise - TapefllRead) <= TAPE_THRESH - TAPE_HYST) {
                CurrentTapefll = DETECTED;
            }
            if ((TapebrNoise - TapebrRead) >= TAPE_THRESH + TAPE_HYST) {
                CurrentTapebr = NOT_DETECTED;
            }
            else if ((TapebrNoise - TapebrRead) <= TAPE_THRESH - TAPE_HYST) {
                CurrentTapebr = DETECTED;
            }
            if ((TapeblNoise - TapeblRead) >= TAPE_THRESH + TAPE_HYST) {
                CurrentTapebl = NOT_DETECTED;
            }
            else if ((TapeblNoise - TapeblRead) <= TAPE_THRESH - TAPE_HYST) {
                CurrentTapebl = DETECTED;
            }

            // compare past values with current values
            if (CurrentTapefrr != LastTapefrr) {
                returnVal = TRUE;
                LastTapefrr = CurrentTapefrr;
            }
            if (CurrentTapefr != LastTapefr) {
                returnVal = TRUE;
                LastTapefr = CurrentTapefr;
            }
            if (CurrentTapefl != LastTapefl) {
                returnVal = TRUE;
                LastTapefl = CurrentTapefl;
            }
            if (CurrentTapefll != LastTapefll) {
                returnVal = TRUE;
                LastTapefll = CurrentTapefll;
            }
            if (CurrentTapebr != LastTapebr) {
                returnVal = TRUE;
                LastTapebr = CurrentTapebr;
            }
            if (CurrentTapebl != LastTapebl) {
                returnVal = TRUE;
                LastTapebl = CurrentTapebl;
            }
        }
    }
    if (returnVal) {
        param += (CurrentTapefrr << TAPEfrrBit);
        param += (CurrentTapefr << TAPEfrBit);
        param += (CurrentTapefl << TAPEflBit);
        param += (CurrentTapefll << TAPEfllBit);
        param += (CurrentTapebr << TAPEbrBit);
        param += (CurrentTapebl << TAPEblBit);
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

/**
 * @Function CheckBeacon(void)
 * @param none
 * @return TRUE or FALSE
 * @brief This function is the event checker that detects if there is a change
 *      in beacon detetion
 * @author Cooper Cantrell 5/14/2024 2:47
 */
uint8_t CheckBeacon(void) {
    uint8_t returnVal = FALSE;
    enum sensor CurrentBeacon = !(BEACON_PIN & IO_PortsReadPort(BEACON_PORT));
    if ((CurrentBeacon != LastBeacon)) {
        LastBeacon = CurrentBeacon;
        returnVal = TRUE;
        ES_Event ThisEvent;
        ThisEvent.EventParam = CurrentBeacon;
        ThisEvent.EventType = BEACON;
#ifndef EVENTCHECKER_TEST // keep this as is for test harness
#ifdef DEBUG_PRINT
        printf("\r\n Posting a BEACON wire event");
#endif
        PostSensorService(ThisEvent);
#else
        SaveEvent(ThisEvent);
#endif
    }
    return returnVal;
}

/**
 * @Function CheckBumper(void)
 * @param none
 * @return TRUE or FALSE
 * @brief This function is the event checker that detects if there is a change
 *      in Bumper detetion
 * @author Cooper Cantrell 5/15/2024 5:26
 */
uint8_t CheckBumper(void){
    uint8_t returnVal = FALSE;
    enum sensor CurrentBumpfr = !!(BUMPERfrPIN & IO_PortsReadPort(BUMPERfrPORT));
    enum sensor CurrentBumpfl = !!(BUMPERflPIN & IO_PortsReadPort(BUMPERflPORT));
    enum sensor CurrentBumpbr = !!(BUMPERbrPIN & IO_PortsReadPort(BUMPERbrPORT));
    enum sensor CurrentBumpbl = !!(BUMPERblPIN & IO_PortsReadPort(BUMPERblPORT));
    //printf("\r\nBumper BL = %d", CurrentBumpbl);
    uint8_t param = (CurrentBumpfr<<BUMPERfrBit) | (CurrentBumpfl<<BUMPERflBit) | (CurrentBumpbr<<BUMPERbrBit) | (CurrentBumpbl <<BUMPERblBit);
    if ((CurrentBumpfr!=LastBumpfr) || (CurrentBumpfl!=LastBumpfl) || 
    (CurrentBumpbr!=LastBumpbr) || (CurrentBumpbl!=LastBumpbl))
    {
        LastBumpfr = CurrentBumpfr;
        LastBumpfl = CurrentBumpfl;
        LastBumpbr = CurrentBumpbr;
        LastBumpbl = CurrentBumpbl;
        returnVal = TRUE;
        ES_Event ThisEvent;
        ThisEvent.EventParam = param;
        ThisEvent.EventType = BUMPER;
#ifndef EVENTCHECKER_TEST // keep this as is for test harness
#ifdef DEBUG_PRINT
        printf("\r\n Posting a BUMPER wire event");
#endif
        PostSensorService(ThisEvent);
#else
        SaveEvent(ThisEvent);
#endif
    }
    return returnVal;
}

/**
 * @Function CheckPing(void)
 * @param none
 * @return TRUE or FALSE
 * @brief This function is the event checker that detects if there is a change
 *      in Ping detection
 * @author Cooper Cantrell 5/15/2024 5:26
 */
uint8_t CheckPing(void){
    uint16_t CurrentPing = PingFilter(PINGGetData());
    uint8_t returnVal = FALSE;
    //printf("\r\n PING SENSOR DIST %d",CurrentPing);
    if (abs(CurrentPing - LastPing) > PING_HYST)
    {
        returnVal = TRUE;
        LastPing = CurrentPing;
        ES_Event ThisEvent;
        ThisEvent.EventType = PING;
        ThisEvent.EventParam = CurrentPing;
#ifndef EVENTCHECKER_TEST // keep this as is for test harness
#ifdef DEBUG_PRINT
        printf("\r\n Posting a PING event");
#endif
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
static uint8_t(*EventList[])(void) = {EVENT_CHECK_LIST};

void PrintEvent(void);

void main(void) {
    BOARD_Init();
    /* user initialization code goes here */
    SensorInit();
    // Do not alter anything below this line
    int i;

    printf("\r\nEvent checking test harness for %s", __FILE__);

    while (1) {
        if (IsTransmitEmpty()) {
            for (i = 0; i < sizeof (EventList) >> 2; i++) {
                if (EventList[i]() == TRUE) {
                    PrintEvent();
                    break;
                }
            }
        }
    }
}

void PrintEvent(void) {
    printf("\r\nFunc: %s\tEvent: %s\tParam: 0x%X", eventName,
            EventNames[storedEvent.EventType], storedEvent.EventParam);
}
#endif