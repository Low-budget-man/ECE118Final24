/*
 * File: TemplateSubHSM.c
 * Author: J. Edward Carryer
 * Modified: Gabriel Elkaim and Soja-Marie Morgens
 *
 * Template file to set up a Heirarchical State Machine to work with the Events and
 * Services Framework (ES_Framework) on the Uno32 for the CMPE-118/L class. Note that
 * this file will need to be modified to fit your exact needs, and most of the names
 * will have to be changed to match your code.
 *
 * There is another template file for the SubHSM's that is slightly differet, and
 * should be used for all of the subordinate state machines (flat or heirarchical)
 *
 * This is provided as an example and a good place to start.
 *
 * History
 * When           Who     What/Why
 * -------------- ---     --------
 * 09/13/13 15:17 ghe      added tattletail functionality and recursive calls
 * 01/15/12 11:12 jec      revisions for Gen2 framework
 * 11/07/11 11:26 jec      made the queue static
 * 10/30/11 17:59 jec      fixed references to CurrentEvent in RunTemplateSM()
 * 10/23/11 18:20 jec      began conversion from SMTemplate.c (02/20/07 rev)
 */


/*******************************************************************************
 * MODULE #INCLUDE                                                             *
 ******************************************************************************/

#include "ES_Configure.h"
#include "ES_Framework.h"
#include "BOARD.h"
#include "FollowTapeHSM.h"
#include "OMWSubHSM.h" 
#include "AvoidObstacleSubHSM.h" 
/*******************************************************************************
 * PRIVATE #DEFINES                                                            *
 ******************************************************************************/
//Include any defines you need to do
// Temp 1 for testing
#define CORRECT_TAPE_MASK 1

/*******************************************************************************
 * MODULE #DEFINES                                                             *
 ******************************************************************************/


typedef enum {
    InitPState,
    Align,
	Forward,
	OMW,
	AvoidObstacle,

} FollowTapeHSMState_t;

static const char *StateNames[] = {
	"InitPState",
	"Align",
	"Forward",
	"OMW",
	"AvoidObstacle",
};


/*******************************************************************************
 * PRIVATE FUNCTION PROTOTYPES                                                 *
 ******************************************************************************/
/* Prototypes for private functions for this machine. They should be functions
   relevant to the behavior of this state machine
   Example: char RunAway(uint_8 seconds);*/
/*******************************************************************************
 * PRIVATE MODULE VARIABLES                                                            *
 ******************************************************************************/
/* You will need MyPriority and the state variable; you may need others as well.
 * The type of state variable should match that of enum in header file. */

static FollowTapeHSMState_t CurrentState = InitPState; // <- change enum name to match ENUM
static uint8_t MyPriority;


/*******************************************************************************
 * PUBLIC FUNCTIONS                                                            *
 ******************************************************************************/

/**
 * @Function InitTemplateHSM(uint8_t Priority)
 * @param Priority - internal variable to track which event queue to use
 * @return TRUE or FALSE
 * @brief This will get called by the framework at the beginning of the code
 *        execution. It will post an ES_INIT event to the appropriate event
 *        queue, which will be handled inside RunTemplateFSM function. Remember
 *        to rename this to something appropriate.
 *        Returns TRUE if successful, FALSE otherwise
 * @author J. Edward Carryer, 2011.10.23 19:25 */
uint8_t InitFollowTapeHSM(void)
{
    // put us into the Initial PseudoState
    CurrentState = InitPState;
    // post the initial transition event
    ES_Event ThisEvent;
    ThisEvent.EventType = ES_INIT;
    RunFollowTapeHSM(ThisEvent);
}
/**
 * @Function RunTemplateHSM(ES_Event ThisEvent)
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
ES_Event RunFollowTapeHSM(ES_Event ThisEvent)
{
    uint8_t makeTransition = FALSE; // use to flag transition
    FollowTapeHSMState_t nextState; // <- change type to correct enum

    ES_Tattle(); // trace call stack

    switch (CurrentState) {
    case InitPState: // If current state is initial Pseudo State
        if (ThisEvent.EventType == ES_INIT)// only respond to ES_Init
        {
            // this is where you would put any actions associated with the
            // transition from the initial pseudo-state into the actual
            // initial state
            // Initialize all sub-state machines
            //InitTemplateSubHSM();
            // now put the machine into the actual initial state
            nextState = Align;
            makeTransition = TRUE;
            ThisEvent.EventType = ES_NO_EVENT;
            ;
        }
        break;

    case Align: 
        switch (ThisEvent.EventType) {
			case ES_ENTRY: 
//					Maw_LeftMtrSpeed(-20);
//					Maw_RightMtrSpeed(20);
					break;
			case TAPE: 
				if(ThisEvent.EventParam == 0){
					nextState = Forward;
					makeTransition = TRUE;
					ThisEvent.EventType = ES_NO_EVENT;
				}
				else if ( ThisEvent.EventParam == CORRECT_TAPE_MASK){
					nextState = OMW;
					makeTransition = TRUE;
					ThisEvent.EventType = ES_NO_EVENT;
				}
				break;
			case ES_NO_EVENT:
			default:
				break;
			}
        break;
		
	case Forward:
		switch (ThisEvent.EventType) {
			case ES_ENTRY: 
//					Maw_LeftMtrSpeed(100);
//					Maw_RightMtrSpeed(100);
					break;
			case TAPE: 
				if(ThisEvent.EventParam != 0){
					nextState = Align;
					makeTransition = TRUE;
					ThisEvent.EventType = ES_NO_EVENT;
				}
			case ES_NO_EVENT:
			default:
				break;
			}
		break;
		
	case OMW:
		switch (ThisEvent.EventType) {
			//ThisEvent = RunOMWSubHSM(ThisEvent);
			case BUMPER: 
				nextState = AvoidObstacle;
				makeTransition = TRUE;
				ThisEvent.EventType = ES_NO_EVENT;
			case ES_NO_EVENT:
			default:
				break;
			}
		break;
		
	case AvoidObstacle:
		switch (ThisEvent.EventType) {
			//ThisEvent = RunDodgeObstacleSubHSM(ThisEvent);
			case OBSTACLE_AVOIDED: 
				nextState = OMW;
				makeTransition = TRUE;
				ThisEvent.EventType = ES_NO_EVENT;
			case ES_NO_EVENT:
			default:
				break;
			}
		break;
		
	
	
		
    default: // all unhandled states fall into here
        break;
    } // end switch on Current State

    if (makeTransition == TRUE) { // making a state transition, send EXIT and ENTRY
        // recursively call the current state with an exit event
        RunFollowTapeHSM(EXIT_EVENT); // <- rename to your own Run function
        CurrentState = nextState;
        RunFollowTapeHSM(ENTRY_EVENT); // <- rename to your own Run function
    }

    ES_Tail(); // trace call stack end
    return ThisEvent;
}


/*******************************************************************************
 * PRIVATE FUNCTIONS                                                           *
 ******************************************************************************/
