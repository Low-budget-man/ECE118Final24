//#include "PingSensor.h"
//#include "BOARD.h"
//#include <xc.h>
//#include <sys/attribs.h>
//#include <stdio.h>
////#include "MG996RServoDriver.h"
////#include "FreeRunningTimer.h"
//
//#define PINGSENSORTESTSTAP 1
//
//uint16_t startTime;
//uint16_t time;
//
//void PINGInit(){
//    T2CON = 0; // everything should be off
//    T2CONbits.TCKPS = 0b110; // 1:4 prescaler/ 10MHz clk 
//    T2CONbits.T32 = 0;
//    PR2 = (37500 - 1); // interrupt at 20 milliS intervals
//    T2CONbits.ON = 1; // turn the timer on
//    
//    OC3CON = 0;
//    OC3CONbits.SIDL = 1;//stop in idle
//    OC3CONbits.OC32 = 0;//32 bit mode
//    OC3CONbits.OCFLT = 0;//get that error stuff out of here we ballin'
//    OC3CONbits.OCTSEL = 0;//timer 2
//    OC3CONbits.OCM = 0b101;//continuous pulse mode
//    OC3R = 0;
//    OC3RS = 8;//12 microsecond pulse
//    
//    OC3CONbits.ON = 1;
//    
//    IC3CON = 0;
//    IC3CONbits.C32 = 0;//32 bit mode, forcing timer 2
//    IC3CONbits.FEDGE = 1;//capture rising edge first
//    IC3CONbits.ICTMR = 1;//timer two is source
//    IC3CONbits.ICI = 0;//interrupt every capture
//    IC3CONbits.ICM = 0b001;//
//    IC3CONbits.ON = 1;
//    
//    IFS0bits.IC3IF = 0;
//    IPC3bits.IC3IP = 3;
//    IPC3bits.IC3IS = 3;
//    IEC0bits.IC3IE = 1;
//    
//    TRISDbits.TRISD10 = 1;
//    //ODCDbits.ODCD3 = 1;
//    
//}
//
//uint16_t PINGGetData(){
//    return time/58*16;//return in millimeters (time is measured in . 1micro seconds so is 10 times the expected amount /58 should be cm but x10 is mm)(x16 for new prescaler))
//}
//
//void __ISR(_INPUT_CAPTURE_3_VECTOR) __IC3Interrupt(void){
//    if(PORTDbits.RD10){//rising edge case
//        startTime = IC3BUF & 0xFFFF;
//    }else{//falling edge
//        int16_t data = (IC3BUF & 0xFFFF);
//        data = (data - startTime);
//        if(data < 0){
//            data = -data;
//        }
//        time = data;
//    }
//    IFS0bits.IC3IF = 0;
//}
//
//#if PINGSENSORTESTSTAP
//int main(){
//    BOARD_Init();
//    PINGInit();
//    printf("initializing\r\n");
//    uint64_t* PingTimer = 0;
//    
//    while(1){
//        for(int i = 0; i < 40000; i++){
//            asm("nop");
//        }
//        uint16_t data = PINGGetData();
//        printf("distance: %d\r\n", data);
//    }
//}
//
//#endif

#include "PingSensor.h"
#include "BOARD.h"
#include <xc.h>
#include <sys/attribs.h>
#include <stdio.h>

//#define PINGSENSORTESTSTAP
#define PINGINPUTCAPTURE IC2
#define PINGINPUTCAPTUREPIN RD9
#define PINGOUTPUTCOMPARE OC3
uint16_t startTime;
uint16_t time;

void PINGInit(){
    T3CON = 0; // everything should be off
    T3CONbits.TCKPS = 0b110; // 1:4 prescaler/ 10MHz clk 
//    T3CONbits.T32 = 0;
    PR3 = (37500 - 1); // interrupt at 20 milliS intervals
    T3CONbits.ON = 1; // turn the timer on
    
    OC3CON = 0;
    OC3CONbits.SIDL = 1;//stop in idle
    OC3CONbits.OC32 = 0;//32 bit mode
    OC3CONbits.OCFLT = 0;//get that error stuff out of here we ballin'
    OC3CONbits.OCTSEL = 1;//timer 3
    OC3CONbits.OCM = 0b101;//continuous pulse mode
    OC3R = 0;
    OC3RS = 8;//10-ish microsecond pulse
    
    OC3CONbits.ON = 1;
    
    IC2CON = 0;
    IC2CONbits.C32 = 0;//32 bit mode, forcing timer 2
    IC2CONbits.FEDGE = 1;//capture rising edge first
    IC2CONbits.ICTMR = 0;//timer 3 is source
    IC2CONbits.ICI = 0;//interrupt every capture
    IC2CONbits.ICM = 0b001;//
    IC2CONbits.ON = 1;
    
    IFS0bits.IC2IF = 0;
    IPC2bits.IC2IP = 3;
    IPC2bits.IC2IS = 3;
    IEC0bits.IC2IE = 1;
    
    TRISDbits.TRISD9 = 1;
    //ODCDbits.ODCD3 = 1;
    
}

uint16_t PINGGetData(){
    return time/58*16;//return in millimeters (time is measured in . 1micro seconds so is 10 times the expected amount /58 should be cm but x10 is mm)(x16 for new prescaler))
}

void __ISR(_INPUT_CAPTURE_2_VECTOR) __IC2Interrupt(void){
    if(PORTDbits.RD9){//rising edge case
        startTime = IC2BUF & 0xFFFF;
    }else{//falling edge
        int16_t data = (IC2BUF & 0xFFFF);
        data = (data - startTime);
        if(data < 0){
            data = -data;
        }
        time = data;
    }
    IFS0bits.IC2IF = 0;
}

#ifdef PINGSENSORTESTSTAP
#include "serial.h"
#include <stdio.h>
int main(){
    BOARD_Init();
    SERIAL_Init();
    PINGInit();
    printf("initializing\r\n");
    uint64_t* PingTimer = 0;
    while(1){
        for(int i = 0; i < 40000; i++){
            asm("nop");
        }
        uint16_t data = PINGGetData();
        printf("distance: %d\r\n", data);
    }
}

#endif
