;2-DIGIT HEX TO ASCII FORMAT
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
	MOV R0, #0X49
	MOV R1, R0
	ROR R0, R0, #4
	ADD R0, R0, #0X30
	AND R1, R1, 0X0F
	ADD R1, R1, #0X30
	LDR R4, =RESULT
	STRB R1,[R4], #1
	STRB R0, [R4]
STOP B STOP
	AREA MDATA, DATA, READWRITE
RESULT DCW 0
	END 
	
	
	