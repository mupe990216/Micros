    .include "p30F3013.inc"
    .EQU	RS_LCD,		RF4
    .EQU	RW_LCD,		RF5
    .EQU	E_LCD,		RD8
    
    .GLOBAL	_COMANDO_LCD
    .GLOBAL	_DATO_LCD
    .GLOBAL	_BF_LCD
    .GLOBAL	_INI_LCD_8BITS

; @BRIEF: ENVIA LOS COMANDOS AL LCD
; @PARAM: W0(WREG), COMANDO A ENVIAR
_COMANDO_LCD:
    BCLR    PORTF,	#RS_LCD	    ;RS = 0
    NOP
    BCLR    PORTF,	#RW_LCD	    ;RW = 0
    NOP
    BSET    PORTD,	#E_LCD	    ;E = 1
    NOP
    MOV.B   WREG,	PORTB	    ;PORTB(7:0) = W0(7:0)
    NOP
    BCLR    PORTD,	#E_LCD	    ;E = 0
    
    RETURN

; @BRIEF: ENVIA LOS DATOS AL LCD
; @PARAM: W0(WREG), DATO A ENVIAR
_DATO_LCD:
    BSET    PORTF,	#RS_LCD	    ;RS = 1
    NOP
    BCLR    PORTF,	#RW_LCD	    ;RW = 0
    NOP
    BSET    PORTD,	#E_LCD	    ;E = 1
    NOP
    MOV.B   WREG,	PORTB	    ;PORTB(7:0) = W0(7:0)
    NOP
    BCLR    PORTD,	#E_LCD	    ;E = 0
        
    RETURN
    
_BF_LCD:
    BCLR    PORTF,	#RS_LCD	    ;RS = 0
    NOP
    PUSH    TRISB		    ;STACK(SP++) = TRISB
    NOP    
    BSET    PORTF,	#RW_LCD	    ;RW = 1
    NOP
    BSET    PORTD,	#E_LCD	    ;E = 1
    NOP
ESPERA_LCD:
    BTSC    PORTB,	#RB7	    ;POLLING
    GOTO    ESPERA_LCD
    ;CONTINUARA ...
    
    RETURN
    
_INI_LCD_8BITS:
    CALL    _RETARDO_50ms
    MOV	    #0X30,	W0
    CALL    _COMANDO_LCD
    
    CALL    _RETARDO_50ms    
    MOV	    #0X30,	W0
    CALL    _COMANDO_LCD
    
    CALL    _RETARDO_50ms 
    MOV	    #0X30,	W0
    CALL    _COMANDO_LCD
    
    CALL    _BF_LCD
    MOV	    #0X38,	W0
    CALL    _COMANDO_LCD
    
    CALL    _BF_LCD
    MOV	    #0X08,	W0
    CALL    _COMANDO_LCD
    
    CALL    _BF_LCD
    MOV	    #0X01,	W0
    CALL    _COMANDO_LCD
    
    CALL    _BF_LCD
    MOV	    #0X06,	W0
    CALL    _COMANDO_LCD
    
    CALL    _BF_LCD
    MOV	    #0X0F,	W0
    CALL    _COMANDO_LCD
    
    RETURN


