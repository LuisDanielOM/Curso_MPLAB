/*----------------------------------------------Anti-rebote en pulsadores-----------------------------------------
 
 El rebote es una pequeña fluctuación en la señal de voltaje que envía un arreglo PULLUP/PULLDOWN con un botón.
 Dicho rebote es un problema producido por la falla mecánica del botón y provoca errores considerables a la hora 
 de hacer lecturas digitales con mucha sensibilidad.

 Para solucionar este problema de puede seguir dos métodos:

---------- Anti-rebote por hardware

Se deben colocar un capacitor de 100nF en paralelo a la resistencia PULL.

---------- Anti-rebote por software

Dependiendo el arreglo PULL se utiliza un código especial para el botón.  

Ejemplo con PUllUP
    if(PORTAbits.RA0 == 0)
    {
        while(PORTAbits.RA0 == 0);
        __delay_ms(10);
        <Sentencias>;
    }

Ejemplo con PULLDOWMN
    If(PORTAbits.RA0==1){
        while(PORTAbits.RA0==1);
        __delay_ms(10);
        <Sentencias>;
    }


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

unsigned int contador1 = 0;     //Contador para el botón con rebote
unsigned int contador2 = 0;     //Contador para el botón sin rebote

void main(void) {

    ADCON1bits.PCFG=0x0F;     //Asignación de todos los pines como digitales
    TRISBbits.RB0 = 1;  //Se declara el pin B0 y B1 como entrada
    TRISBbits.RB1 = 1;  
    TRISCbits.RC2 = 0;  //Se declara el pin C0 y C1 como salida
    TRISCbits.RC1 = 0;              
    
    LATCbits.LC2 = 0;  //Se limpian los pines C0 y C1
    LATCbits.LC1 = 0;  
    
    while (1) {

        if(PORTBbits.RB0==1){           //El primer botón tendrá rebote por lo que el contador 1 funcionara mal
            contador1++;
        }
        else if(PORTBbits.RB1 == 1){    //El segundo botón tendrá anti-rebote por lo que el contador 1 funcionará bien
            while(PORTBbits.RB1 ==1);
            __delay_ms(50);
            contador2++;
        }

        //Estas estructuras if sirven para encender un led respectivo por 1 segundo cuando cada contador llega 
        //a 10 para después reiniciar cada contador
        if(contador1==10){       
            LATCbits.LC2 = 1;
            __delay_ms(100);
            LATCbits.LC2=0;
            contador1 = 0;
        }
        if (contador2==10){
            LATCbits.LC1 = 1;
            __delay_ms(100);
            LATCbits.LC1=0;
            contador2 = 0;
        }

    }
}
