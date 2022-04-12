	;Sort an array using selection sort
	AREA RESET, DATA, READONLY
	EXPORT __Vectors
__Vectors
	DCD 0X10001000
	DCD Reset_Handler
	ALIGN
	AREA mycode, CODE, READONLY
	ENTRY
	EXPORT Reset_Handler
	
Reset_Handler
	MOV R5,#-1
	MOV R1, #0XE
	MOV R2, #99
	MOV R3, #0x5555
	MOV R4, #0XF
	MOV R6, #-2
	
	LDR R0, =SARRAY
	STR R5, [R0],#4
	STR R1, [R0],#4
	STR R2, [R0],#4
	STR R3, [R0],#4
	STR R4, [R0],#4
	STR R6, [R0], #4
	LDR R0, =SARRAY
	ADD R11, R0, #24     ;pointer to last location
	
	MOV32 R3, #5           ;N-1
	
	
OL	LDR R4, [R0]            ; R4=first element the array
	MOV R7, R0
	ADD R7, R7, #4          ; R6=second element array
IL	LDR R6, [R7]            ;
	CMP R6, R4              ; CHECK IF SECOND ELEMENT IS LESSER THAN FIRST
	BLE L1
	B LL1
L1      MOV R8, R7                  ; MOVE THE ADDR OF LESSER ELEMENT IN R8
	    LDR R4, [R8]                ; LOAD THE LESSER ELEMENT IN R4
LL1     ADD R7, R7,#4               ; INCREMENT THE ADDRESS POINTER BY 4
	CMP R7, R11                 ; IF R7 and R11 POINTS TO SAME ADDRESS , STOP INNER LOOP
	BNE IL
	
	LDR R5, [R0]            ; PUT THE SMALLEST LOCATION IN THE FIRST PLACE
	STR R4, [R0]
	STR R5, [R8]
L2 	SUB R3, R3, #1            ; REDUCE THE ITERATION OF OUTERLOOP BY ONE
	CMP R3, #0
	BEQ STOP
        ADD R0, R0, #4           ;MAKE SECOND ELEMENT IN THE ARRAY AS THE FIRST ELEMENT OF THE ARRAY TO START NEXT ITERATION OF THE OUTER LOOP

	MOV R8, R0                 
	
	B OL
STOP B STOP

	AREA MDATA, DATA, READWRITE
SARRAY DCD 0
	END
	
	
	
	