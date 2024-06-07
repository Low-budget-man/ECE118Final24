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
#include "LED.h"
#include <stdio.h>
#include "ES_Configure.h"
#include "ES_Events.h"

/*******************************************************************************
 * PRIVATE #DEFINES                                                            *
 ******************************************************************************/
#define BAD_READ
//#define ONLY_SERVOS
//#define MawTest
//NOTE : PING ECHO = y8
// PING trigger = y10
#define PWMFRQ 1000

//Motor is outside in: pwm/dir/dir
#define RIGHT_MOTOR PWM_PORTY12
#define LEFT_MOTOR PWM_PORTZ06
#define RIGHT_DIR1 PORTY,PIN11
// was pin 9 but that seems to not work
#define RIGHT_DIR2 PORTY,PIN6
#define LEFT_DIR1 PORTZ,PIN5
#define LEFT_DIR2 PORTZ,PIN4
// when Dir1 = 1 and Dir2 = 0 that is forward
// fans 
#define FANs PORTZ, PIN7
//Servo: Brn/red/orn is gnd/pwr/sig
#define RIGHT_DOOR RC_PORTZ08
#define LEFT_DOOR RC_PORTY07
// macro to read the battery voltage 
#define CURRENT_BATT_VOLT AD_ReadADPin(BAT_VOLTAGE)
// for max power
#define MAXPOWER
#define OPEN 725
#define CLOSE 1500
// for the collecting drum
//#define DRUM_BACKWARDS
#define DRUM_DIR1 PORTZ,PIN9
#define DRUM_DIR2 PORTZ,PIN3
/*******************************************************************************
 * PRIVATE VARIABLES                                                           *
 ******************************************************************************/

/*******************************************************************************
 * PRIVATE FUNCTIONS                                                           *
 ******************************************************************************/

/**
 * @Function ScaleValue(char newSpeed)
 * @param newSpeed - A value between 0 and 100 which is the abs of new speed 
 * @param of the motor. and scales it dependent on the battery reading 
 * @return the properly scaled value that will go into the setPWM function
 * @brief  This functon will be used to scale 
 * @author Cooper Cantrell, 2024.5.21 */
 unsigned int ScaleValue(char newSpeed){
    // convert the Max motor voltage (8V) to the same 32 mV units of the output
    // of the read pin function
#ifndef MAXPOWER
    float mathSpeed = newSpeed;
    float maxV = (MAX_MOTOR_VOLTAGE) * 31;
    float CurrentV = (float) CURRENT_BATT_VOLT;
#ifdef BAD_READ
    CurrentV = 9.95 * 31; //this should be approx 10V
#endif
    unsigned int out = 0;
    if(CurrentV < maxV){
        out = 0;
        printf("\r\n ERROR ERROR---BATT VOLTAGE TOO LOW TO RUN [%d]---ERROR ERROR",CURRENT_BATT_VOLT);
    }
    else{
        out = (unsigned int) ((10*mathSpeed * maxV)/CurrentV);
    }
    if(out < 0 ){
        printf("warning motors have been under set, moving within bounds");
        out = 0;
    } else if(out > 1000){
        printf("warning motors have been over set, moving within bounds");
        out = 1000;
    }
        return out;
#else
return newSpeed * 10;
#endif

     
    //issues with battery reading motor for now
    //return newSpeed* 10;
}
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
    //inits the fans
    IO_PortsSetPortOutputs(FANs);
    IO_PortsClearPortBits(FANs);
    // for the servos
    RC_Init();
    RC_AddPins(RIGHT_DOOR|LEFT_DOOR);
    // SET up the LEDs
    LED_Init();
    LED_AddBanks(LED_BANK1);
    LED_OffBank(LED_BANK1, 0xf);
    //sets up the Drum
    IO_PortsSetPortOutputs(DRUM_DIR1);
    IO_PortsSetPortOutputs(DRUM_DIR2);
    IO_PortsSetPortBits(DRUM_DIR1);
    IO_PortsSetPortBits(DRUM_DIR2);
    Maw_Drum(TRUE);
}


/**
 * @Function Maw_LeftMtrSpeed(char newSpeed)
 * @param newSpeed - A value between -100 and 100 which is the new speed
 * @param of the motor. 0 stops the motor. A negative value is reverse.
 * @return SUCCESS or ERROR
 * @brief  This function is used to set the speed and direction of the left motor.
 * @author Caitlin Bonesio, 2024.5.16 */
char Maw_LeftMtrSpeed(char newSpeed){
    newSpeed *= LEFT_BIAS;
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
    PWM_SetDutyCycle(LEFT_MOTOR, ScaleValue(newSpeed));
    return SUCCESS;
}
/**
 * @Function Maw_MaxMtr(uint8_t Dir)
 * @param Dir - a true for forward or false for reverse
 * @return SUCCESS or ERROR
 * @brief  This function sets both motors to their max speed forward, regardless of battery voltage
 * @author Caitlin Bonesio, 2024.6.3 */
char Maw_MaxMtr(uint8_t dir){
    if(dir == 0){
        IO_PortsSetPortBits(LEFT_DIR2);
        IO_PortsClearPortBits(LEFT_DIR1);
        IO_PortsSetPortBits(RIGHT_DIR2);
        IO_PortsClearPortBits(RIGHT_DIR1);
    } else {
        IO_PortsSetPortBits(LEFT_DIR1);
        IO_PortsClearPortBits(LEFT_DIR2);
        IO_PortsSetPortBits(RIGHT_DIR1);
        IO_PortsClearPortBits(RIGHT_DIR2);
    }
    PWM_SetDutyCycle(RIGHT_MOTOR, 998);
    PWM_SetDutyCycle(LEFT_MOTOR, 968);
}
/**
 * @Function Maw_RightMtrSpeed(char newSpeed)
 * @param newSpeed - A value between -100 and 100 which is the new speed
 * @param of the motor. 0 stops the motor. A negative value is reverse.
 * @return SUCCESS or ERROR
 * @brief  This function is used to set the speed and direction of the left motor.
 * @author Caitlin Bonesio, 2024.5.16 */
char Maw_RightMtrSpeed(char newSpeed){
    newSpeed *= RIGHT_BIAS;
    if(newSpeed < 0){
        IO_PortsSetPortBits(RIGHT_DIR2);
        IO_PortsClearPortBits(RIGHT_DIR1);
        newSpeed *= -1;
    } else if (newSpeed > 0){
        IO_PortsSetPortBits(RIGHT_DIR1);
        IO_PortsClearPortBits(RIGHT_DIR2);
    // may need to be removed if breaking too hard
    } else {
        IO_PortsClearPortBits(RIGHT_DIR1);
        IO_PortsClearPortBits(RIGHT_DIR2);
    }
    PWM_SetDutyCycle(RIGHT_MOTOR, ScaleValue(newSpeed));
#ifdef MOTORTATTLE
    printf("\r\nrpin1: %d-%d",LATDbits.LATD2, (IO_PortsReadPort(PORTY) & PIN6)/PIN6);
#endif
    return SUCCESS;
}

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
char Maw_RightDoor(uint16_t Position){
    
    RC_SetPulseTime(RIGHT_DOOR, Position);
    
    return SUCCESS;
}

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
char Maw_LeftDoor(uint16_t Position){
    
    RC_SetPulseTime(LEFT_DOOR, Position);
    return SUCCESS;
}
/**
 * @Function Maw_Doors(uint8_t Input)
 * @param Input - bool that true will put the poker in such a way that opens the trapdoor
 * @return none
 * @brief  This function will be used to set the doors of the bot async  
 * @note this calls the doors service to set the doors into the wanted config 
 * @author Cooper Cantrell, 2024.6.5 */
void Maw_Doors(uint8_t Input){
    if(Input){
        Maw_RightDoor(OPEN);
    }
    else
    {
        Maw_RightDoor(CLOSE);
    }
    
    
}
/**
 * @Function Maw_Fans(uint8_t power)
 * @param power - a bool true if on 0 if off
 * @return none
 * @brief  This function is used to turn on and off the fans
 * @author Cooper Cantrell, 2024.6.3 */
void Maw_Fans(uint8_t power){
    if (power)
    {
        IO_PortsSetPortBits(FANs);
    }
    else
    {
        IO_PortsClearPortBits(FANs);
    }
}

/**
 * @Function Maw_Drum(uint8_t DIR)
 * @param DIR - a bool true if Collecting deposit otherwise 
 * @return none
 * @brief  This function will switch the dir of the drum
 * @author Cooper Cantrell, 2024.6.5 */
void Maw_Drum(uint8_t DIR){
#ifdef DRUM_BACKWARDS
    DIR = !DIR;
#endif
    if(DIR){
        IO_PortsSetPortBits(DRUM_DIR1);
        IO_PortsClearPortBits(DRUM_DIR2);
    }
    else{
        IO_PortsSetPortBits(DRUM_DIR2);
        IO_PortsClearPortBits(DRUM_DIR1);
    }
}

#ifdef MOTORTATTLE
void Motor_Tattle(const char* func, int16_t left, int16_t right){
    static uint16_t LastTime;
    printf("\r\nfunc: %s, lspeed %d, rspeed %d, time %d", func, left, right, ES_Timer_GetTime() - LastTime);
    LastTime = ES_Timer_GetTime();   
}
#endif

#ifdef MawTest
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
#ifndef ONLY_SERVOS
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
#endif
//    printf("\r\n Test 3 right servo");
//    DELAY(A_BIT);
//    printf("\r\n collect");
//    Maw_RightDoor(TRUE);
//    DELAY(YET_A_BIT_LONGER);
//    printf("\r\n deposit");
//    Maw_RightDoor(FALSE);
//    DELAY(YET_A_BIT_LONGER);
//    printf("\r\n Testing of the right servo done");
//    DELAY(A_BIT_MORE);
//    printf("\r\n Test 4 left servo");
//    DELAY(A_BIT);
//    printf("\r\n collect");
//    Maw_LeftDoor(TRUE);
//    DELAY(YET_A_BIT_LONGER);
//    printf("\r\n deposit");
//    Maw_LeftDoor(FALSE);
//    DELAY(YET_A_BIT_LONGER);
//    printf("\r\n Testing of the left servo done");
//    DELAY(A_BIT_MORE);
//    printf("\r\n All Tests Done Goodbye");
    return SUCCESS;
}
#endif
