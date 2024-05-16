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

/*******************************************************************************
 * PRIVATE #DEFINES                                                            *
 ******************************************************************************/

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
void Maw_Init(void);


/**
 * @Function Maw_LeftMtrSpeed(char newSpeed)
 * @param newSpeed - A value between -100 and 100 which is the new speed
 * @param of the motor. 0 stops the motor. A negative value is reverse.
 * @return SUCCESS or ERROR
 * @brief  This function is used to set the speed and direction of the left motor.
 * @author Cooper Cantrell, 2024.5.16 */
char Maw_LeftMtrSpeed(char newSpeed);

/**
 * @Function Maw_RightMtrSpeed(char newSpeed)
 * @param newSpeed - A value between -100 and 100 which is the new speed
 * @param of the motor. 0 stops the motor. A negative value is reverse.
 * @return SUCCESS or ERROR
 * @brief  This function is used to set the speed and direction of the left motor.
 * @author Cooper Cantrell, 2024.5.16 */
char Maw_RightMtrSpeed(char newSpeed);

