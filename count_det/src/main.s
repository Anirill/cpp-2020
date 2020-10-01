.text
.global count_det
count_det:
	mov r3, #0  // result
	
	ldr r1, [r0]  
	add r0, #16
	ldr r2, [r0]
	mul r1, r2, r1
	add r0, #16
	ldr r2, [r0]
	mul r1, r2, r1
	add r3, r1  // result = 0 + a11 * a22 * a33
	
	sub r0, #28
	ldr r1, [r0]
        add r0, #16
        ldr r2, [r0]
        mul r1, r2, r1
        add r0, #4
        ldr r2, [r0]
        mul r1, r2, r1
        add r3, r1  // result + a12 * a23 * a31

        sub r0, #16
        ldr r1, [r0]
        add r0, #4
        ldr r2, [r0]
        mul r1, r2, r1
        add r0, #16
        ldr r2, [r0]
        mul r1, r2, r1
        add r3, r1 // result + a13 * a21 * a32

        sub r0, #28
        ldr r1, [r0]
        add r0, #20
        ldr r2, [r0]
        mul r1, r2, r1
        add r0, #8
        ldr r2, [r0]
        mul r1, r2, r1
        sub r3, r1  // result -  a11 * a23 * a32

        sub r0, #24
        ldr r1, [r0]
        add r0, #8
        ldr r2, [r0]
        mul r1, r2, r1
        add r0, #20
        ldr r2, [r0]
        mul r1, r2, r1
        sub r3, r1  // result -  a12 * a21 * a33

        sub r0, #24
        ldr r1, [r0]
        add r0, #8
        ldr r2, [r0]
        mul r1, r2, r1
        add r0, #8
        ldr r2, [r0]
        mul r1, r2, r1
        sub r3, r1  // result -  a13 * a22 * a31

	mov r0, r3  
	bx lr

