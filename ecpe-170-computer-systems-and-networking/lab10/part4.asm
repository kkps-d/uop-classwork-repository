# A Stub to develop assembly code using QtSPIM

	# Declare main as a global function
	.globl main 

	# All program code is placed after the
	# .text assembler directive
	.text 		

# The label 'main' represents the starting point
main:
    # Get addresses of A and B
    # Register map
    # $s0 = address of A
    # $s1 = address of B
    # $s2 = C = 12
    # $s3 = i = 0
    la $s0, A
    la $s1, B

    # Set intial values for B
    addi $t0, $zero, 1 # Set temp to 1
    sw $t0, 0($s1) # Store 1 in B[0]
    addi $t0, $zero, 2 # Set temp to 2
    sw $t0, 4($s1) # Store 2 in B[1]
    addi $t0, $zero, 3 # Set temp to 3
    sw $t0, 8($s1) # Store 3 in B[2]
    addi $t0, $zero, 4 # Set temp to 4
    sw $t0, 12($s1) # Store 4 in B[3]
    addi $t0, $zero, 5 # Set temp to 5
    sw $t0, 16($s1) # Store 5 in B[4]

    # Set value of C and i
    addi $s2, $zero, 12
    addi $s3, $zero, 0

    addi $t0, $zero, 5 # For for comparison (i < 5)
    addi $t1, $zero, 4 # For multiplying array index
    for:
        bge $s3, $t0, endfor # break for if i >= 5

        mul $t2, $s3, $t1 # i * 4 for array access offset
        add $t3, $s1, $t2 # $t3 = address of B + offset $t2
        lw $t4, 0($t3) # Load value at address to $t4
        add $t5, $t4, $s2 # $t5 = B[i] + C
        sw $t5, 0($t3) # Store above value into address of B + offset

        addi $s3, $s3, 1 # i++
        j for
    endfor:

    addi $s3, $s3, -1 # i--

    addi $t0, $zero, 4 # For multiplying array index
    while:
        blt $s3, $zero, endwhile # Break if i less than 0
        mul $t1, $s3, $t0 # i * 4 for array access offset
        add $t2, $s1, $t1 # $t2 = address of B + offset $t1
        lw $t3, 0($t2) # Load value at address to $t3
        add $t3, $t3, $t3 # Multiply it by 2
        sw $t3, 0($t2) # Store it to memory
        addi $s3, $s3, -1 # i--
        j while
    endwhile:

	# Exit the program by means of a syscall.
	# There are many syscalls - pick the desired one
	# by placing its code in $v0. The code for exit is "10"

	li $v0, 10 # Sets $v0 to "10" to select exit syscall
	syscall # Exit

	# All memory structures are placed after the
	# .data assembler directive
	.data

	# The .word assembler directive reserves space
	# in memory for a single 4-byte word (or multiple 4-byte words)
	# and assigns that memory location an initial value
	# (or a comma separated list of initial values)
	#For example:
	#value:	.word 12
    A: .space 20 # Space for 20 / 4 = 5 words
    B: .space 20 # Space for 20 / 4 = 5 words
