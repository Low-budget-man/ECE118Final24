/*
 * File: RammingSubHSM.c
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
#include "maw.h"
#include "SensorEventChecker.h"
#include "BOARD.h"
#include "RammingSubHSM.h"
#include "IO_Ports.h"

/*******************************************************************************
 * MODULE #DEFINES                                                             *
 ******************************************************************************/
typedef enum {
    InitPSubState,
	Align,
    BackUp,
	FirstDoor,
	SecondDoor,
	Charge,
	Wait,
	Back2,
	Return2Arena,
} RammingSubHSMState_t;

static const char *StateNames[] = {
	"InitPSubState",
	"Align",
	"BackUp",
	"FirstDoor",
	"SecondDoor",
	"Charge",
	"Wait",
	"Back2",
	"Return2Arena",
};

#define ALIGN_TIME 1000
//back up default 1000
#define BACKUP_TIME 2000
// #define RAM_TIME 10
#define DOOR_TIME 200
#define WAIT_TIME 500
#define BACKUP2_TIME 1500
#define RETURN_TIME 2400

#define FAN_PORT PORTZ
#define FAN_PIN PIN9
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

static RammingSubHSMState_t CurrentState = InitPSubState; // <- change name to match ENUM
static uint8_t MyPriority;


/*******************************************************************************
 * PUBLIC FUNCTIONS                                                            *
 ******************************************************************************/

/**
 * @Function InitRammingSubHSM(uint8_t Priority)
 * @param Priority - internal variable to track which event queue to use
 * @return TRUE or FALSE
 * @brief This will get called by the framework at the beginning of the code
 *        execution. It will post an ES_INIT event to the appropriate event
 *        queue, which will be handled inside RunTemplateFSM function. Remember
 *        to rename this to something appropriate.
 *        Returns TRUE if successful, FALSE otherwise
 * @author J. Edward Carryer, 2011.10.23 19:25 */
uint8_t InitRammingSubHSM(void)
{
    ES_Event returnEvent;

    CurrentState = InitPSubState;
    returnEvent = RunRammingSubHSM(INIT_EVENT);
    if (returnEvent.EventType == ES_NO_EVENT) {
        return TRUE;
    }
    return FALSE;
}

/**
 * @Function RunRammingSubHSM(ES_Event ThisEvent)
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
ES_Event RunRammingSubHSM(ES_Event ThisEvent)
{
    uint8_t makeTransition = FALSE; // use to flag transition
    RammingSubHSMState_t nextState; // <- change type to correct enum

    ES_Tattle(); // trace call stack
	//The following switch statement written by ChatGPT, because I'm lazy/exhausted. -Max
    switch (CurrentState) {
		case InitPSubState: // If current state is initial Psedudo State
        if (ThisEvent.EventType == ES_INIT)// only respond to ES_Init
        {
            // this is where you would put any actions associated with the
            // transition from the initial pseudo-state into the actual
            // initial state
            // INIT the fans       
            // now put the machine into the actual initial state
            nextState = Align;
            makeTransition = TRUE;
            ThisEvent.EventType = ES_NO_EVENT;
        }
        break;
		
		case Align:
			switch (ThisEvent.EventType) {
                case ES_ENTRY: //Guessing here. 
                    MOTOR_TATTLE(100, 100)
                    Maw_LeftMtrSpeed(100);
                    Maw_RightMtrSpeed(100);
                    ES_Timer_InitTimer(RAM_TIMER, ALIGN_TIME);
                    break;
                case ES_TIMEOUT: //More of a watchdog than anything
                    if (ThisEvent.EventParam == RAM_TIMER){
                        nextState = BackUp;
                        makeTransition = TRUE;
                        ThisEvent.EventType = ES_NO_EVENT;
                    }
                    break;
                    
                case ES_NO_EVENT:
                    break;
                default:
                // Unhandled events pass back up to the next level
                break;
            }
            break;		
        case BackUp:
            switch (ThisEvent.EventType) {
				case ES_ENTRY:
                    MOTOR_TATTLE(-100, -100)
					Maw_LeftMtrSpeed(-100);
					Maw_RightMtrSpeed(-100);
					ES_Timer_InitTimer(RAM_TIMER, BACKUP_TIME);
					break;
                case ES_TIMEOUT:
					if (ThisEvent.EventParam == RAM_TIMER){
						nextState = FirstDoor;
						makeTransition = TRUE;
						ThisEvent.EventType = ES_NO_EVENT;
                        printf("\r\nLeaving backup on a timeout");
					}
                    break;
                case BUMPER:
					if (ThisEvent.EventParam){//check if a bumper is on
						nextState = FirstDoor;
						makeTransition = TRUE;
						ThisEvent.EventType = ES_NO_EVENT;
                        ES_Timer_StopTimer(RAM_TIMER);
                        printf("\r\nLeaving backup on a bumper");
					}
                    break;
                case ES_NO_EVENT:
                default:
                    // Unhandled events pass back up to the next level
                    break;
            }
            break;
			
		case FirstDoor:
			switch (ThisEvent.EventType) {
				case ES_ENTRY:
					Maw_LeftDoor(FALSE);
                    Maw_Fans(1);  
					ES_Timer_InitTimer(RAM_TIMER, DOOR_TIME);
                    MOTOR_TATTLE(0, 0)
					Maw_LeftMtrSpeed(0);
					Maw_RightMtrSpeed(0);
					break;
                case ES_TIMEOUT:
					if (ThisEvent.EventParam == RAM_TIMER){
						nextState = SecondDoor;
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
		case SecondDoor:	//Continue moving back in this state, minimal delay, just so doors don't interfere.
            switch (ThisEvent.EventType) {
				case ES_ENTRY:
					Maw_RightDoor(FALSE);
					ES_Timer_InitTimer(RAM_TIMER, DOOR_TIME);
					break;
                case ES_TIMEOUT:
					if (ThisEvent.EventParam == RAM_TIMER){
						nextState = Charge;
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

        case Charge:
            switch (ThisEvent.EventType) {
				case ES_ENTRY:
                    //Turn On Fans  
					// ES_Timer_InitTimer(RAM_TIMER, RAM_TIME);
                    MOTOR_TATTLE(110, 110)
                    Maw_MaxMtr(TRUE);
					break;			
				case BUMPER: //Stop instead of trying to plow through wall
                    if(ThisEvent.EventParam){
                        nextState = Wait;
                        makeTransition = TRUE;
                        ThisEvent.EventType = ES_NO_EVENT;
                        ES_Timer_StopTimer(RAM_TIMER);
                    }
                    break;
                case ES_NO_EVENT:
                default:
                    // Unhandled events pass back up to the next level
                    break;
            }
            break;

        case Wait:
            switch (ThisEvent.EventType) {
				case ES_ENTRY://No fan function yet
					ES_Timer_InitTimer(RAM_TIMER, WAIT_TIME);
                    MOTOR_TATTLE(0, 0)
					Maw_LeftMtrSpeed(0);
					Maw_RightMtrSpeed(0);
					break;
                case ES_TIMEOUT:
					if (ThisEvent.EventParam == RAM_TIMER){
						nextState = Back2;
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

		case Back2:
			switch (ThisEvent.EventType) {
				case ES_ENTRY:
                    MOTOR_TATTLE(-60, -100)
					Maw_LeftMtrSpeed(-60);
					Maw_RightMtrSpeed(-100);
                    Maw_Fans(0);    
					ES_Timer_InitTimer(RAM_TIMER, BACKUP2_TIME);
                    Maw_LeftDoor(1);
					break;
                case TAPE:
                case ES_TIMEOUT:
					if (ThisEvent.EventParam == RAM_TIMER){
						nextState = Return2Arena;
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
		case Return2Arena:
			switch (ThisEvent.EventType) {
				case ES_ENTRY:
                    MOTOR_TATTLE(0, 100)
					Maw_LeftMtrSpeed(0);
					Maw_RightMtrSpeed(100);
					ES_Timer_InitTimer(RAM_TIMER, RETURN_TIME);
                    Maw_RightDoor(1);
					break;
                case ES_TIMEOUT:
					if (ThisEvent.EventParam == RAM_TIMER){
						nextState = Align;
						makeTransition = TRUE;
						ThisEvent.EventType = DEPOSITED;
					}
                    break;
                case ES_EXIT:
                    MOTOR_TATTLE(0, 0)
					Maw_LeftMtrSpeed(0);
					Maw_RightMtrSpeed(0);
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
        RunRammingSubHSM(EXIT_EVENT); // <- rename to your own Run function
        if(nextState == FirstDoor){printf("\r\nleaving backup");}
        CurrentState = nextState;
        RunRammingSubHSM(ENTRY_EVENT); // <- rename to your own Run function
    }

    ES_Tail(); // trace call stack end
    return ThisEvent;
}


/*******************************************************************************
 * PRIVATE FUNCTIONS                                                           *
 ******************************************************************************/

