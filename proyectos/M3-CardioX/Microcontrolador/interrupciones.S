        .include "p30F3013.inc"
		
	.GLOBAL __U1RXInterrupt
	.GLOBAL __T3Interrupt
	.GLOBAL __ADCInterrupt

	.GLOBAL _dato
;******************************************************************************
;DESCRIPCION:	ISR (INTERRUPT SERVICE ROUTINE) DEL UART 1
;*****************************************************************************
__ADCInterrupt:
    PUSH    W0
    PUSH    W1
    
    BTG	    LATB,	#LATB5
    NOP
    MOV     #ADCBUF0,   W1
    CLR     W0
 ;   MOV     ADCBUF1,   W0
    REPEAT  #7
    ADD     W0,         [W1++],     W0
    
    LSR     W0,         #7,	    W0
    MOV     W0,         U1TXREG
    
    BCLR    IFS0,       #ADIF

    POP	    W1
    POP	    W0
    RETFIE                     	;REGRESO DE LA ISR
;******************************************************************************
;DESCRIPCION:	ISR (INTERRUPT SERVICE ROUTINE) DEL UART 1
;*****************************************************************************
__U1RXInterrupt:
    PUSH	W0
				
    MOV		U1RXREG,	W0
    MOV		W0,		PORTB
    NOP

    BTG		LATD,		#LATD8
    NOP

    ;SE LIMPIA LA BANDERA DE INTERRUPCION DEL UART 1
    BCLR 	IFS0, 		#U1RXIF   

    POP		W0
    RETFIE                     	;REGRESO DE LA ISR

;******************************************************************************
;DESCRIPCION:	ISR (INTERRUPT SERVICE ROUTINE) DEL TIMER 3
;*****************************************************************************
__T3Interrupt:
    PUSH	W0

    BTG		LATD,		#LATD8
    NOP
;    MOV		_dato,		W0
;    MOV		W0,		U1TXREG
;    INC		_dato
    BCLR 	IFS0, 		#T3IF   

    POP		W0
    RETFIE                     	;REGRESO DE LA ISR

    