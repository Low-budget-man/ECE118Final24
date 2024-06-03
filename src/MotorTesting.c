#include <BOARD.h>
#include <xc.h>
#include <stdio.h>
#include "ES_Configure.h"
#include "ES_Framework.h"
#include "SensorEventChecker.h"
// My includes
#include "AD.h"
#include "LED.h"
#include "Maw.h"
#include "IO_Ports.h"
#include "ES_Timers.h"

#define BUMPERfrPORT PORTX
#define BUMPERfrPIN PIN8
#define BUMPERflPORT PORTW
#define BUMPERflPIN PIN5
#define BUMPERbrPORT PORTX
#define BUMPERbrPIN PIN11
#define BUMPERblPORT PORTW
//Pin 6 and 8 is haveing issues and does not work
#define BUMPERblPIN PIN7

void main(void)
{
    ES_Return_t ErrorType;

    BOARD_Init();
    printf("Starting Motor Testing\r\n");


    // Your hardware initialization function calls go here
    Maw_Init();
    // now initialize the Events and Services Framework and start it running

    while(TRUE);
};

/*------------------------------- Footnotes -------------------------------*/
/*------------------------------ End of file ------------------------------*/

