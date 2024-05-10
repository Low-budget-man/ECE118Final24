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
/*******************************************************************************
 * MODULE #DEFINES                                                             *
 ******************************************************************************/
#define BATTERY_DISCONNECT_THRESHOLD 175
#define TRACK_VOLTAGE AD_PORTV3
#define TRACK_THRESH 200
#define TRACK_HYST 60
#define TAPE_VOLTAGEL
#define TAPE_VOLTAGER
#define TAPE_THRESH
#define TAPE_HYST
#define TAPERBit (0)
#define TAPELBit (1)
/*******************************************************************************
 * EVENTCHECKER_TEST SPECIFIC CODE                                                             *
 ******************************************************************************/

//#define EVENTCHECKER_TEST
#ifdef EVENTCHECKER_TEST
#include <stdio.h>
#define SaveEvent(x) do {eventName=__func__; storedEvent=x;} while (0)

static const char *eventName;
static ES_Event storedEvent;
#endif
//#define DEBUG_PRINT
#ifdef DEBUG_PRINT
#include <stdio.h>
#endif
/*******************************************************************************
 * PRIVATE FUNCTION PROTOTYPES                                                 *
 ******************************************************************************/
/* Prototypes for private functions for this EventChecker. They should be functions
   relevant to the behavior of this particular event checker */

/*******************************************************************************
 * PRIVATE MODULE VARIABLES                                                    *
 ******************************************************************************/
static enum {NOT_DETECTED, DETECTED} LastTrack = NOT_DETECTED;
static enum {NOT_DETECTED, DETECTED} LastTapeL = NOT_DETECTED;
static enum {NOT_DETECTED, DETECTED} LastTapeR = NOT_DETECTED;  
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
#ifndef EVENTCHECKER_TEST           // keep this as is for test harness
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
uint8_t CheckTrack(void){
    //sets up the basic vars that are needed for the I/O of this function
    uint8_t returnVal = FALSE;
    static enum {NOT_DETECTED, DETECTED} CurrentTrack;
    uint16_t TrackVoltage = AD_ReadADPin(TRACK_VOLTAGE);
    // checks to see what the current value is
    if(TrackVoltage > TRACK_THRESH + TRACK_HYST){
        CurrentTrack = DETECTED;
    }
    else if(TrackVoltage < TRACK_THRESH - TRACK_HYST){
        CurrentTrack = NOT_DETECTED;
    }
    // checks if there is a change from current to past and acts properly
    if(CurrentTrack != LastTrack){
        returnVal = TRUE;
        LastTrack = CurrentTrack;
        ES_Event ThisEvent;
        ThisEvent.EventParam = CurrentTrack;
        ThisEvent.EventType = TRACKWIRE;
        #ifndef EVENTCHECKER_TEST           // keep this as is for test harness
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
uint8_t CheckTape(void){
    // event checker setup
    uint8_t returnVal = FALSE;
    uint8_t param = 0;
    static enum {NOT_DETECTED, DETECTED} CurrentTapeL;
    static enum {NOT_DETECTED, DETECTED} CurrentTapeR;
    uint16_t TapeLeftVolt = AD_ReadADPin(TAPE_VOLTAGEL);
    uint16_t TapeRightVolt = AD_ReadADPin(TAPE_VOLTAGER);
    // for the left tape detetor
    if(TapeLeftVolt > TAPE_THRESH + TAPE_HYST){
        CurrentTapeL = DETECTED;
    }
    else if(TapeLeftVolt < TRACK_THRESH - TRACK_HYST){
        CurrentTapeL = NOT_DETECTED;
    }
    // for the right tape detetor
    if(TapeRightVolt > TAPE_THRESH + TAPE_HYST){
        CurrentTapeR = DETECTED;
    }
    else if(TapeRightVolt < TAPE_THRESH + TAPE_HYST){
        CurrentTapeR = NOT_DETECTED;
    }
    //if more tape detetors will add them here
    
    // compare to last left
    if(CurrentTapeL != LastTapeL){
        param += (CurrentTapeL<<TAPELBit);
    }
    // compare to last right
    if(CurrentTapeR != LastTapeR){
        param += (CurrentTapeR<<TAPERBit);
    }
    if (param)
    {
        returnVal = TRUE;
        ES_Event ThisEvent;
        ThisEvent.EventType = TAPE;
        ThisEvent.EventParam = param;
        #ifndef EVENTCHECKER_TEST           // keep this as is for test harness
        #ifdef DEBUG_PRINT
        printf("\r\n Posting a Tape  event");
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
    AD_Init();
    AD_AddPins(TRACK_VOLTAGE);
    // Do not alter anything below this line
    int i;

    printf("\r\nEvent checking test harness for %s", __FILE__);

    while (1) {
        if (IsTransmitEmpty()) {
            for (i = 0; i< sizeof (EventList) >> 2; i++) {
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