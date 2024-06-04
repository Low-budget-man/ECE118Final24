/*******************************************************************************
 * MODULE #INCLUDE                                                             *
 ******************************************************************************/

#include "ES_Configure.h"
#include "ES_Framework.h"
#include "BOARD.h"
#include "AlignSubHSM.h"
#include "OMWSubHSM.h" 
#include "AvoidObstacleSubHSM.h" 
#include "SensorEventChecker.h"
#include "Maw.h"
/*******************************************************************************
 * PRIVATE #DEFINES                                                            *
 ******************************************************************************/
//Include any defines you need to do


/*******************************************************************************
 * MODULE #DEFINES                                                             *
 ******************************************************************************/


typedef enum {
    InitPState,
    Align,
	Forward,

} AlignHSMState_t;

static const char *StateNames[] = {
	"InitPState",
	"Align",
	"Forward",
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

static AlignHSMState_t CurrentState = InitPState; // <- change enum name to match ENUM
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
uint8_t InitAlignHSM(void)
{
    // put us into the Initial PseudoState
    CurrentState = InitPState;
    // post the initial transition event
    ES_Event ThisEvent;
    ThisEvent.EventType = ES_INIT;
    RunAlignHSM(ThisEvent);
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
ES_Event RunAlignHSM(ES_Event ThisEvent)
{
    uint8_t makeTransition = FALSE; // use to flag transition
    AlignHSMState_t nextState; // <- change type to correct enum

    ES_Tattle(); // trace call stack

    switch (CurrentState) {
    case InitPState: // If current state is initial Pseudo State
        if (ThisEvent.EventType == ES_INIT)// only respond to ES_Init
        {
            // this is where you would put any actions associated with the
            // transition from the initial pseudo-state into the actual
            // initial state
            // Initialize all sub-state machines
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
                    MOTOR_TATTLE(-80, 80)
					Maw_LeftMtrSpeed(-80);
					Maw_RightMtrSpeed(80);
                    Maw_RightDoor(2);
					break;
			case TAPE: 
				if(!(ThisEvent.EventParam & (1<<TAPEfrrBit)) && !(ThisEvent.EventParam & (1<<TAPEfrBit))){
					nextState = Forward;
					makeTransition = TRUE;
					ThisEvent.EventType = ES_NO_EVENT;
				}
                if((ThisEvent.EventParam & (1<<TAPEfrrBit)) && !(ThisEvent.EventParam & (1<<TAPEfrBit))){
                    ThisEvent.EventType = ALIGNED;
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
                    MOTOR_TATTLE(100, 100)
					Maw_LeftMtrSpeed(100);
					Maw_RightMtrSpeed(100);
					break;
			case TAPE: 
				if(!(!(ThisEvent.EventParam & (1<<TAPEfrrBit)) && !(ThisEvent.EventParam & (1<<TAPEfrBit)))){
					nextState = Align;
					makeTransition = TRUE;
					ThisEvent.EventType = ES_NO_EVENT;
				}
                if((ThisEvent.EventParam & (1<<TAPEfrrBit)) && !(ThisEvent.EventParam & (1<<TAPEfrBit))){
                    ThisEvent.EventType = ALIGNED;
                }
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
        RunAlignHSM(EXIT_EVENT); // <- rename to your own Run function
        CurrentState = nextState;
        RunAlignHSM(ENTRY_EVENT); // <- rename to your own Run function
    }

    ES_Tail(); // trace call stack end
    return ThisEvent;
}


/*******************************************************************************
 * PRIVATE FUNCTIONS                                                           *
 ******************************************************************************/

