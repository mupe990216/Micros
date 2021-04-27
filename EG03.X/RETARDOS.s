    .include "p30F3013.inc"
    
    .GLOBAL	_RETARDO_50ms
    .GLOBAL	_RETARDO_1S
    
_RETARDO_50ms:
    PUSH    W0    
    MOV	    #0X8000,	W0    
CICLO1_50ms:
    DEC	    W0,		W0
    BRA	    NZ,		CICLO1_1S
    POP	    W0
    RETURN

_RETARDO_1S:
	PUSH	W0
	PUSH	W1
	
	MOV	#10,		W1	
CICLO2_1S:
	CLR	W0	
CICLO1_1S:
	DEC	W0,		W0  
	BRA	NZ,		CICLO1_1S
	
	DEC	W1,		W1
	BRA	NZ,		CICLO2_1S
	
	POP	W1
	POP	W0
	RETURN
    


