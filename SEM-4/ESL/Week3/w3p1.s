	;Division by repetative subtraction
	AREA RESET, DATA, READONLY
    EXPORT  __Vectors

__Vectors 
      DCD  0x40001000     ; stack pointer value when stack is empty
      DCD  Reset_Handler  ; reset vector
  
    ALIGN
    AREA mycode, CODE, READONLY
	ENTRY
	EXPORT Reset_Handler
Reset_Handler
	LDR R0,=X
	LDR R1,=Y
	LDR R5,=QUOTIENT
	LDR R2,[R0]
	LDR R3, [R1]
	CMP R2, R3
	BCC SWAP
L1	MOV R4, #0
L2	SUB R2, R2, R3
	ADD R4, R4, #1
	CMP R2, R3
	BHS L2
	STR R4, [R5]
	B STOP	
SWAP MOV R0, R2
	 MOV R2, R3
	 MOV R3, R0
	 B L1
STOP B STOP
X DCD 20
Y DCD 5
	AREA MDATA, DATA, READWRITE
QUOTIENT DCD 0
	END 