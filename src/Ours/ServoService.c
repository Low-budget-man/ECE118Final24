/*
 * File: ServoService.c
 * Author: Max Meyers
 * Created 5/13/2024 at 1:13PM
 */

/*******************************************************************************
 * MODULE #INCLUDE                                                             *
 ******************************************************************************/
#include "../../include/Ours/ServoEventChecker.h"
#include "../../include/Provided/LED.h"
#include "../../include/Ours/ES_Configure.h"
#include "../../include/Provided/ES_Framework.h"
#include "../../include/Ours/ServoService.h"
#include "../../include/Provided/LED.h"
#include <stdio.h>

/*******************************************************************************
 * MODULE #DEFINES                                                             *
 ******************************************************************************/
#define LEFT_SERVO_LED (0b010)
#define RIGHT_SERVO_LED (0b100)
#define INWARD_PULSE 0
#define OUTWARD_PULSE 1023
#define LEFT_SERVO_PIN PWM_PORTY10
#define RIGHT_SERVO_PIN PWM_PORTY12 // only 5 total PWM pins allowed by hardware, these are 2 of them
#define DOOR_DELAY 200

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
 * @Function InitServoService(uint8_t Priority)
 * @param Priority - internal variable to track which event queue to use
 * @return TRUE or FALSE
 * @brief This will get called by the framework at the beginning of the code
 *        execution. It will post an ES_INIT event to the appropriate event
 *        queue, which will be handled inside RunTemplateService function. Remember
 *        to rename this to something appropriate.
 *        Returns TRUE if successful, FALSE otherwise
 * @author Max Meyers 5/13/2024 1:13 PM*/
uint8_t InitServoService(uint8_t Priority){
    ES_Event ThisEvent;

	ES_Timer_Init(SERVO_TIMER, DOOR_DELAY);
    MyPriority = Priority;
    //Need to del later
    printf("\r\n Init Servo Service");
    // post the initial transition event
    ThisEvent.EventType = ES_INIT;
	
    if (ES_PostToService(MyPriority, ThisEvent) == TRUE) {
        return TRUE;
    } else {
        return FALSE;
    }
}

/**
 * @Function PostServoService(ES_Event ThisEvent)
 * @param ThisEvent - the event (type and param) to be posted to queue
 * @return TRUE or FALSE
 * @brief This function is a wrapper to the queue posting function, and its name
 *        will be used inside ES_Configure to point to which queue events should
 *        be posted to. Remember to rename to something appropriate.
 *        Returns TRUE if successful, FALSE otherwise
 * @author Max Meyers 5/13/2024 1:15 PM */
uint8_t PostServoService(ES_Event ThisEvent)
{
    return ES_PostToService(MyPriority, ThisEvent);
}

/**
 * @Function RunTemplateService(ES_Event ThisEvent)
 * @param ThisEvent - the event (type and param) to be responded.
 * @return Event - return event (type and param), in general should be ES_NO_EVENT
 * @brief This function is where you implement the whole of the service,
 *        as this is called any time a new event is passed to the event queue.  
 * @author Max Meyers 5/8/2024 */
ES_Event RunServoService(ES_Event ThisEvent){
    ES_Event ReturnEvent;
	static ES_Event_typ_t LastEvent = ES_INIT;
    printf("\r\n Servo Event");
    ReturnEvent.EventType = ES_NO_EVENT; // assume no errors
    // when simple service test is called it will print otherwise 
    // the LEDS will be used to show that the service can be processed
    switch (ThisEvent.EventType) {
        case ES_INIT:
            // No hardware initialization or single time setups, those
            // go in the init function above.
            //
            // This section is used to reset service for some reason
            break;
        case TRACKWIRE: 
            if(ThisEvent.EventParam){
                // detected
                LED_OnBank(LED_BANK1,LEFT_SERVO_LED);
            }
            else{
                // not detected
                LED_OffBank(LED_BANK1,LEFT_SERVO_LED);
            }
			ES_Timer_InitTimer(SERVO_TIMER, DOOR_DELAY);
            break;
		case ES_TIMEOUT: 
            if((LastEvent.EventType == TRACKWIRE) && LastEvent.EventParam){
                // Track wire detected last event
                LED_OnBank(LED_BANK1,RIGHT_SERVO_LED);
				ReturnEvent.EventType = DOORS_OPEN;
            }
            else{
                // not detected
                LED_OffBank(LED_BANK1,RIGHT_SERVO_LED);
				ReturnEvent.EventType = DOORS_CLOSED;
            }
            break;
        default:
            printf("ERROR UNKNOWN EVENT IN SERVICE");
            break;
    }
	LastEvent = ThisEvent;
    return ReturnEvent;
}

/*******************************************************************************
 * PRIVATE FUNCTIONs                                                           *
 ******************************************************************************/

