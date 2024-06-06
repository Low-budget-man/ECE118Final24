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
#include "Maw.h"
#include "LED.h"
/*******************************************************************************
 * MODULE #DEFINES                                                             *
 ******************************************************************************/
#define DOORTIME 100
//Bigger to be more open (closer to 90 deg in)
#define collectR 2250
#define depositR 725
#define blockR 1550
// Smaller to be more open (sticking out all of the way)
#define depositL 2250
#define collectL 850
#define blockO -25
#define Dummy 0

/*******************************************************************************
 * PRIVATE FUNCTION PROTOTYPES                                                 *
 ******************************************************************************/
/* Prototypes for private functions for this machine. They should be functions
   relevant to the behavior of this state machine */

/*******************************************************************************
 * PRIVATE MODULE VARIABLES                                                    *
 ******************************************************************************/
static DOOR doorConfig = Blocking;
static uint8_t Priority;

static uint16_t LPositions[] = {
    depositL,
    collectL,
    Dummy,
};
static uint16_t RPositions[] = {
    depositR,
    collectR,
    blockR,
};
/*******************************************************************************
 * PUBLIC FUNCTIONS                                                            *
 ******************************************************************************/

/**
 * @Function InitDoorService(uint8_t Priority)
 * @param Priority - internal variable to track which event queue to use
 * @return TRUE or FALSE
 * @brief This will get called by the framework at the beginning of the code
 *        execution. It will post an ES_INIT event to the appropriate event
 *        queue, which will be handled inside RunTemplateService function. Remember
 *        to rename this to something appropriate.
 *        Returns TRUE if successful, FALSE otherwise
 * @author Cooper Cantrell 5/8/2024 8:13 PM*/
uint8_t InitDoorService(uint8_t InputPriority){
    ES_Event ThisEvent;
    Priority = InputPriority;
    // for the init of the timers
    ES_Timer_Init();
    // post the initial transition event
    ThisEvent.EventType = ES_INIT;
    if (ES_PostToService(Priority, ThisEvent) == TRUE)
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

/**
 * @Function PostDoorService(ES_Event ThisEvent)
 * @param ThisEvent - the event (type and param) to be posted to queue
 * @return TRUE or FALSE
 * @brief This function is a wrapper to the queue posting function, and its name
 *        will be used inside ES_Configure to point to which queue events should
 *        be posted to. Remember to rename to something appropriate.
 *        Returns TRUE if successful, FALSE otherwise
 * @author Cooper Cantrell 5/8/2024 8:13 PM */
uint8_t PostDoorService(ES_Event ThisEvent)
{
    return ES_PostToService(Priority, ThisEvent);
}

/**
 * @Function RunDoorService(ES_Event ThisEvent)
 * @param ThisEvent - the event (type and param) to be responded.
 * @return Event - return event (type and param), in general should be ES_NO_EVENT
 * @brief This function is where you implement the whole of the service,
 *        as this is called any time a new event is passed to the event queue.  
 * @author Cooper Cantrell 5/8/2024 */
ES_Event RunDoorService(ES_Event ThisEvent){
    //printf("\r\n Got Door post %s, param %d",EventNames[ThisEvent.EventType],ThisEvent.EventParam);
    switch (ThisEvent.EventType)
    {
    case DOORS:
        if (!(ThisEvent.EventParam == doorConfig))
        {
            
            LPositions[2] = blockR - blockO + 2*(blockO * doorConfig);
            doorConfig = ThisEvent.EventParam;
            Maw_LeftDoor(LPositions[ThisEvent.EventParam]);
            // printf("setting left door to position %d", LPositions[ThisEvent.EventParam]);
            ES_Timer_InitTimer(DOORTIMER, DOORTIME);
        }
        
        break;
    case ES_TIMEOUT:
        if(ThisEvent.EventParam == DOORTIMER){
            Maw_RightDoor(RPositions[doorConfig]);
            // printf("setting right door to position %d", RPositions[doorConfig]);
        }
        break;
    default:
        break;
    }

    return NO_EVENT;
}


/*******************************************************************************
 * PRIVATE FUNCTIONs                      
 --+                                     *
 ******************************************************************************/
