;finding factorial of a number using a subroutines using recursion
	AREA    RESET, DATA, READONLY
     	EXPORT  __Vectors

__Vectors 
      DCD  0x40001000     ; stack pointer value when stack is empty
      DCD  Reset_Handler  ; reset vector
  
    ALIGN
    AREA mycode, CODE, READONLY
	ENTRY
	EXPORT Reset_Handler
Reset_Handler
	MOV R0, #8
	MOV R3, #1
	LDR R4,=RESULT
	BL FACT
	STR R3, [R4]
	B STOP
	
FACT 		PUSH {R14}
			MUL R3, R3, R0
			SUB R0, R0, #1
			CMP R0, #0
			BEQ L1
			BL FACT
			POP {R14}
L1			BX LR
STOP B STOP 
	 AREA MYDATA, DATA, READWRITE
RESULT DCD 0
	 END