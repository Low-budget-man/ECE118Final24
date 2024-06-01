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
/*******************************************************************************
 * PUBLIC DEFINES PROTOTYPES                                                  *
 ******************************************************************************/
// This is in Volts
#define MAX_MOTOR_VOLTAGE 8 
// the motor Bias is a number that will be multiplied to the motors as you set the speed, keep between 0-1
#define RIGHT_BIAS 1
#define LEFT_BIAS .97


/*******************************************************************************
 * PUBLIC FUNCTION PROTOTYPES                                                  *
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
 * @Function Maw_RightDoor(uint8_t Position)
 * @param Position - a true for depositing or false for collecting
 * @return SUCCESS or ERROR
 * @brief  This function is used to open and close the doors
 * @author Cooper Cantrell, 2024.5.16 */
char Maw_RightDoor(uint8_t Position);

/**
 * @Function Maw_LeftDoor(uint8_t Position)
 * @param Position - a true for depositing or false for collecting
 * @return SUCCESS or ERROR
 * @brief  This function is used to open and close the doors
 * @author Cooper Cantrell, 2024.5.16 */
char Maw_LeftDoor(uint8_t Position);

#endif
