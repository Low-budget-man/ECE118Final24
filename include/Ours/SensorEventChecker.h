/* 
 * File:   TemplateEventChecker.h
 * Author: Gabriel Hugh Elkaim
 *
 * Template file to set up typical EventCheckers for the  Events and Services
 * Framework (ES_Framework) on the Uno32 for the CMPE-118/L class. Note that
 * this file will need to be modified to fit your exact needs, and most of the
 * names will have to be changed to match your code.
 *
 * This EventCheckers file will work with simple services, FSM's and HSM's.
 *
 * Remember that EventCheckers should only return TRUE when an event has occured,
 * and that the event is a TRANSITION between two detectable differences. They
 * should also be atomic and run as fast as possible for good results.
 *
 * This is provided as an example and a good place to start.
 *
 * Created on September 27, 2013, 8:37 AM
 * Modified on September 12, 2016, 7:59 PM
 */

#ifndef SENSOREVENTCHECKER_H
#define	SENSOREVENTCHECKER_H

/*******************************************************************************
 * PUBLIC #INCLUDES                                                            *
 ******************************************************************************/

#include "ES_Configure.h"   // defines ES_Event, INIT_EVENT, ENTRY_EVENT, and EXIT_EVENT
#include "BOARD.h"

//ADDING SOMETHING TO COMMIT
/*******************************************************************************
 * PUBLIC #DEFINES                                                             *
 ******************************************************************************/
#define TAPEfrrBit (0)
#define TAPEfrBit (1)
#define TAPEflBit (2)
#define TAPEfllBit (3)
#define TAPEbrBit (4)
#define TAPEblBit (5)

#define BUMPERfrBit (1)
#define BUMPERflBit (0)
#define BUMPERbrBit (3)
#define BUMPERblBit (2)

/*******************************************************************************
 * PUBLIC TYPEDEFS                                                             *
 ******************************************************************************/


/*******************************************************************************
 * PUBLIC FUNCTION PROTOTYPES                                                  *
 ******************************************************************************/
/**
 * @Function SensorInit(void)
 * @param none
 * @return none
 * @brief This function will init all that is needed for the sensor so that in 
 * the main functions only this needs to be called
 * @author Cooper Cantrell 5/13/2024 3:37pm
 */
void SensorInit(void);

/**
 * @Function CheckBattery(void)
 * @param none
 * @return TRUE or FALSE
 * @brief This function is a prototype event checker that checks the battery voltage
 *        against a fixed threshold (#defined in the .c file). Note that you need to
 *        keep track of previous history, and that the actual battery voltage is checked
 *        only once at the beginning of the function. The function will post an event
 *        of either BATTERY_CONNECTED or BATTERY_DISCONNECTED if the power switch is turned
 *        on or off with the USB cord plugged into the Uno32. Returns TRUE if there was an 
 *        event, FALSE otherwise.
 * @note Use this code as a template for your other event checkers, and modify as necessary.
 * @author Gabriel H Elkaim, 2013.09.27 09:18
 * @modified Gabriel H Elkaim/Max Dunne, 2016.09.12 20:08 */
uint8_t CheckBattery(void);

/**
 * @Function CheckTrack(void)
 * @param none
 * @return TRUE or FALSE
 * @brief This function is the event checker that detects if the inductor is 
 *      close enough to the track wire by comparing it to a #define in the .c
 * @author Cooper Cantrell 5/8/2024 3:44
 */
uint8_t CheckTrack(void);

/**
 * @Function CheckTape(void)
 * @param none
 * @return TRUE or FALSE
 * @brief This function is the event checker that detects if there is a change
 *      in tape detection
 * @author Cooper Cantrell 5/10/2024 12:07
 */
uint8_t CheckTape(void);

/**
 * @Function CheckBeacon(void)
 * @param none
 * @return TRUE or FALSE
 * @brief This function is the event checker that detects if there is a change
 *      in beacon detection
 * @author Cooper Cantrell 5/14/2024 2:47
 */
uint8_t CheckBeacon(void);

/**
 * @Function CheckBumper(void)
 * @param none
 * @return TRUE or FALSE
 * @brief This function is the event checker that detects if there is a change
 *      in Bumper detection
 * @author Cooper Cantrell 5/15/2024 5:26
 */
uint8_t CheckBumper(void);

/**
 * @Function CheckPing(void)
 * @param none
 * @return TRUE or FALSE
 * @brief This function is the event checker that detects if there is a change
 *      in Ping detection
 * @author Cooper Cantrell 5/15/2024 5:26
 */
uint8_t CheckPing(void);
#endif	/* TEMPLATEEVENTCHECKER_H */

