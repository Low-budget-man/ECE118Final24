/*
 * File: SensorService.h
 * Author: Cooper Cantrell
 * Created 5/8/2024 at 10:36PM
 */

#ifndef SensorService_H  // <- This should be changed to your own guard on both
#define SensorService_H  //    of these lines


/*******************************************************************************
 * PUBLIC #INCLUDES                                                            *
 ******************************************************************************/

#include "ES_Configure.h"   // defines ES_Event, INIT_EVENT, ENTRY_EVENT, and EXIT_EVENT
#include "ES_Events.h"
/*******************************************************************************
 * PUBLIC #DEFINES                                                             *
 ******************************************************************************/
#define PINGCLOSEc 320
#define PINGCLOSEf 640

/*******************************************************************************
 * PUBLIC TYPEDEFS                                                             *
 ******************************************************************************/


/*******************************************************************************
 * PUBLIC FUNCTION PROTOTYPES                                                  *
 ******************************************************************************/
/**
 * @Function ChangePingThres(uint16_t Newval)
 * @param Newval - the new value for the ping close thesh
 * @return void
 * @brief This function will change the PingClose Threshold 
 * @author Cooper Cantrell 6/1/2024 4:14 PM*/
void ChangePingThres(uint16_t Newval);
 
/**
 * @Function InitSensorService(uint8_t Priority)
 * @param Priority - internal variable to track which event queue to use
 * @return TRUE or FALSE
 * @brief This will get called by the framework at the beginning of the code
 *        execution. It will post an ES_INIT event to the appropriate event
 *        queue, which will be handled inside RunTemplateService function. Remember
 *        to rename this to something appropriate.
 *        Returns TRUE if successful, FALSE otherwise
 * @author Cooper Cantrell 5/8/2024 8:13 PM*/
uint8_t InitSensorService(uint8_t Priority);

/**
 * @Function PostSensorService(ES_Event ThisEvent)
 * @param ThisEvent - the event (type and param) to be posted to queue
 * @return TRUE or FALSE
 * @brief This function is a wrapper to the queue posting function, and its name
 *        will be used inside ES_Configure to point to which queue events should
 *        be posted to. Remember to rename to something appropriate.
 *        Returns TRUE if successful, FALSE otherwise
 * @author Cooper Cantrell 5/8/2024 8:13 PM */
uint8_t PostSensorService(ES_Event ThisEvent);

/**
 * @Function RunTemplateService(ES_Event ThisEvent)
 * @param ThisEvent - the event (type and param) to be responded.
 * @return Event - return event (type and param), in general should be ES_NO_EVENT
 * @brief This function is where you implement the whole of the service,
 *        as this is called any time a new event is passed to the event queue.  
 * @author Cooper Cantrell 5/8/2024 */
ES_Event RunSensorService(ES_Event ThisEvent);



#endif /* TemplateService_H */

