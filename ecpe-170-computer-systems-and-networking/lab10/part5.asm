# A Stub to develop assembly code using QtSPIM

	# Declare main as a global function
	.globl main 

	# All program code is placed after the
	# .text assembler directive
	.text 		

# The label 'main' represents the starting point
main:
    # Register map
    # s0 = i = 0
    # s1 = Address of string
    # s2 = Result memory address, 0 by default
    la $s1, string # Get address of string

    li $v0, 4 # Syscall 4 -> print_string
    la $a0, msg1 # Load address of msg1 to print
    syscall # execute

    li $v0, 8 # Syscall 8 -> read_string
    syscall 
    # Returns:
    # $a0, memory address of string input buffer
    # $a1, length of string buffer (n)
    
    move $t0, $a0 # Copy buffer address to temporary register
    li $t3, 'e' # Load value of 'e' into $t3 for comparison

    while:
        beq $t0, $zero, endwhile # If buffer address is null, break while
        add $t1, $t0, $s0 # Offset $t0 by $s0 and store new address in $t1
        lbu $t2, 0($t1) # Load character at string[i] into t2
        beq $t2, $zero, endwhile # If buffer address is null, break while
        if:
            bne $t2, $t3, endif # If string[i] != 'e', exit if
            move $s2, $t1 # Else, copy $t1, address of string[i] to $s2
            j endwhile # Then break while loop
        endif:
        addi $s0, $s0, 1 # i++
        j while
    endwhile:

    if2:
        beq $s2, $zero, else2 # If result is null, exit if

        # Print "First match at address "
        li $v0, 4
	    la $a0, msg2
	    syscall

        # Print address as integer
        li $v0, 1
	    move $a0, $s2
	    syscall

        # Print newline
        li $v0, 4
	    la $a0, newline
	    syscall

        # Print "The matching character is "
        li $v0, 4
	    la $a0, msg3
	    syscall

        # Print address as integer
        lbu $t0, 0($s2) # Load the character from memory address
        li $v0, 11
	    move $a0, $t0
	    syscall
        j endif2
    else2:
        # Print "No match found"
        li $v0, 4
	    la $a0, msg4
	    syscall
        j endif2
    endif2:
    # Print results

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
    string: .space 256 # Space for 256 chars
    msg1: .asciiz "Enter a word:   "
    msg2: .asciiz "First match at address "
    msg3: .asciiz "The matching character is "
    msg4: .asciiz "No match found\n"
    newline: .asciiz "\n"
