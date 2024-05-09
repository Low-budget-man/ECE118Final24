#include <BOARD.h>
#include <xc.h>
#include <stdio.h>
#include "ES_Configure.h"
#include "ES_Framework.h"
// My includes
#include "AD.h"
#include "LED.h"
void main(void)
{
    ES_Return_t ErrorType;

    BOARD_Init();

    printf("Starting ES Framework Template\r\n");
    printf("using the 2nd Generation Events & Services Framework\r\n");


    // Your hardware initialization function calls go here
    // LEDs for all sensors
    LED_Init();
    LED_AddBanks(LED_BANK1);
    //sets all of the banks to 0 in case that is needed (0x0F) is a full bank)
    LED_OffBank(LED_BANK1,0x0F);
    // init the Track detector
    AD_Init();
    AD_AddPins(TRACK_VOLTAGE);
    //adding the LEDS so that if printf is broken we can see
    LED_OnBank(LED_BANK1,0x4);
    
    // now initialize the Events and Services Framework and start it running
    ErrorType = ES_Initialize();
    if (ErrorType == Success) {
        ErrorType = ES_Run();

    }
    //if we got to here, there was an error
    switch (ErrorType) {
    case FailedPointer:
        printf("Failed on NULL pointer");
        break;
    case FailedInit:
        printf("Failed Initialization");
        break;
    default:
        printf("Other Failure: %d", ErrorType);
        break;
    }
    for (;;)
        ;

};

/*------------------------------- Footnotes -------------------------------*/
/*------------------------------ End of file ------------------------------*/
