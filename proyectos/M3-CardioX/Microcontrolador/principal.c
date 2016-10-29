/********************************************************************************/
/* DESCRIPCIÓN: ESTE PROGRAMA CONFIGURA EL UART                 				*/
/* DISPOSITIVO: DSPIC30F3013													*/
/********************************************************************************/
#include "p30F3013.h"
/********************************************************************************/
/* 						BITS DE CONFIGURACIÓN									*/	
/********************************************************************************/
/* SE DESACTIVA EL CLOCK SWITCHING Y EL FAIL-SAFE CLOCK MONITOR (FSCM) Y SE 	*/
/* ACTIVA EL OSCILADOR INTERNO (FAST RC) PARA TRABAJAR							*/
/* FSCM: PERMITE AL DISPOSITIVO CONTINUAR OPERANDO AUN CUANDO OCURRA UNA FALLA 	*/
/* EN EL OSCILADOR. CUANDO OCURRE UNA FALLA EN EL OSCILADOR SE GENERA UNA 		*/
/* TRAMPA Y SE CAMBIA EL RELOJ AL OSCILADOR FRC  								*/
/********************************************************************************/
//_FOSC(CSW_FSCM_OFF & FRC); 
#pragma config FOSFPR = FRC             // Oscillator (Internal Fast RC (No change to Primary Osc Mode bits))
#pragma config FCKSMEN = CSW_FSCM_OFF   // Clock Switching and Monitor (Sw Disabled, Mon Disabled)/********************************************************************************/
/* SE DESACTIVA EL WATCHDOG														*/
/********************************************************************************/
//_FWDT(WDT_OFF); 
#pragma config WDT = WDT_OFF            // Watchdog Timer (Disabled)
/********************************************************************************/
/* SE ACTIVA EL POWER ON RESET (POR), BROWN OUT RESET (BOR), 					*/	
/* POWER UP TIMER (PWRT) Y EL MASTER CLEAR (MCLR)								*/
/* POR: AL MOMENTO DE ALIMENTAR EL DSPIC OCURRE UN RESET CUANDO EL VOLTAJE DE 	*/	
/* ALIMENTACIÓN ALCANZA UN VOLTAJE DE UMBRAL (VPOR), EL CUAL ES 1.85V			*/
/* BOR: ESTE MODULO GENERA UN RESET CUANDO EL VOLTAJE DE ALIMENTACIÓN DECAE		*/
/* POR DEBAJO DE UN CIERTO UMBRAL ESTABLECIDO (2.7V) 							*/
/* PWRT: MANTIENE AL DSPIC EN RESET POR UN CIERTO TIEMPO ESTABLECIDO, ESTO 		*/
/* AYUDA A ASEGURAR QUE EL VOLTAJE DE ALIMENTACIÓN SE HA ESTABILIZADO (16ms) 	*/
/********************************************************************************/
//_FBORPOR( PBOR_ON & BORV27 & PWRT_16 & MCLR_EN ); 
// FBORPOR
#pragma config FPWRT  = PWRT_16          // POR Timer Value (16ms)
#pragma config BODENV = BORV27           // Brown Out Voltage (2.7V)
#pragma config BOREN  = PBOR_ON          // PBOR Enable (Enabled)
#pragma config MCLRE  = MCLR_EN          // Master Clear Enable (Enabled)
/********************************************************************************/
/*SE DESACTIVA EL CÓDIGO DE PROTECCIÓN											*/
/********************************************************************************/
//_FGS(CODE_PROT_OFF);      
// FGS
#pragma config GWRP = GWRP_OFF          // General Code Segment Write Protect (Disabled)
#pragma config GCP = CODE_PROT_OFF      // General Segment Code Protection (Disabled)

/********************************************************************************/
/* SECCIÓN DE DECLARACIÓN DE CONSTANTES CON DEFINE								*/
/********************************************************************************/
#define EVER 1
#define MUESTRAS 64

/********************************************************************************/
/* VARIABLES NO INICIALIZADAS LA MEMORIA DE DATOS CERCANA (NEAR), LOCALIZADA	*/
/* EN LOS PRIMEROS 8KB DE RAM													*/
/********************************************************************************/
int var1 __attribute__ ((near));

void iniPerifericos( void );
void iniInterrupciones( void );
extern void RETARDO_1S( void );
extern void RETARDO_30ms( void );

unsigned char dato = 0;

int main (void)
{
    
    iniPerifericos();
    iniInterrupciones();
    
    //Habilitacion de perifericos 
    U1MODEbits.UARTEN   = 1;
    U1STAbits.UTXEN     = 1;
    ADCON1bits.ADON     = 1;
    T3CONbits.TON       = 1;
  
    for(;EVER;)
    {
        Nop();
    }
    
    return 0;
}
/****************************************************************************/
/* DESCRICION:	ESTA RUTINA INICIALIZA LAS INTERRPCIONES    				*/
/* PARAMETROS: NINGUNO                                                      */
/* RETORNO: NINGUNO															*/
/****************************************************************************/
void iniInterrupciones( void )
{
    //Habilitacion de interrupcion de recepcion del UART
    IFS0bits.U1RXIF = 0;
    IEC0bits.U1RXIE = 1;
    //Habilitacion de interrupcion del TIMER 3
    IFS0bits.T3IF = 0;
    IEC0bits.T3IE = 1;
    //Habilitacion de interrupcion del ADC
    IFS0bits.ADIF = 0;
    IEC0bits.ADIE = 1;
}
/****************************************************************************/
/* DESCRICION:	ESTA RUTINA INICIALIZA LOS PERIFERICOS						*/
/* PARAMETROS: NINGUNO                                                      */
/* RETORNO: NINGUNO															*/
/****************************************************************************/
void iniPerifericos( void )
{
    PORTB = 0;
    Nop();
    LATB = 0;
    Nop();
    TRISB = 0;
    Nop();
    TRISBbits.TRISB2 = 1;
    Nop();

    PORTD = 0;
    Nop();
    LATD = 0;
    Nop();
    TRISD = 0;
    Nop();
   
    PORTC = 0;
    Nop();
    LATC = 0;
    Nop();
    TRISC = 0;
    Nop();
    TRISCbits.TRISC14 = 1;  //U1ARX <--- entrada
    Nop();
    
    //Configuracion de UART
    U1MODE = 0X0420;
    U1STA  = 0X8000;
    U1BRG  = 11;    //9600 BAUDIOS
    
    //Configuracion de TIMER 3 
    //FOSC = 7.3728Mhz, Pre-escala = 1, FTxIF = 512 hz
    TMR3    = 0;
    PR3     = 450;
    T3CON   = 0; 
    
    //Configuracion del ADC
    
    ADCON1 = 0X0044;
    ADCON2 = 0X001C;
    ADCON3 = 0X0102;
    ADCHS  = 0X0002;
    ADPCFG = 0XFFFB;
    ADCSSL = 0X0000;
}

