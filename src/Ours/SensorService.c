/*
 * File: SensorService.c
 * Author: Cooper Cantrell
 * Created 5/8/2024 at 10:36PM
 */

/*******************************************************************************
 * MODULE #INCLUDE                                                             *
 ******************************************************************************/
#include "../../include/Ours/SensorEventChecker.h"
#include "../../include/Provided/LED.h"
#include "../../include/Ours/ES_Configure.h"
#include "../../include/Provided/ES_Framework.h"
#include "../../include/Ours/SensorService.h"
#include "../../include/Provided/LED.h"
#include "ES_Timers.h"
#include <stdio.h>
#include <stdint.h>
#include "MawHSM.h"
#include "LED.h"
/*******************************************************************************
 * MODULE #DEFINES                                                             *
 ******************************************************************************/
#define TRACK_LED (0x1)
#define TAPE_LED (0x2)
#define BEACON_LED (0x4)
#define DEBOUNCE_WaitB 2
#define DEBOUNCE_WaitP 32
#define DEBOUNCE_WaitT 32

#define CLOSE_HYST 50

//#define ServiceTestHarness
/*******************************************************************************
 * PRIVATE FUNCTION PROTOTYPES                                                 *
 ******************************************************************************/
/* Prototypes for private functions for this machine. They should be functions
   relevant to the behavior of this state machine */

/*******************************************************************************
 * PRIVATE MODULE VARIABLES                                                    *
 ******************************************************************************/
enum sensor {
    NOT_DETECTED, DETECTED
};
static uint8_t MyPriority;
static uint8_t LastBump;
static uint8_t LastTrack;
static uint8_t LastTrackP; //Last Track Posted
static uint16_t LastPing;
static enum sensor Dist;
uint16_t CLOSE_THRESH = PINGCLOSEc;
/*******************************************************************************
 * PUBLIC FUNCTIONS                                                            *
 ******************************************************************************/
/**
 * @Function ChangePingThres(uint16_t Newval)
 * @param Newval - the new value for the ping close thesh
 * @return void
 * @brief This function will change the PingClose Threshold 
 * @author Cooper Cantrell 6/1/2024 4:14 PM*/
void ChangePingThres(uint16_t Newval){
    CLOSE_THRESH = Newval;
}
/**
 * @Function InitSensorService(uint8_t Priority)
 * @param Priority - internal variable to track which event queue to use
 * @return TRUE or FALSE
 * @brief This will get called by the framework at the beginning of the code
 *        execution. It will post an ES_INIT event to the appropriate event
 *        queue, which will be handled inside RunTemplateService function. Remember
 *        to rename this to something appropriate.
 *        Returns TRUE if successful, FALSE otherwise
 * @author Cooper Cantrell 5/8/2024 8:13 PM*/
uint8_t InitSensorService(uint8_t Priority)
{
    ES_Event ThisEvent;

    MyPriority = Priority;
    // for the init of the timers
    ES_Timer_Init();
    // post the initial transition event
    ThisEvent.EventType = ES_INIT;
    if (ES_PostToService(MyPriority, ThisEvent) == TRUE)
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

/**
 * @Function PostSensorService(ES_Event ThisEvent)
 * @param ThisEvent - the event (type and param) to be posted to queue
 * @return TRUE or FALSE
 * @brief This function is a wrapper to the queue posting function, and its name
 *        will be used inside ES_Configure to point to which queue events should
 *        be posted to. Remember to rename to something appropriate.
 *        Returns TRUE if successful, FALSE otherwise
 * @author Max Meyers 5/13/2024 1:13 PM */
uint8_t PostSensorService(ES_Event ThisEvent)
{
    return ES_PostToService(MyPriority, ThisEvent);
}

/**
 * @Function RunTemplateService(ES_Event ThisEvent)
 * @param ThisEvent - the event (type and param) to be responded.
 * @return Event - return event (type and param), in general should be ES_NO_EVENT
 * @brief This function is where you implement the whole of the service,
 *        as this is called any time a new event is passed to the event queue.
 * @author Cooper Cantrell 5/8/2024 */
ES_Event RunSensorService(ES_Event ThisEvent)
{
    ES_Event ReturnEvent;
    ReturnEvent.EventType = ES_NO_EVENT; // assume no errors
    // when simple service test is called it will print otherwise
    // the LEDS will be used to show that the service can be processed
    switch (ThisEvent.EventType)
    {
    case ES_INIT:
        // No hardware initialization or single time setups, those
        // go in the init function above.
        //
        // This section is used to reset service for some reason
        break;
    case TRACKWIRE:
//        if(ThisEvent.EventParam){
//            LED_OnBank(LED_BANK1,TRACK_LED);
//        } else {
//            LED_OffBank(LED_BANK1,TRACK_LED);
//        }
        ES_Timer_InitTimer(TRACK_DEBOUNCE_T,DEBOUNCE_WaitT);
        LastTrack = ThisEvent.EventParam;
        break;
    case TAPE:
//        if(ThisEvent.EventParam){
//            LED_OnBank(LED_BANK1,TAPE_LED);
//        } else {
//            LED_OffBank(LED_BANK1,TAPE_LED);
//        }
#ifdef ServiceTestHarness
        printf("\r\nTape Event with the param,0x%x", ThisEvent.EventParam);
#else
        PostMawHSM(ThisEvent);
#endif
        // Temp case to see if the event is raised properly
        //            if(ThisEvent.EventParam){
        //                // detected
        //                LED_OnBank(LED_BANK1,TAPE_LED);
        //            }
        //            else{
        //                // not detected
        //                LED_OffBank(LED_BANK1,TAPE_LED);
        //            }
        break;
    case BEACON:
#ifdef ServiceTestHarness
        printf("\r\n Beacon Event param: %x", ThisEvent.EventParam);
#endif

        break;
    case BUMPER:
        ES_Timer_InitTimer(BUMPER_DEBOUNCE_T, DEBOUNCE_WaitB);
        LastBump = ThisEvent.EventParam;
        break;
    case ES_TIMEOUT:
        if (ThisEvent.EventParam == BUMPER_DEBOUNCE_T)
        {
            
            ES_Event PostEvent;
            PostEvent.EventParam = LastBump;
            PostEvent.EventType = BUMPER;
            LED_SetBank(LED_BANK2,LastBump);
#ifdef ServiceTestHarness
            printf("\r\n Debounced Bumper Event with param %x", LastBump);
#else
        PostMawHSM(PostEvent);
#endif
        }
        else if (ThisEvent.EventParam == PING_DEBOUNCE_T){
            enum sensor ThisDist = Dist;
            if(LastPing > CLOSE_THRESH + CLOSE_HYST){
                ThisDist = NOT_DETECTED;
            }
            else if(LastPing < CLOSE_THRESH - CLOSE_HYST){
                ThisDist = DETECTED;
            }
            if(ThisDist != Dist){
                ES_Event PostEvent;
                PostEvent.EventType = PINGCLOSE;
                PostEvent.EventParam = ThisDist;
                Dist = ThisDist;
                PostSensorService(PostEvent);
            }
        }
        else if (ThisEvent.EventParam == TRACK_DEBOUNCE_T)
        {
            if(LastTrack != LastTrackP){
#ifdef ServiceTestHarness
            printf("\r\nTrack Event with the param,0x%x", LastTrack);
#else
            ES_Event PostEvent;
            PostEvent.EventType = TRACKWIRE;
            PostEvent.EventParam = LastTrack;
            PostMawHSM(PostEvent);
#endif
        }
           LastTrackP = LastTrack;
        }
        
        else
        {
//            printf("\r\nERROR: Unknown TimerParam in SensorService");
        }
        break;
    case PING:
        ES_Timer_InitTimer(PING_DEBOUNCE_T, DEBOUNCE_WaitP);
        LastPing = ThisEvent.EventParam;       
        break; 
    case PINGCLOSE:
#ifdef ServiceTestHarness
            printf("\r\n PINGCLOSE Event with param %x", ThisEvent.EventParam);
#else
        PostMawHSM(ThisEvent);
#endif
        break;   
    // for events we want to ignore
    case ES_NO_EVENT:
        break;
    case ES_TIMERACTIVE:
        break;
    case ES_TIMERSTOPPED:
        break;
    default:
        printf("\r\nERROR: Unknown event in SensorService: %s",EventNames[ThisEvent.EventType]);
    }
    // Post All Events to the HSM
    return ReturnEvent;
}

/*******************************************************************************
 * PRIVATE FUNCTIONs                                                           *
 ******************************************************************************/
