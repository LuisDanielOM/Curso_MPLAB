/*-----------------------------------------Display de 7 segmentos---------------------------------------------

Un display es un dispositivo conformado por un grupo de 7 LEDs, y un punto, que están ordenados de tal manera de 
que puedan mostrar los números del 0 al 9 cuando se enciendan, aunque su uso no está restringido a escribir solo
esos números.

Existen dos tipos de display de 7 segmentes, los que tienen una terminal ánodo(+) en común y que encienden con
una señal lógica baja, y los que tienen una terminal cátodo(GND) común y encienden con una señal lógica alta.

*/

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

//Se almacenan las combinaciones para mostrar los números del 0 al 9 con un display cátodo común
unsigned int display[10] = {0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F};  

void main(void) {

    ADCON1bits.PCFG = 0x0F; //Se declaran todos los pines como digitales
    TRISD = 0;              //El puerto D se declara como salida
    
    while (1) {
        //El siguiente bucle for recorrerá el arreglo y en cada iteración asignará cada elemento al puerto LATD
        //para así encender los segmentos del display 
        for (int i = 0; i < 10; i++){
            LATD = display[i];
            __delay_ms(100);
        }
    }
}

