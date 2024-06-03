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
#include "ES_Timers.h"
#include "BOARD.h"
#include "SensorEventChecker.h"
#include "OMWSubHSM.h"
#include "Maw.h"
#include "stdio.h"

/*******************************************************************************
 * MODULE #DEFINES                                                             *
 ******************************************************************************/
//#define REALSSM
#define BRAINDEAD
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
typedef enum
{
    InitPSubState,
    Straight,
    TiltRight,
    TiltLeft,
    Panic,
#ifdef BRAINDEAD
    HardLeft,
#endif
} OMWSubHSMState_t;

static const char *StateNames[] = {
    "InitPSubState",
    "Straight",
    "TiltRight",
    "TiltLeft",
    "Panic",
#ifdef BRAINDEAD
    "HardLeft",
#endif
};

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

    CurrentState = InitPSubState;
    returnEvent = RunOMWSubHSM(INIT_EVENT);
    if (returnEvent.EventType == ES_NO_EVENT)
    {
        return TRUE;
    }
    return FALSE;
}
#ifdef REALSSM
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

    uint8_t makeTransition = FALSE; // use to flag transition
    OMWSubHSMState_t nextState;     // <- change type to correct enum

    ES_Tattle(); // trace call stack

#ifndef BRAINDEAD
    if (CurrentState == InitPSubState)
    {
        if (ThisEvent.EventType == ES_INIT) // only respond to ES_Init
        {
            // this is where you would put any actions associated with the
            // transition from the initial pseudo-state into the actual
            // initial state

            // now put the machine into the actual initial state
            nextState = Straight;
            makeTransition = TRUE;
            ThisEvent.EventType = ES_NO_EVENT;
        }
    }

    if (ThisEvent.EventType == ES_ENTRY)
    {
        switch (CurrentState)
        {
        case TiltLeft:
            Maw_LeftMtrSpeed(50);
            Maw_RightMtrSpeed(100);
            break;
        case TiltRight:
            Maw_LeftMtrSpeed(100);
            Maw_RightMtrSpeed(50);
            break;
        case Straight:
        default:
            Maw_LeftMtrSpeed(100);
            Maw_RightMtrSpeed(100);
            break;
        case Panic:
            Maw_LeftMtrSpeed(0);
            Maw_RightMtrSpeed(0);
            break;
        }
    }

    // FRR is bit 0, FR is bit 1.
    // Let's try doing this manually in case the #defines are somehow off
    if (ThisEvent.EventType == TAPE)
    {

        // Both tapes are on turn left
        if ((ThisEvent.EventParam & 0x1) && (ThisEvent.EventParam & 0x2))
        {
            if (CurrentState != TiltLeft)
            {
                nextState = TiltLeft;
                makeTransition = TRUE;
                ThisEvent.EventType = ES_NO_EVENT;
            }
        }
        else // Both tapes are off turn right
            if ((ThisEvent.EventParam & !0x1) && (ThisEvent.EventParam & !0x2))
            {
                if (CurrentState != TiltRight)
                {
                    nextState = TiltRight;
                    makeTransition = TRUE;
                    ThisEvent.EventType = ES_NO_EVENT;
                }
            }
            else // left tape on right tape off NOT EXPECTED STOPPING
                if ((ThisEvent.EventParam & 0x1) && (ThisEvent.EventParam & !0x2))
                { // Literally just moved the ! into the parens
                    if (CurrentState != Panic)
                    {
                        nextState = Panic;
                        makeTransition = TRUE;
                        ThisEvent.EventType = ES_NO_EVENT;
                    }
                }
                else // left tape off right tape on on course
                    if ((ThisEvent.EventParam & !0x1) && (ThisEvent.EventParam & 0x2))
                    {
                        if (CurrentState != Straight)
                        {
                            nextState = Straight;
                            makeTransition = TRUE;
                            ThisEvent.EventType = ES_NO_EVENT;
                        }
                    }
    }

#else
    switch (CurrentState)
    {
    case InitPSubState:
        if (ThisEvent.EventParam == ES_INIT)
        {
            // Init Stuff here

            nextState = TiltRight;
            makeTransition = TRUE;
            ThisEvent.EventType = ES_NO_EVENT;
        }

        break;
    case TiltRight:
        switch (ThisEvent.EventType)
        {
        case ES_ENTRY:
            Maw_LeftMtrSpeed(100);
            Maw_RightMtrSpeed(50);
            break;
        case TAPE:
            // sees tape
            if (ThisEvent.EventParam)
            {
                nextState = HardLeft;
                makeTransition = TRUE;
                ThisEvent.EventType = ES_NO_EVENT;
            }

        default:
            break;
        }
    case HardLeft:
        switch (ThisEvent.EventType)
        {
        case ES_ENTRY:
            Maw_RightMtrSpeed(100);
            Maw_LeftMtrSpeed(-100);
            break;
        case TAPE:
            // sees no tape
            if (!(ThisEvent.EventParam))
            {
                nextState = TiltRight;
                makeTransition = TRUE;
                ThisEvent.EventType = ES_NO_EVENT;
            }
            break;
        }

    default:
        break;
    }
#endif
    if (makeTransition == TRUE)
    { // making a state transition, send EXIT and ENTRY
        // recursively call the current state with an exit event
        RunOMWSubHSM(EXIT_EVENT); // <- rename to your own Run function
        CurrentState = nextState;
        RunOMWSubHSM(ENTRY_EVENT); // <- rename to your own Run function
    }

    ES_Tail();

    return ThisEvent;
}
#else
ES_Event RunOMWSubHSM(ES_Event ThisEvent){
    static uint8_t guideBackFlag = 0;
    if(ThisEvent.EventType == ES_ENTRY){
        Maw_LeftMtrSpeed(100);
        Maw_RightMtrSpeed(100);
        guideBackFlag = 0;
    }
    if(ThisEvent.EventType == TAPE){
        ThisEvent.EventType = ES_NO_EVENT;
        
        //GuideTapes is a two bit number, the left bit is if TAPEfr is on and the Right bit is if TAPEfrr is on
        uint8_t GuideTapes = (((ThisEvent.EventParam & 1 << TAPEfrrBit) >> (TAPEfrrBit)) | (((ThisEvent.EventParam & 1 << TAPEfrBit) >> (TAPEfrBit-1))));
        switch (GuideTapes){
            case 0b00://left is off and right is off: turn right
                Maw_LeftMtrSpeed(100);
                Maw_RightMtrSpeed(60);
                // this is for testing may allow us to catch a 
                //few more balls
                Maw_RightDoor(1);
                //printf("\r\nleft is off and right is off: turn right\r\n");
                break;
            case 0b01://left is off and right is on: on track go forward
                Maw_LeftMtrSpeed(100);
                Maw_RightMtrSpeed(100);
                Maw_RightDoor(1);
                guideBackFlag = 0;
                //printf("\r\nleft is off and right is on: on track go forward\r\n");
                break;
            case 0b10://left is on and right is off: unexpected, assume way to far left turn hard Left (was panic mode)
                //I've chosen to not have the robot move forward during this as the assumption may be wrong in which case it would drive itself off the edge
                Maw_LeftMtrSpeed(-100);
                Maw_RightMtrSpeed(100);
                Maw_RightDoor(1);
                //printf("\r\nleft is on and right is off: Panic!\r\n");
                break;
            case 0b11://Left is on and right is on: fully on tape turn left
                Maw_LeftMtrSpeed(60);
                Maw_RightMtrSpeed(100);
                Maw_RightDoor(1);
                //printf("\r\nLeft is on and right is on: fully on tape turn left\r\n");
                break;
        }
        //this code overwrites any previous motor sets, used when the bot is almost over the edge
        if((ThisEvent.EventParam & (1<<TAPEfllBit | 1<<TAPEflBit | 1<<TAPEblBit )) || guideBackFlag){
            
            guideBackFlag = 1;
            Maw_LeftMtrSpeed(-100);
            Maw_RightMtrSpeed(100);
            Maw_RightDoor(2);
        }
    }
}
        
#endif
/*******************************************************************************
 * PRIVATE FUNCTIONS                                                           *
 ******************************************************************************/
