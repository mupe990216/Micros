    .include "p30F3013.inc"

    .GLOBAL _RETARDO_1S
    .GLOBAL _RETARDO_100ms
    
;/**@brief ESTA RUTINA GENERA UN RETARDO DE 1 SEGUNDO
; *
; * SIEMPRE QUE ESCRIBIMOS UNA FUNCION EN ENSAMBLADOR DEBEMOS GUARDAR AL INICIO 
; * LOS REGISTROS QUE USEMOS DENTRO DE LA FUNCION Y AL FINAL LOS REESTABLECEMOS
; */	
_RETARDO_100ms:
	PUSH	W0
	
	MOV	#0x8000		w0	;W0 = CALCULAR
CICLO1_100ms:	
	DEC	W0,		W0	;W0 = 0 - 1 = -1 = 0B11111111 11111111 = 65535
	BRA	NZ,		CICLO1_100ms
	
	POP	W0
	RETURN

    ;/**@brief ESTA RUTINA GENERA UN RETARDO DE 1 SEGUNDO
; *
; * SIEMPRE QUE ESCRIBIMOS UNA FUNCION EN ENSAMBLADOR DEBEMOS GUARDAR AL INICIO 
; * LOS REGISTROS QUE USEMOS DENTRO DE LA FUNCION Y AL FINAL LOS REESTABLECEMOS
; */	
_RETARDO_1S:
	PUSH	W0
	PUSH	W1
	
	MOV	#10,		W1
CICLO2_1S:    
	CLR	W0			;W0 = 0
CICLO1_1S:	
	DEC	W0,		W0	;W0 = 0 - 1 = -1 = 0B11111111 11111111 = 65535
	BRA	NZ,		CICLO1_1S
	
	DEC	W1,		W1
	BRA	NZ,		CICLO2_1S

	POP	W1
	POP	W0
	RETURN

