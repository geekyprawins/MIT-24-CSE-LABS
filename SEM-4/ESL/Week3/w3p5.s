	AREA RESET, DATA, READONLY
	EXPORT __Vectors
__Vectors
	DCD 0X10001000
	DCD Reset_Handler
	ALIGN
	AREA MYCODE, CODE, READONLY
	ENTRY
	EXPORT Reset_Handler
		
Reset_Handler
	LDR R0,=SRC
	LDR R1,[R0]
	LDR R5,=DST
	MOV R8,0xF
	MOV R4, #4
	
up	AND R2, R1, R8
	LSL R8, #4
	LSR R1, #4
	ORR R3, R2
	SUBS R4, #1
	BNE up
	STR R3,[R5]
	
STOP B STOP
SRC DCD 0x01020304
	
	AREA MYDATA, DATA, READWRITE
DST DCD 0
	END
