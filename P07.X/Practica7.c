#include "p30F3013.h"


//_FOSC(CSW_FSCM_OFF & FRC); 
#pragma config FOSFPR = FRC             // Oscillator (Internal Fast RC (No change to Primary Osc Mode bits))
#pragma config FCKSMEN = CSW_FSCM_OFF   // Clock Switching and Monitor (Sw Disabled, Mon Disabled)
/********************************************************************************/
/* SE DESACTIVA EL WAvoid habilitarPerifericos()TCHDOG														*/
//_FWDT(WDT_OFF); 
#pragma config WDT = WDT_OFF            // Watchdog Timer (Disabled)
/********************************************************************************/
//_FBORPOR( PBOR_ON & BORV27 & PWRT_16 & MCLR_EN ); 
// FBORPOR
#pragma config FPWRT  = PWRT_16          // POR Timer Value (16ms)
#pragma config BODENV = BORV20           // Brown Out Voltage (2.7V)
#pragma config BOREN  = PBOR_ON          // PBOR Enable (Enabled)
#pragma config MCLRE  = MCLR_EN          // Master Clear Enable (Enabled)
/********************************************************************************/
//_FGS(CODE_PROT_OFF)
// FGS
#pragma config GWRP = GWRP_OFF          // General Code Segment Write Protect (Disabled)
#pragma config GCP = CODE_PROT_OFF      // General Segment Code Protection (Disabled)

/********************************************************************************/
/* SECCI?N DE DECLARACI?N DE CONSTANTES CON DEFINE								*/
/********************************************************************************/
#define EVER 1
//#define MUESTRAS 64

/********************************************************************************/
/* DECLARACIONES GLOBALES														*/
/********************************************************************************/
/*DECLARACI?N DE LA ISR DEL TIMER 1 USANDO __attribute__						*/
/********************************************************************************/
void __attribute__((__interrupt__)) _INT0Interrupt( void );

void configurarPuertos();  
void configurarUART();
void configurarInt();

extern void INI_LCD_8BITS( );
extern void BF_LCD( );
extern void DATO_LCD( unsigned short int Dato );
extern void COMANDO_LCD( unsigned short int Dato );
extern void habilitarLPOSC( );
extern void printLCD( char *cad );

short int dato, drcv;
char RTC[9];

int main(void) 
{    
    configurarPuertos();
    configurarUART();
    INI_LCD_8BITS();
    configurarInt();        
    drcv = 0;
    for(;EVER;){
        if( drcv == 1 ){
            BF_LCD();
            DATO_LCD( dato );
            drcv = 0;
        }
        asm("nop");
    }
    
    return 0;
}


void configurarInt()
{
    IFS0bits.U1RXIF = 0;     //Apagando la bandera de la interrupci�n
    IEC0bits.U1RXIE = 1;     //Habilitando Interrupci�n
    U1MODEbits.UARTEN = 1;   //encender el UART
}

void configurarUART()
{
    U1MODE = 0X0420;    
    U1STA = 0X8000;
    U1BRG = 11;
}

void configurarPuertos()
{
    PORTB = 0;
    asm("nop");
    LATB = 0;
    asm("nop");
    TRISB = 0;
    asm("nop");
    
    ADPCFG = 0XFFFF;
    
    PORTD = 0;
    asm("nop");
    LATD = 0;
    asm("nop");
    
    TRISDbits.TRISD8 = 0;   //BCLR TRISD, #TRISD8
    asm("nop");
    
    PORTF = 0;
    asm("nop");
    LATF = 0;
    asm("nop");
    
    TRISFbits.TRISF4 = 0;   //BCLR TRISF, #TRISF4
    asm("nop");
    
    TRISFbits.TRISF5 = 0;   //BCLR TRISF, #TRISF5
    asm("nop");        
    
    PORTC = 0;
    asm("nop");
    LATC = 0;
    asm("nop");
        
    TRISCbits.TRISC14 = 1;   //BSET TRISC, #TRISC14
    asm("nop");                       
    
}
/**  @brief: CONFIGURACION DEL UART 1. EL UART 1 SE COMUNICA CON 
 *           EL FT232 PARA COMUNICACION CON PC
 *   @baudrate: 115200 BAUDIOS
 *   @frame: 8 BITS X DATO, SIN PARIDAD, 1 BIT DE PARO
 */

/********************************************************************************/
/* DESCRICION:	ISR (INTERRUPT SERVICE ROUTINE) DE RECEPCION DEL UART 2			*/
/* LA RUTINA TIENE QUE SER GLOBAL PARA SER UNA ISR								*/	
/* SE USA PUSH.S PARA GUARDAR LOS REGISTROS W0, W1, W2, W3, C, Z, N Y DC EN LOS */
/* REGISTROS SOMBRA																*/
/********************************************************************************/
void __attribute__((__interrupt__, no_auto_psv)) _INT0Interrupt( void )
{
//    LATD = LATD ^ 0x0200;
//    LATDbits.LATD9 = ~LATDbits.LATD9;
    //asm("btg latd, #latd9");
        
    IFS0bits.T1IF = 0;
}
//      T1IF=1,   T1IF=1
//      ________
//_____|        |_______|