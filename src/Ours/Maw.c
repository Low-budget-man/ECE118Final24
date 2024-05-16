/*
 * File:   Maw.c
 * Author: Cooper Cantrell
 *
 * Created on May 16, 2024, 1:55 PM
 */

#include <Maw.h>
#include <BOARD.h>
#include <xc.h>
#include <pwm.h>
#include <serial.h>
#include <AD.h>
#include "SensorEventChecker.h"
#include "IO_Ports.h"

/*******************************************************************************
 * PRIVATE #DEFINES                                                            *
 ******************************************************************************/
#define PWMFRQ 1000
#define RIGHT_MOTOR PWM_PORTY12
#define LEFT_MOTOR PWM_PORTZ06
#define RIGHT_DIR1 PORTY,PIN11
#define RIGHT_DIR2 PORTY,PIN10
#define LEFT_DIR1 PORTZ,PIN5
#define LEFT_DIR2 PORTZ,PIN4
// when Dir1 = 1 that is forward
/*******************************************************************************
 * PRIVATE VARIABLES                                                           *
 ******************************************************************************/

/*******************************************************************************
 * PUBLIC FUNCTIONS                                                           *
 ******************************************************************************/

/**
 * @Function Maw_Init(void)
 * @param None.
 * @return None.
 * @brief  Performs all the initialization necessary for the Maw. this includes initializing
 * the PWM module, the A/D converter, the data directions on some pins, and
 * setting the initial motor directions.
 * @note  None.
 * @author Cooper Cantrell, 2024.5.16 */
void Maw_Init(void){
    // init the sensors
    SensorInit();
    // Setting up the PWM in the same way that the roach was 
    PWM_SetFrequency(PWMFRQ);
    PWM_AddPins(LEFT_MOTOR | RIGHT_MOTOR);
    //for dir
    IO_PortsSetPortOutputs(RIGHT_DIR1);
    IO_PortsSetPortOutputs(RIGHT_DIR2);
    IO_PortsSetPortOutputs(LEFT_DIR1);
    IO_PortsSetPortOutputs(LEFT_DIR2);
    // starts the motors at 0 speed
    IO_PortsClearPortBits(RIGHT_DIR1);
    IO_PortsClearPortBits(RIGHT_DIR2);
     IO_PortsClearPortBits(LEFT_DIR1);
    IO_PortsClearPortBits(LEFT_DIR2);
}


/**
 * @Function Maw_LeftMtrSpeed(char newSpeed)
 * @param newSpeed - A value between -100 and 100 which is the new speed
 * @param of the motor. 0 stops the motor. A negative value is reverse.
 * @return SUCCESS or ERROR
 * @brief  This function is used to set the speed and direction of the left motor.
 * @author Cooper Cantrell, 2024.5.16 */
char Maw_LeftMtrSpeed(char newSpeed){
    if(newSpeed < 0){
        IO_PortsSetPortBits(LEFT_DIR2);
        IO_PortsClearPortBits(LEFT_DIR1);
        newSpeed *= -1;
    } else if (newSpeed > 0){
        IO_PortsSetPortBits(LEFT_DIR1);
        IO_PortsClearPortBits(LEFT_DIR2);
    } else {
        IO_PortsClearPortBits(LEFT_DIR1);
        IO_PortsClearPortBits(LEFT_DIR2);
    }
    PWM_SetDutyCycle(LEFT_MOTOR, newSpeed*10);
}

/**
 * @Function Maw_RightMtrSpeed(char newSpeed)
 * @param newSpeed - A value between -100 and 100 which is the new speed
 * @param of the motor. 0 stops the motor. A negative value is reverse.
 * @return SUCCESS or ERROR
 * @brief  This function is used to set the speed and direction of the left motor.
 * @author Cooper Cantrell, 2024.5.16 */
char Maw_RightMtrSpeed(char newSpeed){
    if(newSpeed < 0){
        IO_PortsSetPortBits(RIGHT_DIR2);
        IO_PortsClearPortBits(RIGHT_DIR1);
    } else if (newSpeed > 0){
        IO_PortsSetPortBits(RIGHT_DIR1);
        IO_PortsClearPortBits(RIGHT_DIR2);
    // may need to be removed if breaking too hard
    } else {
        IO_PortsClearPortBits(RIGHT_DIR1);
        IO_PortsClearPortBits(RIGHT_DIR2);
    }
    PWM_SetDutyCycle(RIGHT_MOTOR, newSpeed*10);
}

