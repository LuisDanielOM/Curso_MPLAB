/*--------------------------Entradas y salidas de datos------------------------
El microcontrolador PIC18F4550 posee la capacidad de utilizar perifericos como entradas y salidas, los registros 
que se deben considerar para el uso de estos perifericos son: 

    TRIS: Este es el registro de dirección de datos.
    PORT: Lee los niveles logicos en los pines del PIC.
    LAT: Estados de salida, alto o bajo.

Cada registro visto con anterioridad estará asociado a cada puerto del microcontrolador, y como en este caso se cuenta
con 5 puertos para el PIC18F4550, se tiene en total el acceso a los siguientes registros:

    TRISA   PORTA   LATA
    TRISB   PORTB   LATB
    TRISC   PORTC   LATC
    TRISD   PORTD   LATD
    TRISE   PORTE   LATE

---------- Registro TRIS
Es un registro de dirección de datos donde se configura si un puerto será de entrada o salida.
    -Para especificar que es una salida se coloca un 0.
    -Para especificar que es una entrada se coloca un 1.

---------- Registro PORT

Sirve para leer los niveles lógicos de cada pin en el PIC. Solo se utiliza para leer datos de entrada que obtiene el PIC 
de dispositivos externos conectados a sus pines.

---------- Registro LAT

Este es un latch de salida que servira para establecer el estado logico (alto o bajo) de los pines
que sean salidas.

---------- Procedimiento para trabajar con entradas y salidas de datos

1.- Configurar los pines como digitales o analógicos. Para el caso del PIC18F4550 el registro que se ocupa para hacer
esto será el "ADCON1".
2.- Configurar los puestos o pines ya sea como entradas o salidas.
3.- Limpiar el puerto o pin correspondiente.

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

void main(void) {
    
    //Configuraciones con otros registros
    ADCON1bits.PCFG = 0x0F;             //Se declaran todos los pines como digitales (buscar datasheet)
    INTCON2bits.RBPU = 0;        //Esta instrucción habilita las resistencias internas de las entradas como pull up
                                 //un 0 las habilita y un 1 las deshabilita. Solo funciona para los PORTB del 2 al 7.
    
    //Configuración de dirección de los pines
    TRISD = 0x00;           //Se asigna todo el puerto D como salida (0) en formato hexadecimal.
    TRISB = 0b11111111;     //Se asigna todo el puerto B como entrada (1) en formato binario.
    TRISCbits.RC0 = 0;      //Se asigna solo un bit del puerto C como salida, en este caso el PIN C0.
    TRISA = 0xFF;           //Se asigna todo el puerto A como entrada (1) en formato hexadecimal.

    //Limpieza del estado incial del puerto
    LATD = 0x00;    //Se asigna un 0 para limpiar todo el puerto D
    LATCbits.LC0 = 0;
    
    //Se utiliza un bucle while para que se ciclen todas las intrucciones dentro de su ámbito
    while (1) {
        LATDbits.LD0=1;  //Se pone el estado del pin D0 en estado alto.
        __delay_ms(100);   //Esta sentencia da un delay de 1000 ms
        LATD = 0b00011010;  //Se pone en estado alto solo algunos pines del puerto D.
        __delay_ms(100);

        if(PORTAbits.RA0==1 || PORTBbits.RB2==0 ){      //Se usa el registro PORTB y PORTA para la lectura de bits en los botones
            LATCbits.LC0 = 1;       
        }else{
            LATCbits.LC0 = 0;
        }
    }
}
