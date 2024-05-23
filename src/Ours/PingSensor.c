#include "PingSensor.h"
#include "BOARD.h"
#include <xc.h>
#include <sys/attribs.h>
#include <stdio.h>

//#define PINGSENSORTESTSTAP

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
    OC3RS = 7;//10 microsecond pulse
    
    OC3CONbits.ON = 1;
    
    IC3CON = 0;
    IC3CONbits.C32 = 1;//32 bit mode, forcing timer 2
    IC3CONbits.FEDGE = 1;//capture rising edge first
    IC3CONbits.ICTMR = 0;//timer 3 is source
    IC3CONbits.ICI = 0;//interrupt every capture
    IC3CONbits.ICM = 0b001;//
    IC3CONbits.ON = 1;
    
    IFS0bits.IC3IF = 0;
    IPC3bits.IC3IP = 3;
    IPC3bits.IC3IS = 3;
    IEC0bits.IC3IE = 1;
    
    TRISDbits.TRISD10 = 1;
    //ODCDbits.ODCD3 = 1;
    
}

uint16_t PINGGetData(){
    return time/58*16;//return in millimeters (time is measured in . 1micro seconds so is 10 times the expected amount /58 should be cm but x10 is mm)(x16 for new prescaler))
}

void __ISR(_INPUT_CAPTURE_3_VECTOR) __IC3Interrupt(void){
    if(PORTDbits.RD10){//rising edge case
        startTime = IC3BUF & 0xFFFF;
    }else{//falling edge
        int16_t data = (IC3BUF & 0xFFFF);
        data = (data - startTime);
        if(data < 0){
            data = -data;
        }
        time = data;
    }
    IFS0bits.IC3IF = 0;
}

#ifdef PINGSENSORTESTSTAP
#include "serial.h"
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
        printf("distance: %d\r\n", data);
    }
}

#endif
