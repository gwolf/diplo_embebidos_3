        .include "p30F3013.inc"
		
	.GLOBAL __U1RXInterrupt
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


	
