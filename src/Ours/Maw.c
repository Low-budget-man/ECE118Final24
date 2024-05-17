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
#include "RC_Servo.h"

/*******************************************************************************
 * PRIVATE #DEFINES                                                            *
 ******************************************************************************/
#define MawTest


#define PWMFRQ 1000
#define RIGHT_MOTOR PWM_PORTY12
#define LEFT_MOTOR PWM_PORTZ06
#define RIGHT_DIR1 PORTY,PIN11
// was pin 9 but that seems to not work
#define RIGHT_DIR2 PORTY,PIN5
#define LEFT_DIR1 PORTZ,PIN5
#define LEFT_DIR2 PORTZ,PIN4
// when Dir1 = 1 and Dir2 = 0 that is forward
#define RIGHT_DOOR RC_PORTY06
#define LEFT_DOOR RC_PORTY07
#define OPEN MAXPULSE
#define CLOSED MINPULSE


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
 * @author Cooper Cantrell & Caitlin Bonesio, 2024.5.16 */
void Maw_Init(void){
    // Setting up the PWM in the same way that the roach was 
    PWM_Init();
    PWM_SetFrequency(PWMFRQ);
    PWM_AddPins(LEFT_MOTOR | RIGHT_MOTOR);
    // init the sensors
    SensorInit();
    //set up servos
    RC_Init();
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
    // for the servos
    RC_Init();
    RC_AddPins(RIGHT_DOOR|LEFT_DOOR);
}


/**
 * @Function Maw_LeftMtrSpeed(char newSpeed)
 * @param newSpeed - A value between -100 and 100 which is the new speed
 * @param of the motor. 0 stops the motor. A negative value is reverse.
 * @return SUCCESS or ERROR
 * @brief  This function is used to set the speed and direction of the left motor.
 * @author Caitlin Bonesio, 2024.5.16 */
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
    return SUCCESS;
}

/**
 * @Function Maw_RightMtrSpeed(char newSpeed)
 * @param newSpeed - A value between -100 and 100 which is the new speed
 * @param of the motor. 0 stops the motor. A negative value is reverse.
 * @return SUCCESS or ERROR
 * @brief  This function is used to set the speed and direction of the left motor.
 * @author Caitlin Bonesio, 2024.5.16 */
char Maw_RightMtrSpeed(char newSpeed){
    if(newSpeed < 0){
        IO_PortsSetPortBits(RIGHT_DIR2);
        IO_PortsClearPortBits(RIGHT_DIR1);
        newSpeed *= -1;
        printf("\r\n Setting speed to %d",newSpeed);
    } else if (newSpeed > 0){
        IO_PortsSetPortBits(RIGHT_DIR1);
        IO_PortsClearPortBits(RIGHT_DIR2);
    // may need to be removed if breaking too hard
    } else {
        IO_PortsClearPortBits(RIGHT_DIR1);
        IO_PortsClearPortBits(RIGHT_DIR2);
    }
    PWM_SetDutyCycle(RIGHT_MOTOR, newSpeed*10);
    return SUCCESS;
}

/**
 * @Function Maw_RightDoor(uint8_t Position)
 * @param Position - a true or false value for OPEN or CLOSED
 * @return SUCCESS or ERROR
 * @brief  This function is used to open and close the doors
 * @author Cooper Cantrell, 2024.5.16 */
char Maw_RightDoor(uint8_t Position){
    if(Position){
        RC_SetPulseTime(RIGHT_DOOR,OPEN);
    }
    else{
        RC_SetPulseTime(RIGHT_DOOR,CLOSED);
    }
    return SUCCESS;
}

/**
 * @Function Maw_LeftDoor(uint8_t Position)
 * @param Position - a true or false value for OPEN or CLOSED
 * @return SUCCESS or ERROR
 * @brief  This function is used to open and close the doors
 * @author Cooper Cantrell, 2024.5.16 */
char Maw_LeftDoor(uint8_t Position){
    if(Position){
        RC_SetPulseTime(LEFT_DOOR,OPEN);
    }
    else{
        RC_SetPulseTime(LEFT_DOOR,CLOSED);
    }
    return SUCCESS;
}

#ifdef MawTest
#include <stdio.h>
int wait;
#define DELAY(x)    for (wait = 0; wait <= x; wait++) {asm("nop");}
#define A_BIT       183000
#define A_BIT_MORE  366000
#define YET_A_BIT_LONGER (A_BIT_MORE<<2)
#define A_LOT       1830000
int main(void){
    BOARD_Init();
    printf("Maw Test code for the moving parts will begin shortly");
    Maw_Init();
    DELAY(A_BIT);
    printf("\r\n Test 1 Right motor");
    DELAY(A_BIT);
    printf("\r\n Right Motor Speed 50");
    Maw_RightMtrSpeed(50);
    DELAY(YET_A_BIT_LONGER);
    printf("\r\n Right Motor Speed 100");
    Maw_RightMtrSpeed(100);
    DELAY(YET_A_BIT_LONGER);
    printf("\r\n Right Motor Speed -50");
    Maw_RightMtrSpeed(-50);
    DELAY(YET_A_BIT_LONGER);
    printf("\r\n Right Motor Speed -100");
    Maw_RightMtrSpeed(-100);
    DELAY(YET_A_BIT_LONGER);
    Maw_RightMtrSpeed(0);
    printf("\r\n Testing of the right motor done ");
    DELAY(A_BIT_MORE);
    printf("\r\n Test 2 Left motor");
    DELAY(A_BIT);
    printf("\r\n Left Motor Speed 50");
    Maw_LeftMtrSpeed(50);
    DELAY(YET_A_BIT_LONGER);
    printf("\r\n Left Motor Speed 100");
    Maw_LeftMtrSpeed(100);
    DELAY(YET_A_BIT_LONGER);
    printf("\r\n Left Motor Speed -50");
    Maw_LeftMtrSpeed(-50);
    DELAY(YET_A_BIT_LONGER);
    printf("\r\n Left Motor Speed -100");
    Maw_LeftMtrSpeed(-100);
    DELAY(YET_A_BIT_LONGER);
    Maw_LeftMtrSpeed(0);
    printf("\r\n Testing of the left motor done ");
    DELAY(A_BIT_MORE);
    printf("\r\n Test 3 right servo");
    DELAY(A_BIT);
    printf("\r\n OPEN");
    Maw_RightDoor(TRUE);
    DELAY(YET_A_BIT_LONGER);
    printf("\r\n CLOSE");
    Maw_RightDoor(FALSE);
    DELAY(YET_A_BIT_LONGER);
    printf("\r\n Testing of the right servo done");
    DELAY(A_BIT_MORE);
    printf("\r\n Test 4 left servo");
    DELAY(A_BIT);
    printf("\r\n OPEN");
    Maw_LeftDoor(TRUE);
    DELAY(YET_A_BIT_LONGER);
    printf("\r\n CLOSE");
    Maw_LeftDoor(FALSE);
    DELAY(YET_A_BIT_LONGER);
    printf("\r\n Testing of the left servo done");
    DELAY(A_BIT_MORE);
    printf("\r\n All Tests Done Goodbye");
    return SUCCESS;
}
#endif
