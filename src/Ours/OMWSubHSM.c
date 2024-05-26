/*
 * File: OMWSubHSM.c
 * Author: J. Edward Carryer
 * Modified: Gabriel H Elkaim
 *
 * OMW file to set up a Heirarchical State Machine to work with the Events and
 * Services Framework (ES_Framework) on the Uno32 for the CMPE-118/L class. Note that
 * this file will need to be modified to fit your exact needs, and most of the names
 * will have to be changed to match your code.
 *
 * There is for a substate machine. Make sure it has a unique name
 *
 * This is provided as an example and a good place to start.
 *
 * History
 * When           Who     What/Why
 * -------------- ---     --------
 * 09/13/13 15:17 ghe      added tattletail functionality and recursive calls
 * 01/15/12 11:12 jec      revisions for Gen2 framework
 * 11/07/11 11:26 jec      made the queue static
 * 10/30/11 17:59 jec      fixed references to CurrentEvent in RunOMWSM()
 * 10/23/11 18:20 jec      began conversion from SMOMW.c (02/20/07 rev)
 */


/*******************************************************************************
 * MODULE #INCLUDE                                                             *
 ******************************************************************************/

#include "ES_Configure.h"
#include "ES_Framework.h"
#include "BOARD.h"
#include "SensorEventChecker.h"
#include "OMWSubHSM.h"

/*******************************************************************************
 * MODULE #DEFINES                                                             *
 ******************************************************************************/
typedef enum {
    InitPSubState,
    Straight,
	TiltRight,
	TiltLeft,
} OMWSubHSMState_t;

static const char *StateNames[] = {
	"InitPSubState",
	"Straight",
	"TiltRight",
	"TiltLeft",
};



/*******************************************************************************
 * PRIVATE FUNCTION PROTOTYPES                                                 *
 ******************************************************************************/
/* Prototypes for private functions for this machine. They should be functions
   relevant to the behavior of this state machine */

/*******************************************************************************
 * PRIVATE MODULE VARIABLES                                                            *
 ******************************************************************************/
/* You will need MyPriority and the state variable; you may need others as well.
 * The type of state variable should match that of enum in header file. */

static OMWSubHSMState_t CurrentState = InitPSubState; // <- change name to match ENUM
static uint8_t MyPriority;


/*******************************************************************************
 * PUBLIC FUNCTIONS                                                            *
 ******************************************************************************/

/**
 * @Function InitOMWSubHSM(uint8_t Priority)
 * @param Priority - internal variable to track which event queue to use
 * @return TRUE or FALSE
 * @brief This will get called by the framework at the beginning of the code
 *        execution. It will post an ES_INIT event to the appropriate event
 *        queue, which will be handled inside RunOMWFSM function. Remember
 *        to rename this to something appropriate.
 *        Returns TRUE if successful, FALSE otherwise
 * @author J. Edward Carryer, 2011.10.23 19:25 */
uint8_t InitOMWSubHSM(void)
{
    ES_Event returnEvent;

    return TRUE;
}

/**
 * @Function RunOMWSubHSM(ES_Event ThisEvent)
 * @param ThisEvent - the event (type and param) to be responded.
 * @return Event - return event (type and param), in general should be ES_NO_EVENT
 * @brief This function is where you implement the whole of the heirarchical state
 *        machine, as this is called any time a new event is passed to the event
 *        queue. This function will be called recursively to implement the correct
 *        order for a state transition to be: exit current state -> enter next state
 *        using the ES_EXIT and ES_ENTRY events.
 * @note Remember to rename to something appropriate.
 *       The lower level state machines are run first, to see if the event is dealt
 *       with there rather than at the current level. ES_EXIT and ES_ENTRY events are
 *       not consumed as these need to pass pack to the higher level state machine.
 * @author J. Edward Carryer, 2011.10.23 19:25
 * @author Gabriel H Elkaim, 2011.10.23 19:25 */
ES_Event RunOMWSubHSM(ES_Event ThisEvent)
{
    ThisEvent.EventType = ES_NO_EVENT;
        //Both tapes are on turn left
    if((ThisEvent.EventParam & TAPEfrrBit) && (ThisEvent.EventParam & TAPEfrBit)){
        //Maw_LeftMtrSpeed(50);
        //Maw_RightMtrSpeed(100);
    }else//Both tapes are off turn right
    if(!(ThisEvent.EventParam & TAPEfrrBit) && !(ThisEvent.EventParam & TAPEfrBit)){
        //Maw_LeftMtrSpeed(100);
        //Maw_RightMtrSpeed(50);
    }else//left tape on right tape off NOT EXPECTED STOPPING
    if(!(ThisEvent.EventParam & TAPEfrrBit) && (ThisEvent.EventParam & TAPEfrBit)){
        //Maw_LeftMtrSpeed(0);
        //Maw_RightMtrSpeed(0);
    }else//left tape off right tape on on course
    if((ThisEvent.EventParam & TAPEfrrBit) && !(ThisEvent.EventParam & TAPEfrBit)){
        //Maw_LeftMtrSpeed(100);
        //Maw_RightMtrSpeed(100);
    }
    return ThisEvent;
}


/*******************************************************************************
 * PRIVATE FUNCTIONS                                                           *
 ******************************************************************************/

