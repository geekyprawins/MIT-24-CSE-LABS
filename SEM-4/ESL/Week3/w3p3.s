	AREA    RESET, DATA, READONLY
    EXPORT  __Vectors

__Vectors 
      DCD  0x10001000     ; stack pointer value when stack is empty
      DCD  Reset_Handler  ; reset vector
      ALIGN
      AREA mycode, CODE, READONLY
      ENTRY
      EXPORT Reset_Handler
		
Reset_Handler
		LDR R0, =n1 
		ldr r1, =n2
		ldr r6, =lcm
		ldrb r2, [r0]
		ldrb r3, [r1]
		mov r7, r2
		mov r8, r3
back	cmp r2, r3
		beq exit
		bcs down
		sub r3, r2
		b back
down    sub r2, r3
		b back
exit 	ldr r0, =gcd
		strb r2, [r0]
		mov r5, #0
		mul r7, r8
		ldr r4, [r0]
		cmp r4, #1
		beq prod
up		sub r7, r4
		add r5, #1
		cmp r7, #0
		bne up
        str r5, [r6]
		b STOP
prod    str r7, [r6]

STOP
		B STOP          ; Be there
n1 		dcd 4
n2 		dcd 2
		AREA mydata, DATA, READWRITE
gcd 	DCD 0
lcm     dcd 0	
		END