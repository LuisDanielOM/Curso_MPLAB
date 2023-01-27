//Template for the PIC18F4550

#pragma PLLDIV = 2 , CPUDIV = OSC1_PLL2, USBDIV = 2  
#pragma FOSC = HSPLL_HS, FCMEN = OFF, IESO = OFF       
#pragma config PWRT = OFF, BOR = OFF, BORV = 3, VREGEN = OFF     
#pragma config WDT = OFF       
#pragma config WDTPS = 32768   
#pragma config CCP2MX = ON, PBADEN = OFF, LPT1OSC = OFF, MCLRE = ON      
#pragma config STVREN = ON, LVP = ON, ICPRT = OFF, XINST = OFF     
#pragma config CP0 = OFF, CP1 = OFF, CP2 = OFF, CP3 = OFF       
#pragma config CPB = OFF, CPD = OFF       
#pragma config WRT0 = OFF, WRT1 = OFF, WRT2 = OFF, WRT3 = OFF       
#pragma config WRTC = OFF, WRTB = OFF, WRTD = OFF      
#pragma config EBTR0 = OFF, EBTR1 = OFF, EBTR2 = OFF, EBTR3 = OFF      
#pragma config EBTRB = OFF

#define _XTAL_FREQ 48000000

#include <xc.h>

void main(void) {
    while (1)
    {
        
    } 
}
