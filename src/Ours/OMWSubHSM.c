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
//#define PuppyTime 3000
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

ES_Event RunOMWSubHSM(ES_Event ThisEvent){
  //printf("\r\n OMW post %s, param %d",EventNames[ThisEvent.EventType],ThisEvent.EventParam);
    static uint8_t guideBackFlag = 0;
    if(ThisEvent.EventType == ES_ENTRY){
        MOTOR_TATTLE(100, 100)
        Maw_LeftMtrSpeed(100);
        Maw_RightMtrSpeed(100);
        guideBackFlag = 0;
    }
    if(ThisEvent.EventType == TAPE){
#ifdef PuppyTime
        ES_Timer_InitTimer(OMW_PUPPY,PuppyTime);
#endif
        ThisEvent.EventType = ES_NO_EVENT;
        //GuideTapes is a two bit number, the left bit is if TAPEfr is on and the Right bit is if TAPEfrr is on
        uint8_t GuideTapes = (((ThisEvent.EventParam & (1 << TAPEfrrBit)) >> (TAPEfrrBit)) | (((ThisEvent.EventParam & (1 << TAPEfrBit)) >> (TAPEfrBit-1))));
        //printf("\r\nguideTapes %X, gbf: %d", GuideTapes, guideBackFlag);
        switch (GuideTapes){
            case 0b00://left is off and right is off: turn right
                MOTOR_TATTLE(100, 60)
                Maw_LeftMtrSpeed(100);
                Maw_RightMtrSpeed(0);
                // this is for testing may allow us to catch a 
                //few more balls
                //printf("\r\nleft is off and right is off: turn right\r\n");
                break;
            case 0b01://left is off and right is on: on track go forward
                MOTOR_TATTLE(100, 100)
                Maw_LeftMtrSpeed(100);
                Maw_RightMtrSpeed(100);
                guideBackFlag = 0;
                //printf("\r\nleft is off and right is on: on track go forward\r\n");
                break;
            case 0b10://left is on and right is off: unexpected, assume way to far left turn hard Left (was panic mode)
                //I've chosen to not have the robot move forward during this as the assumption may be wrong in which case it would drive itself off the edge
                MOTOR_TATTLE(-50, 100)
                Maw_LeftMtrSpeed(-50);
                Maw_RightMtrSpeed(100);
                guideBackFlag = 0;
                //printf("\r\nleft is on and right is off: Panic!\r\n");
                break;
            case 0b11://Left is on and right is on: fully on tape turn left
                MOTOR_TATTLE(0, 100)
                Maw_LeftMtrSpeed(0);
                Maw_RightMtrSpeed(100);
                guideBackFlag = 0;
                //printf("\r\nLeft is on and right is on: fully on tape turn left\r\n");
                break;
        }
        
        //this code overwrites any previous motor sets, used when the bot is almost over the edge
        if((ThisEvent.EventParam & ((1<<TAPEfllBit) | (1<<TAPEflBit) | (1<<TAPEblBit) )) || guideBackFlag){
            
            guideBackFlag = 1;
            MOTOR_TATTLE(-100, 100)
            Maw_LeftMtrSpeed(-100);
            Maw_RightMtrSpeed(100);
        }
    }
    if(ThisEvent.EventType == ES_TIMEOUT && ThisEvent.EventParam == OMW_PUPPY){
        ThisEvent.EventType = BUMPER;
        ThisEvent.EventParam = 0xf;
        return ThisEvent;
    }
    return ThisEvent;
}
        

/*******************************************************************************
 * PRIVATE FUNCTIONS                                                           *
 ******************************************************************************/
