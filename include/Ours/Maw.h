/*
 * File:   Maw.h
 * Author: Cooper Cantrell
 *
 * Created on May 16, 2024, 5/16/2024 AM
 * Implements basic functionality for Maw robot motors and movement
 */

#ifndef MAW_H
#define MAW_H

#include <BOARD.h>
#include <stdio.h>
#include "ES_Timers.h"
#include "DoorService.h"
/*******************************************************************************
 * PUBLIC DEFINES PROTOTYPES                                                  *
 ******************************************************************************/
// This is in Volts
#define MAX_MOTOR_VOLTAGE 8 
// the motor Bias is a number that will be multiplied to the motors as you set the speed, keep between 0-1
#define RIGHT_BIAS .998
#define LEFT_BIAS .968
//#define MOTORTATTLE
#ifdef MOTORTATTLE
#define MOTOR_TATTLE(l, r) Motor_Tattle(__FUNCTION__, l, r);
#else
#define MOTOR_TATTLE(l, r)
#endif


/*******************************************************************************
 * PUBLIC FUNCTION PROTOTYPES                                                  *
 ******************************************************************************/
#ifdef MOTORTATTLE
void Motor_Tattle(const char* func, int16_t left, int16_t right);
#endif
/**
 * @Function Maw_Init(void)
 * @param None.
 * @return None.
 * @brief  Performs all the initialization necessary for the Maw. this includes initializing
 * the PWM module, the A/D converter, the data directions on some pins, and
 * setting the initial motor directions.
 * @note  None.
 * @author Cooper Cantrell, 2024.5.16 */
void Maw_Init(void);


/**
 * @Function Maw_LeftMtrSpeed(char newSpeed)
 * @param newSpeed - A value between -100 and 100 which is the new speed
 * @param of the motor. 0 stops the motor. A negative value is reverse.
 * @return SUCCESS or ERROR
 * @brief  This function is used to set the speed and direction of the left motor.
 * @modified Cooper Cantrell 2024.5.21 
 * Changed to have the battery voltage edit the behavor
 * @author Caitlin Bonesio, 2024.5.16 */
char Maw_LeftMtrSpeed(char newSpeed);

/**
 * @Function Maw_RightMtrSpeed(char newSpeed)
 * @param newSpeed - A value between -100 and 100 which is the new speed
 * @param of the motor. 0 stops the motor. A negative value is reverse.
 * @return SUCCESS or ERROR
 * @brief  This function is used to set the speed and direction of the left motor.
 * @modified Cooper Cantrell 2024.5.21 
 * Changed to have the battery voltage edit the behavor
 * @author Caitlin Bonesio, 2024.5.16 */
char Maw_RightMtrSpeed(char newSpeed);

/**
 * @Function Maw_MaxMtr(uint8_t Dir)
 * @param Dir - a true for forward or false for reverse
 * @return SUCCESS or ERROR
 * @brief  This function sets both motors to their max speed forward, regardless of battery voltage
 * @author Caitlin Bonesio, 2024.6.3 */
char Maw_MaxMtr(uint8_t dir);

/**
 * @Function Maw_RightDoor(uint8_t Position)
 * @param Position - a true for collect or false for deposit a param > 1 = blocking
 * @return SUCCESS or ERROR
 * @brief  This function is used to open and close the 
 * @note Because of how the servos are on the bot there it seems like it is 
 * going to the wrong spot this is to abstract away how the servos are mounted
 * @modifyed 5/29/2024
 * @mod able to give a number larger than 1 to enter a block pos
 * @author Cooper Cantrell, 2024.5.16 */
char Maw_RightDoor(uint16_t Position);

/**
 * @Function Maw_LeftDoor(uint8_t Position)
 * @param Position - a true for collect or false for deposit a param > 1 = blocking
 * @return SUCCESS or ERROR
 * @brief  This function is used to open and close the 
 * @note Because of how the servos are on the bot there it seems like it is 
 * going to the wrong spot this is to abstract away how the servos are mounted
 * @modifyed 5/29/2024
 * @mod able to give a number larger than 1 to enter a block pos
 * @author Cooper Cantrell, 2024.5.16 */
char Maw_LeftDoor(uint16_t Position);

/**
 * @Function Maw_Doors(DOOR Input)
 * @param Input - a DOOR enum that is open closed or deposit
 * @return none
 * @brief  This function will be used to set the doors of the bot async  
 * @note this calls the doors service to set the doors into the wanted config 
 * @author Cooper Cantrell, 2024.6.5 */
void Maw_Doors(DOOR Input);

/**
 * @Function Maw_Fans(uint8_t power)
 * @param power - a bool true if on 0 if off
 * @return none
 * @brief  This function is used to turn on and off the fans
 * @author Cooper Cantrell, 2024.6.3 */
void Maw_Fans(uint8_t power);
#endif
