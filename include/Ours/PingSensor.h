/* 
 * File:   PingSensor.h
 * Author: stipi
 *
 * Created on March 7, 2024, 3:34 PM
 */

#include <stdint.h>

#ifndef PINGSENSOR_H
#define	PINGSENSOR_H

/*
 * @Function PINGInit()
 * @Param none
 * @return none
 * @brief Initializes Ping Sensor to read, uses OC3, IC3 and Timer 3
 */
void PINGInit();

/*
 * @Function PINGInit()
 * @Param none
 * @return uint16_t data, holds the distance to object in mm
 * @brief Returns the most recent ping data recieved
 */
uint16_t PINGGetData();

#endif	/* PINGSENSOR_H */

