# A Stub to develop assembly code using QtSPIM

	# Declare main as a global function
	.globl main 

	# All program code is placed after the
	# .text assembler directive
	.text 		

# The label 'main' represents the starting point
main:
    # Load I and Z from memory
    # Register map
    # $s0 = I = 0
    # $s1 = Z = 2
    # $s2 = Address of I
    # $s3 = Address of Z
    la $s2, I # Get address of I in memory
    lw $s0, 0($s2) # Get I value from address and store in $s0
    la $s3, Z # Get address of Z in memory
    lw $s1, 0($s3) # Get Z value from address and store in $s1

    addi $t0, $zero, 20 # For while look comparison (i > 20)
    while:
        bgt $s0, $t0, endwhile # if (i > 20) break;
        addi $s1, $s1, 1 # Z++
        addi $s0, $s0, 2 # i += 2
        j while
    endwhile:

    addi $t0, $zero, 100 # For while look comparison (Z > 100)
    do:
        addi $s1, $s1, 1 # Z++
        blt $s1, $t0, do # Do while Z < 100
    enddo:

    while2:
        ble $s0, $zero, endwhile2 # exit loop if i <= 0
        addi $s1, $s1, -1 # Z--
        addi $s0, $s0, -1 # i--
        j while2
    endwhile2:

    # Store I and Z in memory
    sw $s0, 0($s2)
    sw $s1, 0($s3)

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
    I: .word 0
    Z: .word 2