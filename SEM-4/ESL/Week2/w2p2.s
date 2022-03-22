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
	LDR R0, =V1
	LDR R1, =V2
	LDR R6, =DST
	MOV R2, #4
    ADD R1,#12
	ADD R0,#12
	MOV R5, #0
L1	LDR R3, [R0], #-4
	LDR R4, [R1], #-4
	ADD R4, R5
	MOV R5, #0
	ADDS R3, R3, R4
	ADC  R5,#0
	STR R3, [R6],#4
	;SUB R6, #4
	SUBS R2, #1
	CMP R2,#0
	BNE L1
STOP 
	B STOP
V1 DCD 0x12, 0x27, 0x82345678, 0x72345678
V2 DCD 0x12, 0x2A, 0xA2345678, 0xA2345678
	AREA MYDATA, DATA, READWRITE
DST DCD 0
	END