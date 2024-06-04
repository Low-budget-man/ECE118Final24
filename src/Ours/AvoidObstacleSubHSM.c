/*
 * File: AvoidObstacleSubHSM.c
 * Author: J. Edward Carryer
 * Modified: Gabriel H Elkaim
 *
 * AvoidObstacle file to set up a Heirarchical State Machine to work with the Events and
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
 * 10/30/11 17:59 jec      fixed references to CurrentEvent in RunAvoidObstacleSM()
 * 10/23/11 18:20 jec      began conversion from SMAvoidObstacle.c (02/20/07 rev)
 */


/*******************************************************************************
 * MODULE #INCLUDE                                                             *
 ******************************************************************************/

#include "ES_Configure.h"
#include "ES_Framework.h"
#include "BOARD.h"
#include "AvoidObstacleSubHSM.h"
#include "Maw.h"
#include "SensorService.h"
/*******************************************************************************
 * MODULE #DEFINES                                                             *
 ******************************************************************************/

/*****PLEASE CHANGE THESE AFTER TESTING*****/
#define DEBUGPRINT
#define BackUpTime 480 
#define BackUpETime 1000
#define Right1Time 832
#define Forward1Time 1598
#define Left1Time 832
#define Forward2Time 2820
//#define Left2Time 1250
#define Right2Time 832

//#define USEPING

//not ping special defines
#define TurnLTime 426
#define BackLTime 426
#define DriftRTime 2500
#define TankRTime 1000
#define PuppyTime 4000
/*******************************************************************************
 * DEBUGPRINT                                               *
 ******************************************************************************/
#ifdef DEBUGPRINT
#include <stdio.h>
#endif

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
#ifdef USEPING
typedef enum {
    InitPSubState,
	BackUp, 
	Right1,
	Forward1,
	Left1,
	Forward2,
	Left2,
	Right2,
	Forward3,
} AvoidObstacleSubHSMState_t;

static const char *StateNames[] = {
	"InitPSubState",
	"BackUp",
	"Right1",
	"Forward1",
	"Left1",
	"Forward2",
	"Left2",
	"Right2",
	"Forward3",
};



static const char *StateNames[] = {
	"InitPSubState",
	"BackUp",
	"Right1",
	"Forward1",
	"Left1",
	"Forward2",
	"Left2",
	"Right2",
	"Forward3",
};
#else
typedef enum {
    InitPSubState,
	BackUp, 
	TurnL,
	DriftR,
    TankR,
	BackL,
} AvoidObstacleSubHSMState_t;

static const char *StateNames[] = {
	"InitPSubState",
	"BackUp", 
	"TurnL",
	"DriftR",
    "TankR",
	"BackL",
};
#endif

static AvoidObstacleSubHSMState_t CurrentState = InitPSubState; // <- change name to match ENUM
static uint8_t MyPriority;


/*******************************************************************************
 * PUBLIC FUNCTIONS                                                            *
 ******************************************************************************/

/**
 * @Function InitAvoidObstacleSubHSM(uint8_t Priority)
 * @param Priority - internal variable to track which event queue to use
 * @return TRUE or FALSE
 * @brief This will get called by the framework at the beginning of the code
 *        execution. It will post an ES_INIT event to the appropriate event
 *        queue, which will be handled inside RunAvoidObstacleFSM function. Remember
 *        to rename this to something appropriate.
 *        Returns TRUE if successful, FALSE otherwise
 * @author J. Edward Carryer, 2011.10.23 19:25 */
uint8_t InitAvoidObstacleSubHSM(void)
{
    ES_Event returnEvent;

    CurrentState = InitPSubState;
    returnEvent = RunAvoidObstacleSubHSM(INIT_EVENT);
    if (returnEvent.EventType == ES_NO_EVENT) {
        return TRUE;
    }
    return FALSE;
}

/**
 * @Function RunAvoidObstacleSubHSM(ES_Event ThisEvent)
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
ES_Event RunAvoidObstacleSubHSM(ES_Event ThisEvent)
{

    uint8_t makeTransition = FALSE; // use to flag transition
    AvoidObstacleSubHSMState_t nextState; // <- change type to correct enum

    ES_Tattle(); // trace call stack
    switch (CurrentState) { //This obnoxiously long switch statement written by ChatGPT.
    case InitPSubState: // If current state is initial Psedudo State
        if (ThisEvent.EventType == ES_INIT)// only respond to ES_Init
        {
            // this is where you would put any actions associated with the
            // transition from the initial pseudo-state into the actual
            // initial state

            // now put the machine into the actual initial state
            nextState = BackUp;
            makeTransition = TRUE;
            ThisEvent.EventType = ES_NO_EVENT;
        }
        break;
        case BackUp:
            switch(ThisEvent.EventType){
                case ES_ENTRY:
                    MOTOR_TATTLE(-100, -100)
                    Maw_LeftMtrSpeed(-100);
                    Maw_RightMtrSpeed(-100);
                    ES_Timer_InitTimer(AVOID_OBSTACLE_TIMER, BackUpETime);

                    break;
                case BUMPER:
                    if(!ThisEvent.EventParam){
                        ES_Timer_InitTimer(AVOID_OBSTACLE_TIMER, BackUpTime);
                    }
                    break;
                case ES_TIMEOUT:
                    if(ThisEvent.EventParam == AVOID_OBSTACLE_TIMER){
                        makeTransition = TRUE;
                        nextState = TurnL;
                        ThisEvent = NO_EVENT;
                    }
            }
            break;
        case TurnL:
            switch(ThisEvent.EventType){
                case ES_ENTRY:
                    MOTOR_TATTLE(-100, 100)
                    Maw_LeftMtrSpeed(-100);
                    Maw_RightMtrSpeed(100);
                    ES_Timer_InitTimer(AVOID_OBSTACLE_TIMER, TurnLTime);
                    break;
                case ES_TIMEOUT:
                    if(ThisEvent.EventParam == AVOID_OBSTACLE_TIMER){
                        makeTransition = TRUE;
                        nextState = DriftR;
                        ThisEvent = NO_EVENT;
                    }
            }
            break;
        case DriftR:
            switch (ThisEvent.EventType)
            {
            case ES_ENTRY:
                    MOTOR_TATTLE(100, 70)
                    Maw_LeftMtrSpeed(100);
                    Maw_RightMtrSpeed(70);
                    ES_Timer_InitTimer (AVOID_OBSTACLE_TIMER,DriftRTime);
                    ES_Timer_InitTimer(AVOID_WATCH_PUPPY_TIMER, PuppyTime);
                break;
            case BUMPER:
                // only turn into backleft is a bumper is pressed down
                if (ThisEvent.EventParam)
                {
                    makeTransition = TRUE;
                    nextState = BackL;
                    ThisEvent = NO_EVENT;
                }
            case TAPE:
             // if the front Tape sensors are detected at all it OMW *should* be able to handle
             // any odd issues if this is the case reset
             if (ThisEvent.EventParam & ((1<<TAPEfrrBit)|(1<<TAPEfrBit)|(1<<TAPEflBit)
             |(1<<TAPEfllBit)))
             {
                    makeTransition = TRUE;
                    nextState = BackUp;
                    ThisEvent.EventType = OBSTACLE_AVOIDED;
                    ThisEvent.EventParam = TRUE;
             }
             case ES_TIMEOUT:
                    if(ThisEvent.EventParam == AVOID_WATCH_PUPPY_TIMER){
                        makeTransition = TRUE;
                        nextState = BackL;
                        ThisEvent = NO_EVENT;
                        ES_Timer_InitTimer(AVOID_OBSTACLE_TIMER, BackLTime);
                    }
                    else if (ThisEvent.EventParam == AVOID_OBSTACLE_TIMER){
                        makeTransition = TRUE;
                        nextState = TankR;
                        ThisEvent = NO_EVENT;
                    }
            default:
                break;
            }
            break;
        case TankR:
            switch(ThisEvent.EventType){
                case ES_ENTRY:
                    MOTOR_TATTLE(-100, 100)
                    Maw_RightMtrSpeed(-100);
                    Maw_LeftMtrSpeed(100);
                    ES_Timer_InitTimer(AVOID_OBSTACLE_TIMER, TankRTime);
                    break;
                case ES_TIMEOUT:
                    if(ThisEvent.EventParam == AVOID_WATCH_PUPPY_TIMER){
                        makeTransition = TRUE;
                        nextState = BackL;
                        ThisEvent = NO_EVENT;
                        ES_Timer_InitTimer(AVOID_OBSTACLE_TIMER, BackLTime);
                    }
                    else if (ThisEvent.EventParam == AVOID_OBSTACLE_TIMER){
                        makeTransition = TRUE;
                        nextState = BackL;
                        ThisEvent = NO_EVENT;
                        ES_Timer_InitTimer(AVOID_OBSTACLE_TIMER, BackLTime);
                    }
                break;
            }
            break;
        case BackL:
            switch(ThisEvent.EventType){
                case ES_ENTRY:
                    MOTOR_TATTLE(-100, 0)
                    Maw_LeftMtrSpeed(-100);
                    Maw_RightMtrSpeed(0);
                    break;
                case BUMPER:
                    if(!ThisEvent.EventParam){
                        ES_Timer_InitTimer(AVOID_OBSTACLE_TIMER, BackLTime);
                    }
                    break;
                case ES_TIMEOUT:
                    if(ThisEvent.EventParam == AVOID_OBSTACLE_TIMER){
                        makeTransition = TRUE;
                        nextState = DriftR;
                        ThisEvent = NO_EVENT;
                    }
                    break;
                default: // all unhandled states fall into here
                    break;
            }
        break;
    } // end switch on Current State

    if (makeTransition == TRUE) { // making a state transition, send EXIT and ENTRY
        // recursively call the current state with an exit event
        RunAvoidObstacleSubHSM(EXIT_EVENT); // <- rename to your own Run function
        CurrentState = nextState;
        RunAvoidObstacleSubHSM(ENTRY_EVENT); // <- rename to your own Run function
    }

    ES_Tail(); // trace call stack end
    return ThisEvent;
}


/*******************************************************************************
 * PRIVATE FUNCTIONS                                                           *
 ******************************************************************************/

