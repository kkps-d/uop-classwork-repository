# A Stub to develop assembly code using QtSPIM

	# Declare main as a global function
	.globl main 

	# All program code is placed after the
	# .text assembler directive
	.text 		

# The label 'main' represents the starting point
main:
    # Register map
    # $s0 - arraySize
    # $t0 - address of arraySize / address of array
    # $t1 - i = 0
    # $t2 - i * 4
    # $t3 - 4
    # $t4 - store address for pointer arithmetic
    # $t5 - an element of array
    la $t0, arraySize # Load address of arraySize into t0
    lw $s0, 0($t0) # Load int at address into s0
    
    la $t0, array # Load address of arraySize into t0
    li $t1, 0 # i = 0
    li $t3, 4 # 4 to multiply with i for pointer arithmetic
    for:
        bge $t1, $s0, endfor # if i >= arraySize, exit for

        li $v0, 4 # Sets syscall code to print_string
        la $a0, msg1 # Set address of message to be printed
        syscall # Prints "Array["

        li $v0, 1 # Sets syscall code to print_int
        move $a0, $t1 # Set integer to be printed
        syscall # Prints integer

        # Prints "]="
        li $v0, 4
        la $a0, msg2
        syscall 

        mul $t2, $t1, $t3 # t2 = i * 4
        # Need to move forward in memory (i * 4) because
        # an int is 4 bytes
        add $t4, $t0, $t2 # new pointer = array pointer + (i * 4)
        lw $t5, 0($t4) # Gets value of array[i]

        # Prints integer
        li $v0, 1
        move $a0, $t5
        syscall

        # Prints "\n"
        li $v0, 4
        la $a0, newline
        syscall

        addi $t1, $t1, 1 # Increment i
        j for
    endfor:

    # Prints "Sum of array is "
    li $v0, 4
    la $a0, msg3
    syscall

    # Call arraySum(array, arraySize)
    # Load arguments
    la $a0, array # array pointer
    lw $a1, arraySize # arraySize
    
    jal arraySum

    # Prints arraySum()'s return
    move $a0, $v0
    li $v0, 1
    syscall

    # Prints "\n"
    li $v0, 4
    la $a0, newline
    syscall


	# Exit the program by means of a syscall.
	# There are many syscalls - pick the desired one
	# by placing its code in $v0. The code for exit is "10"

	li $v0, 10 # Sets $v0 to "10" to select exit syscall
	syscall # Exit

    arraySum:
        # Register map
        # $v0 - result return
        # $a0 - array pointer
        # $a1 - arraySize
        # $t0 - result

        if:
            bne $a1, $zero, else # if arraySize != 0, goto else
            # if equals...
            li $t0, 0 # result = 0
            j endif
        else:
            # Push a0, a1 and ra to stack
            addi $sp, $sp, -4
            sw $a0, 0($sp)
            addi $sp, $sp, -4
            sw $a1, 0($sp)
            addi $sp, $sp, -4
            sw $ra, 0($sp)

            addi $a0, $a0, 4 # location of array[1]
            addi $a1, $a1, -1 # arraySize - 1
            jal arraySum # call arraySum()

            # Retrieve a0, a1 and ra from stack
            lw $ra, 0($sp)
            addi $sp, $sp, 4
            lw $a1, 0($sp)
            addi $sp, $sp, 4
            lw $a0, 0($sp)
            addi $sp, $sp, 4

            lw $t1, 0($a0) # int at *array
            add $t0, $t1, $v0 # int at *array + arraySum return
        endif:
        move $v0, $t0 # return result
        jr $ra # return from function

        

	# All memory structures are placed after the
	# .data assembler directive
	.data
    array: .word 2, 3, 5, 7, 11 # Initialize a chain of words (array) using the given values
    arraySize: .word 5
    msg1: .asciiz "Array["
    msg2: .asciiz "]="
    msg3: .asciiz "Sum of array is "
    newline: .asciiz "\n"
