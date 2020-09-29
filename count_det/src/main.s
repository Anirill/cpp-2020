.data
.balign 4
result:
	.word 0
.balign 4
myvar_1:
	.word 1
.balign 4
myvar_2:
	.word 1
.balign 4
myvar_3:
	.word 1
.text
.global count_det
count_det:
	mov r2, r0	
	
	ldrb r3, [r2], #4
        ldr r1, addr_of_myvar_1
        ldr r1, [r1]
	mul r3, r1, r3
	ldr r1, addr_of_myvar_1
        str r3, [r1]
       
	ldrb r3, [r2], #4
        ldr r1, addr_of_myvar_2
        ldr r1, [r1]
        mul r3, r1, r3
        ldr r1, addr_of_myvar_2
        str r3, [r1]

        ldrb r3, [r2], #4
        ldr r1, addr_of_myvar_3
        ldr r1, [r1]
        mul r3, r1, r3
        ldr r1, addr_of_myvar_3
        str r3, [r1]

        ldrb r3, [r2], #4
        ldr r1, addr_of_myvar_3
        ldr r1, [r1]
        mul r3, r1, r3
        ldr r1, addr_of_myvar_3
        str r3, [r1]

        ldrb r3, [r2], #4
        ldr r1, addr_of_myvar_1
        ldr r1, [r1]
        mul r3, r1, r3
        ldr r1, addr_of_myvar_1
        str r3, [r1]

        ldrb r3, [r2], #4
        ldr r1, addr_of_myvar_2
        ldr r1, [r1]
        mul r3, r1, r3
        ldr r1, addr_of_myvar_2
        str r3, [r1]

        ldrb r3, [r2], #4
        ldr r1, addr_of_myvar_2
        ldr r1, [r1]
        mul r3, r1, r3
        ldr r1, addr_of_myvar_2
        str r3, [r1]

        ldrb r3, [r2], #4
        ldr r1, addr_of_myvar_3
        ldr r1, [r1]
        mul r3, r1, r3
        ldr r1, addr_of_myvar_3
        str r3, [r1]

        ldrb r3, [r2], #4
        ldr r1, addr_of_myvar_1
        ldr r1, [r1]
        mul r3, r1, r3
        ldr r1, addr_of_myvar_1
        str r3, [r1]



        ldr r2, addr_of_result
        ldr r2, [r2]
        ldr r1, addr_of_myvar_1
        ldr r1, [r1]
        add r2, r1, r2
        ldr r1, addr_of_result
        str r2, [r1]
	
	ldr r2, addr_of_result
        ldr r2, [r2]
	ldr r1, addr_of_myvar_2
        ldr r1, [r1]
	add r2, r1, r2
        ldr r1, addr_of_result
        str r2, [r1]

        ldr r2, addr_of_result
        ldr r2, [r2]
        ldr r1, addr_of_myvar_3
        ldr r1, [r1]
        add r2, r1, r2
        ldr r1, addr_of_result
        str r2, [r1]

	
	ldr r1, addr_of_myvar_1
	mov r2, #-1
	str r2, [r1]
	
	ldr r1, addr_of_myvar_2
	mov r2, #-1
        str r2, [r1]

	ldr r1, addr_of_myvar_3
	mov r2, #-1
        str r2, [r1]

	mov r2, r0

        ldrb r3, [r2], #4
        ldr r1, addr_of_myvar_1
        ldr r1, [r1]
        mul r3, r1, r3
        ldr r1, addr_of_myvar_1
        str r3, [r1]

        ldrb r3, [r2], #4
        ldr r1, addr_of_myvar_2
        ldr r1, [r1]
        mul r3, r1, r3
        ldr r1, addr_of_myvar_2
        str r3, [r1]

        ldrb r3, [r2], #4
        ldr r1, addr_of_myvar_3
        ldr r1, [r1]
        mul r3, r1, r3
        ldr r1, addr_of_myvar_3
        str r3, [r1]

        ldrb r3, [r2], #4
        ldr r1, addr_of_myvar_2
        ldr r1, [r1]
        mul r3, r1, r3
        ldr r1, addr_of_myvar_2
        str r3, [r1]

        ldrb r3, [r2], #4
        ldr r1, addr_of_myvar_3
        ldr r1, [r1]
        mul r3, r1, r3
        ldr r1, addr_of_myvar_3
        str r3, [r1]

        ldrb r3, [r2], #4
        ldr r1, addr_of_myvar_1
        ldr r1, [r1]
        mul r3, r1, r3
        ldr r1, addr_of_myvar_1
        str r3, [r1]

        ldrb r3, [r2], #4
        ldr r1, addr_of_myvar_3
        ldr r1, [r1]
        mul r3, r1, r3
        ldr r1, addr_of_myvar_3
        str r3, [r1]

        ldrb r3, [r2], #4
        ldr r1, addr_of_myvar_1
        ldr r1, [r1]
        mul r3, r1, r3
        ldr r1, addr_of_myvar_1
        str r3, [r1]

        ldrb r3, [r2], #4
        ldr r1, addr_of_myvar_2
        ldr r1, [r1]
        mul r3, r1, r3
        ldr r1, addr_of_myvar_2
        str r3, [r1]


        ldr r2, addr_of_result
        ldr r2, [r2]
        ldr r1, addr_of_myvar_1
        ldr r1, [r1]
        add r2, r1, r2
        ldr r1, addr_of_result
        str r2, [r1]

        ldr r2, addr_of_result
        ldr r2, [r2]
        ldr r1, addr_of_myvar_2
        ldr r1, [r1]
        add r2, r1, r2
        ldr r1, addr_of_result
        str r2, [r1]

        ldr r2, addr_of_result
        ldr r2, [r2]
        ldr r1, addr_of_myvar_3
        ldr r1, [r1]
        add r2, r1, r2
        ldr r1, addr_of_result
        str r2, [r1]



	ldr r0, [r1]
	bx lr


addr_of_result : .word result
addr_of_myvar_1 : .word myvar_1
addr_of_myvar_2 : .word myvar_2
addr_of_myvar_3 : .word myvar_3

	

