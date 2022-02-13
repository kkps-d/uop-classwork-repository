# A Stub to develop assembly code using QtSPIM

	# Declare main as a global function
	.globl main 

	# All program code is placed after the
	# .text assembler directive
	.text 		

# The label 'main' represents the starting point
main:

	# Exit the program by means of a syscall.
	# There are many syscalls - pick the desired one
	# by placing its code in $v0. The code for exit is "10"
    # Load variables from memory and store them into registers
    # Use $t0 to store address of current word
    # Register map
    # $s0 = A
    # $s1 = B
    # $s2 = C
    # $s3 = Z
    # $s4 = Z's address
    la $t0, A # Store address of A in $t0
    lw $s0, 0($t0) # Load value at 0($t0) into $s0
    
    la $t0, B
    lw $s1, 0($t0)

    la $t0, C
    lw $s2, 0($t0)

    la $s4, Z # Store Z address in $s4 because we will use it later
    lw $s3, 0($s4)

    # if (A > B || C < 5)
    bgt $s0, $s1, if # A > B
    addi $t0, $zero, 5 # Set $t0 to 5 for comparison
    blt $s2, $t0, if # C < 5

    # else if ((A > B) && ((C+1) == 7))
    # or: ((A <= B) || ((C+1) != 7))
    ble $s0, $s1, else # A <= B
    addi $s2, $s2, 1 # C = C + 1
    addi $t0, $zero, 7 # Set $t0 to 7 for comparison
    bne $s2, $t0, else
    # If all above statements are false,
    # (A > B) && ((C+1) == 7) is true,
    # thus jump to elif
    j elif
    
    # Accidentally optimized the program, I'll just leave this here
    # Gets rid of line 65 - 94
    # if:
    #     addi $s3, $zero, -1 # Z = -1
    #     j endif
    # elif:
    #     addi $s3, $s3, -2 # Z -= -2
    #     j endif
    # else:
    #     addi $s3, $zero, 0 # Z = 0
    #     j endif
    # endif:

    # Set Z value according to branch
    if:
        addi $s3, $zero, 1 # Z = 1
        j endif
    elif:
        addi $s3, $zero, 2 # Z = 2
        j endif
    else:
        addi $s3, $zero, 3 # Z = 3
        j endif
    endif:
    
    # Start switch statement
    # Store temporary values in $t0 for comparison
    addi $t0, $zero, 1 # Set $t0 to 1 for comparison
    beq $s3, $t0, caseA # Goto switch case 1 if Z = 1
    addi $t0, $zero, 2 # Set $t0 to 2 for comparison
    beq $s3, $t0, caseB # Goto switch case 2 if Z = 2
    j default # Goto default for any other number

    caseA:
        addi $s3, $zero, -1 # Z = -1
        j endswitch
    caseB:
        addi $s3, $s3, -2 # Z -= -2
        j endswitch
    default:
        addi $s3, $zero, 0 # Z = 0
        j endswitch
    endswitch:

    # Store Z in memory and not A-C because only Z was modified
    sw $s3, 0($s4)

	li $v0, 10 # Sets $v0 to "10" to select exit syscall
	syscall # Exit

	# All memory structures are placed after the
	# .data assembler directive
	.data
    # Declare variables in memory
    A: .word 10
    B: .word 15
    C: .word 6
    Z: .word 0

	# The .word assembler directive reserves space
	# in memory for a single 4-byte word (or multiple 4-byte words)
	# and assigns that memory location an initial value
	# (or a comma separated list of initial values)
	#For example:
	#value:	.word 12
