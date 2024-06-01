/*
 * File: WanderSubHSM.c
 * Author: J. Edward Carryer
 * Modified: Gabriel H Elkaim
 *
 * Template file to set up a Heirarchical State Machine to work with the Events and
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
 * 10/30/11 17:59 jec      fixed references to CurrentEvent in RunTemplateSM()
 * 10/23/11 18:20 jec      began conversion from SMTemplate.c (02/20/07 rev)
 */


/*******************************************************************************
 * MODULE #INCLUDE                                                             *
 ******************************************************************************/

#include "ES_Configure.h"
#include "ES_Framework.h"
#include "BOARD.h"
#include "WanderSubHSM.h"
#include "Maw.h"
#include "ES_Timers.h"
#include "SensorEventChecker.h"

/*******************************************************************************
 * MODULE #DEFINES                                                             *
 ******************************************************************************/
typedef enum {
    InitPSubState,
    Forward,
    Reverse,
    Spin,
} WanderSubHSMState_t;

static const char *StateNames[] = {
	"InitPSubState",
	"Forward",
	"Reverse",
	"Spin",
};

#define REVERSE_TIME 250
#define SPIN_TIME 476


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

static WanderSubHSMState_t CurrentState = InitPSubState; // <- change name to match ENUM
static uint8_t MyPriority;
static uint8_t LastBump;

/*******************************************************************************
 * PUBLIC FUNCTIONS                                                            *
 ******************************************************************************/

/**
 * @Function InitWanderSubHSM(uint8_t Priority)
 * @param Priority - internal variable to track which event queue to use
 * @return TRUE or FALSE
 * @brief This will get called by the framework at the beginning of the code
 *        execution. It will post an ES_INIT event to the appropriate event
 *        queue, which will be handled inside RunTemplateFSM function. Remember
 *        to rename this to something appropriate.
 *        Returns TRUE if successful, FALSE otherwise
 * @author J. Edward Carryer, 2011.10.23 19:25 */
uint8_t InitWanderSubHSM(void) {
    ES_Event returnEvent;

    CurrentState = InitPSubState;
    returnEvent = RunWanderSubHSM(INIT_EVENT);
    if (returnEvent.EventType == ES_NO_EVENT) {
        return TRUE;
    }
    return FALSE;
}

/**
 * @Function RunWanderSubHSM(ES_Event ThisEvent)
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
ES_Event RunWanderSubHSM(ES_Event ThisEvent) {
    uint8_t makeTransition = FALSE; // use to flag transition
    WanderSubHSMState_t nextState; // <- change type to correct enum

    ES_Tattle(); // trace call stack

    switch (CurrentState) {
        case InitPSubState: // If current state is initial Psedudo State
            if (ThisEvent.EventType == ES_INIT)// only respond to ES_Init
            {
                // this is where you would put any actions associated with the
                // transition from the initial pseudo-state into the actual
                // initial state

                // now put the machine into the actual initial state
                nextState = Forward;
                makeTransition = TRUE;
                ThisEvent.EventType = ES_NO_EVENT;
            }
            break;

            //The following switch statement written by ChatGPT, because I'm exhausted. -Max
        case Forward:
            switch (ThisEvent.EventType) {
                case ES_ENTRY:
                    Maw_LeftMtrSpeed(100);
                    Maw_RightMtrSpeed(100);
                    Maw_RightDoor(1);

                    break;
                case TAPE:
                    nextState = Reverse;
                    makeTransition = TRUE;
                    ThisEvent.EventType = TAPE;
                    break;
                case BUMPER:
                    //only when a bumper is pressed
                    if(ThisEvent.EventParam){
                        nextState = Reverse;
                        makeTransition = TRUE;
                        ThisEvent.EventType = ES_NO_EVENT;
                        LastBump = ThisEvent.EventParam;
                    }
                    break;
                case PINGCLOSE: // May need specific param to state value is low enough to dodge
                    if (ThisEvent.EventParam) {
                        nextState = Spin;
                        makeTransition = TRUE;
                        ThisEvent.EventType = ES_NO_EVENT;
                    }
                    break;
                case ES_TIMEOUT:
                    if (ThisEvent.EventParam == WANDER_SUBSTATE_TIMER) {
                        nextState = Spin;
                        makeTransition = TRUE;
                        ThisEvent.EventType = ES_NO_EVENT;
                    }
                case ES_NO_EVENT:
                default:
                    // Unhandled events pass back up to the next level
                    break;
            }
            break;

        case Reverse:
            switch (ThisEvent.EventType) {
                case ES_ENTRY:
                    Maw_LeftMtrSpeed(-100);
                    Maw_RightMtrSpeed(-100);
                    ES_Timer_InitTimer(WANDER_SUBSTATE_TIMER, (REVERSE_TIME));
                    break;
                case ES_TIMEOUT:
                    if (ThisEvent.EventParam == WANDER_SUBSTATE_TIMER) {
                        nextState = Spin;
                        makeTransition = TRUE;
                        ThisEvent.EventType = ES_NO_EVENT;
                    }
                    break;
                case TAPE:
                    if (TRUE /*ThisEvent.EventParam == WANTED EVENT*/) {
                        nextState = Spin;
                        makeTransition = TRUE;
                        ThisEvent.EventType = ES_NO_EVENT;
                    }
                    break;
                case BUMPER:
                    // Back Bumpers
                    if (ThisEvent.EventParam & ((1<<BUMPERblBit) | (1<<BUMPERbrBit))) {
                        nextState = Forward;
                        makeTransition = TRUE;
                        ThisEvent.EventType = ES_NO_EVENT;

                        // This timer will not tigger on all exits thus not an 
                        // exit event
                        ES_TimerInitTimer(WANDER_SUBSTATE_TIMER, (REVERSE_TIME - ES_Timer_GetTimeRemaining(WANDER_SUBSTATE_TIMER))/2);
                    }
                    else {
                        ES_TimerInitTimer(WANDER_SUBSTATE_TIMER, (REVERSE_TIME));    
                    }
                    break;
                case ES_NO_EVENT:
                default:
                    // Unhandled events pass back up to the next level
                    break;
            }
            break;

        case Spin:
            switch (ThisEvent.EventType) {
                case ES_ENTRY: // ccw to line up with door slightly more easily
                    if (LastBump & (1<<BUMPERfrBit))
                    {
                        Maw_LeftMtrSpeed(-100);
   					    Maw_RightMtrSpeed(100);
                    }
                    else {
                    Maw_LeftMtrSpeed(100);
   					Maw_RightMtrSpeed(-100);
                    }
                    ES_Timer_InitTimer(WANDER_SUBSTATE_TIMER, SPIN_TIME);
                    Maw_RightDoor(2);
                    break;
                case ES_TIMEOUT:
                    if (ThisEvent.EventParam == WANDER_SUBSTATE_TIMER) {
                        nextState = Forward;
                        makeTransition = TRUE;
                        ThisEvent.EventType = ES_NO_EVENT;
                    }
                    break;
                case ES_NO_EVENT:
                default:
                    // Unhandled events pass back up to the next level
                    break;
            }
            break;

        default:
            // Handle unexpected state
            break;
    }


    if (makeTransition == TRUE) { // making a state transition, send EXIT and ENTRY
        // recursively call the current state with an exit event
        RunWanderSubHSM(EXIT_EVENT); // <- rename to your own Run function
        CurrentState = nextState;
        RunWanderSubHSM(ENTRY_EVENT); // <- rename to your own Run function
    }

    ES_Tail(); // trace call stack end
    return ThisEvent;
}


/*******************************************************************************
 * PRIVATE FUNCTIONS                                                           *
 ******************************************************************************/

