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
#include <stdio.h>

/*******************************************************************************
 * MODULE #DEFINES                                                             *
 ******************************************************************************/
#define TRACK_LED (0x1)
#define TAPE_LED (0x2)
#define BEACON_LED (0x4)
/*******************************************************************************
 * PRIVATE FUNCTION PROTOTYPES                                                 *
 ******************************************************************************/
/* Prototypes for private functions for this machine. They should be functions
   relevant to the behavior of this state machine */

/*******************************************************************************
 * PRIVATE MODULE VARIABLES                                                    *
 ******************************************************************************/

static uint8_t MyPriority;

/*******************************************************************************
 * PUBLIC FUNCTIONS                                                            *
 ******************************************************************************/

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
 * @author Cooper Cantrell 5/8/2024 8:13 PM */
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
        printf("\r\nTrack Event with the param,0x%x", ThisEvent.EventParam);
        if (ThisEvent.EventParam)
        {
            // detected
            LED_OnBank(LED_BANK1, TRACK_LED);
        }
        else
        {
            // not detected
            LED_OffBank(LED_BANK1, TRACK_LED);
        }
        break;
    case TAPE:
        // Temp case to see if the event is raised properly
        printf("\r\nTape Event with the param,0x%x", ThisEvent.EventParam);
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
        printf("\r\n Beacon Event param: %x", ThisEvent.EventParam);
        if (ThisEvent.EventParam)
        {
            // detected
            LED_OnBank(LED_BANK1, BEACON_LED);
        }
        else
        {
            // not detected
            LED_OffBank(LED_BANK1, BEACON_LED);
        }
        break;
    case BUMPER:
        printf("\r\n Bumper Event param: %x", ThisEvent.EventParam);
    default:
        printf("\r\nERROR UNKNOWN EVENT IN SERVICE");
        break;
    }
    return ReturnEvent;
}

/*******************************************************************************
 * PRIVATE FUNCTIONs                                                           *
 ******************************************************************************/
