    .include "p30F3013.inc"

    .GLOBAL _habilitarLPOSC
    .GLOBAL __T1Interrupt
    .GLOBAL _useg
    .GLOBAL _dseg
    .GLOBAL _umin
    .GLOBAL _dmin
    .GLOBAL _uhr
    .GLOBAL _dhr
;/**@brief ESTA ES LA ISR DEL TIMER 1
; *
; */	
   
__T1Interrupt:
	PUSH	W0
    
	INC _useg	    ;useg ++ 
	MOV _useg,W0
	CP W0,#10
	BRA NZ,FIN_ISR_T1
	CLR _useg	    ;useg = 0
	
	INC _dseg	    ;dseg ++
	MOV _dseg,W0
	CP W0,#6
	BRA NZ,FIN_ISR_T1
	CLR _dseg	    ;dseg = 0
	
	;Unidad de Minuto
	;Comparacion con 10
	INC _umin	    ;umin ++	
	MOV _umin,W0
	CP W0,#10
	BRA NZ,FIN_ISR_T1
	CLR _umin	    ;umin=0
	
	;Decena de Minuto
	;Comparacion con 6
	INC _dmin	    ;dmin ++
	MOV _dmin,W0
	CP W0,#6
	BRA NZ,FIN_ISR_T1
	CLR _dmin	    ;dmin=0
	
	;Decena de hora
	;Comparacion con 2
	MOV #2,W0
	CP.B _dhr
	BRA Z,VALIDA_RELOJ
    
	INC _uhr	    ;uhr ++
	MOV _uhr,W0
	CP W0,#10
	BRA NZ,FIN_ISR_T1
	CLR _uhr	    ;uhr=0
	INC _dhr
    
;Si es 2 solo alcance Maximo un 4 (24hrs)
VALIDA_RELOJ:
	INC _uhr
	MOV _uhr,W0
	CP W0,#4
	BRA NZ, FIN_ISR_T1
	CLR _uhr
	CLR _dhr
	GOTO FIN_ISR_T1
	
FIN_ISR_T1:
	BCLR	IFS0,	    #T1IF	;APAGAR BANDERA DE INTERRUPCION DEL TIMER1
    
	POP	W0
	RETFIE
;/**@brief ESTA RUTINA HABILITA EL OSCILADOR DE 32 KHz
; *
; * @param: NINGUNO
; * @return: NINGUNO
; */	
_habilitarLPOSC:
	PUSH	W0
	PUSH	W1
	PUSH	W2

	;ESCRIBIR EL CODIGO DE HABILITACION
	MOV	#0X46,	    W0
	MOV	#0X57,	    W1
	MOV	#OSCCONL,   W2
	MOV.B	W0,	    [W2]
	MOV.B	W1,	    [W2]
	BSET	OSCCONL,    #LPOSCEN
	
	POP	W2
	POP	W1
	POP	W0
	RETURN






