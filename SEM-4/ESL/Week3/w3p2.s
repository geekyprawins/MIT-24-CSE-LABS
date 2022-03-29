; SUM OF 'N' NATURAL NUMBERS USING MLA INSTRUCTION
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
	MOV R0, #0XA
	LDR R5, =RESULT
	MOV R1,#1
	MOV R2, #1
	MOV R4, #0
L1	MLA R4, R4, R1, R2
	ADD R2, #1
	CMP R2, R0
	BLS L1
	STR R4, [R5]
STOP B STOP 
	AREA MDATA, DATA, READWRITE
RESULT DCD 0
	END
