# A Stub to develop assembly code using QtSPIM

	# Declare main as a global function
	.globl main 

	# All program code is placed after the
	# .text assembler directive
	.text 		

# The label 'main' represents the starting point
main:
    # Declaring variables
    # Register map
    # $s0 = A = 15
    # $s1 = B = 10
    # $s2 = C = 7
    # $s3 = D = 2
    # $s4 = E = 18
    # $s5 = F = -3
    # $s6 = Z = 0
    addi $s0, $zero, 15
    addi $s1, $zero, 10
    addi $s2, $zero, 7
    addi $s3, $zero, 2
    addi $s4, $zero, 18
    addi $s5, $zero, -3 # Apparently negative values are acceptable
    addi $s6, $zero, 0

    # Perform operations in parentheses
    add $t0, $s0, $s1 # A + B
    sub $t1, $s2, $s3 # C - D
    add $t2, $s4, $s5 # E + F
    sub $t3, $s0, $s2 # A - C
    
    # Perform operations outside of parentheses
    # Temporary registers will be reused
    add $t0, $t0, $t1 # (A + B) + (C - D)
    sub $t2, $t2, $t3 # (E + F) - (A - C)
    add $s6, $t0, $t2 # (A + B) + (C - D) + (E + F) - (A - C)

    # Store $s6 in memory
    la $t0, Z # Get address of Z
    sw $s6, 0($t0) # Store value of $s6 at address of Z in memory


	# Exit the program by means of a syscall.
	# There are many syscalls - pick the desired one
	# by placing its code in $v0. The code for exit is "10"

	li $v0, 10 # Sets $v0 to "10" to select exit syscall
	syscall # Exit

	# All memory structures are placed after the
	# .data assembler directive
	.data
    Z: .word 0

	# The .word assembler directive reserves space
	# in memory for a single 4-byte word (or multiple 4-byte words)
	# and assigns that memory location an initial value
	# (or a comma separated list of initial values)
	#For example:
	#value:	.word 12
