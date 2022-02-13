# A Stub to develop assembly code using QtSPIM

	# Declare main as a global function
	.globl main 

	# All program code is placed after the
	# .text assembler directive
	.text 		

# The label 'main' represents the starting point
main:
    # Register map
    # $s0 = m_w
    # $s1 = m_z
    # $s2 = n1
    # $s3 = n2
    # $t0 = i, Must be pushed to stack before calling functions
    # $t1 = 10, Used for loop checking, also push to stack before functions
    # $t2, result of gcd(), no need to be pushed

    # Initialize variables to their values
    # Set m_w, m_z, i and t1 = 10
    li $s0, 50000 # m_w = 50000
    li $s1, 60000 # m_z = 60000
    li $t0, 0 # i = 0
    li $t1, 10 # i = 10
    
    # For loop starts below
    for:
        bge $t0, $t1, endfor # Exit for if i >= 10

        # Backup $t0 and $t1 to stack
        addi $sp, $sp, -4 # Move pointer 4 bytes back
        sw $t0, 0($sp) # Save t0 to current pointer location
        addi $sp, $sp, -4 # Move pointer 4 bytes back
        sw $t1, 0($sp) # Save t1 to current pointer location

        # Generate two random numbers using random_in_range
        li $a0, 1 # Set first argument to 1
        li $a1, 10000 # Set second argument to 10000
        jal random_in_range # Call first function 
        move $s2, $v0 # Copy results of first function to n1

        li $a0, 1 # Set first argument to 1
        li $a1, 10000 # Set second argument to 10000
        jal random_in_range # Call second function 
        move $s3, $v0 # Copy results of second function to n2

        # Call gcd(n1, n2)
        move $a0, $s2 # Move n1 to first argument
        move $a1, $s3 # move n2 to second argument
        jal gcd # Call gcd
        move $t2, $v0 # Move gcd() results to t2

        # printf starts here
        la $a0, text1 # Load address for text1
        li $v0, 4 # Set syscall for print_int
        syscall # Print string

        move $a0, $s2 # Set integer n1 to be printed
        li $v0, 1 # Set syscall for print_int
	    syscall # Print int
        
        la $a0, text2 # Load address for text2
        li $v0, 4 # Set syscall for print_int
        syscall # Print string

        move $a0, $s3 # Set integer n2 to be printed
        li $v0, 1 # Set syscall for print_int
	    syscall # Print int

        la $a0, text3 # Load address for text3
        li $v0, 4 # Set syscall for print_int
        syscall # Print string

        move $a0, $t2 # Set integer gcd result to be printed
        li $v0, 1 # Set syscall for print_int
	    syscall # Print int

        la $a0, text4 # Load address for text4
        li $v0, 4 # Set syscall for print_int
        syscall # Print string

        # Restore $t0 and $t1 from stack
        lw $t1, 0($sp) # Load from current pointer location into $t1
        addi $sp, $sp, 4 # Move pointer 4 bytes forward
        lw $t0, 0($sp) # Load from current pointer location into $t0
        addi $sp, $sp, 4 # Move pointer 4 bytes forward

        addi $t0, $t0, 1 # i++
        j for # Go back to top of loop
    endfor:
	# Exit the program by means of a syscall.
	# There are many syscalls - pick the desired one
	# by placing its code in $v0. The code for exit is "10"

	li $v0, 10 # Sets $v0 to "10" to select exit syscall
	syscall # Exit

    # random_in_range, get_random, gcd are placed
    # Function to generate a random number
    get_random:
        # $s2-$s7 registers are not pushed to stack,
        # none of them are modified in this function
        # $s0 and $s1 are not pushed to stack as we 
        # want them to be modified by the function

        # Register map
        # $v0 = result
        # The following temp registers are used for logic
        # throughout the function
        # $t0 = 36969
        # $t1 = 18000
        # $t2 = 65535
        # $t3 = 16
        # $t4-$t6, Used for calculations

        li $t0, 36969
        li $t1, 18000
        li $t2, 65535
        li $t3, 16

        and $t4, $s1, $t2 # m_z & 65535, copies bit that are equal
        srl $t5, $s1, $t3 # m_z >> 16, shifts bit right
        mul $t6, $t0, $t4 # 36969 * (m_z & 65535)
        addu $s1, $t6, $t5 # m_z = 36969 * (m_z & 65535) + (m_z >> 16)

        and $t4, $s0, $t2 # m_w & 65535, copies bit that are equal
        srl $t5, $s0, $t3 # m_w >> 16, shifts bit right
        mul $t6, $t1, $t4 # 18000 * (m_w & 65535)
        addu $s0, $t6, $t5 # m_w = 18000 * (m_w & 65535) + (m_w >> 16)

        sll $t4, $s1, $t3 # (m_z << 16)
        addu $v0, $t4, $s0 # result = (m_z << 16) + m_w, move to result register

        # Nothing is popped as nothing was pushed to stack
        
        jr $ra # return from function

    # Function to generate a random number within a range
    random_in_range:
        # $s2-$s7 registers are not pushed to stack,
        # none of them are modified in this function
        # $s0 and $s1 are not pushed to stack as we 
        # want them to be modified by the function

        # Register map
        # $v0 = return register
        # $t0 = range
        # $t1 = rand_num
        # $t2, used for calculations
        # $a0 = low
        # $a1 = high

        sub $t2, $a1, $a0 # high - low
        addi $t0, $t2, 1 # range = high - low + 1
        
        # Push $ra and $t0-$t2 to stack to preserve values
        addi $sp, $sp, -4 # Move pointer 4 bytes back
        sw $ra, 0($sp) # Save ra to current pointer location
        addi $sp, $sp, -4 # Move pointer 4 bytes back
        sw $t0, 0($sp) # Save t0 to current pointer location
        addi $sp, $sp, -4 # Move pointer 4 bytes back
        sw $t1, 0($sp) # Save t1 to current pointer location
        addi $sp, $sp, -4 # Move pointer 4 bytes back
        sw $t2, 0($sp) # Save t2 to current pointer location

        # Call get_random() function and store in rand_num
        jal get_random # Call get_random()
        
        # Restore original values from stack
        lw $t2, 0($sp) # Load from current pointer location into $t2
        addi $sp, $sp, 4 # Move pointer 4 bytes forward
        lw $t1, 0($sp) # Load from current pointer location into $t1
        addi $sp, $sp, 4 # Move pointer 4 bytes forward
        lw $t0, 0($sp) # Load from current pointer location into $t0
        addi $sp, $sp, 4 # Move pointer 4 bytes forward
        lw $ra, 0($sp) # Load from current pointer location into $ra
        addi $sp, $sp, 4 # Move pointer 4 bytes forward

        # Move results of get_random() into rand_num
        move $t1, $v0 # Store return value in rand_num

        divu $t1, $t0 # rand_num / range, need remainder in HI
        mfhi $t2 # Move remainder from HI to $t2
        addu $v0, $t2, $a0 # store (rand_num % range) + low in return register

        # Nothing is popped as no $s registers were pushed to stack

        jr $ra # return from function

    # Function to find greatest common denominator
    gcd:
        # $s registers are not pushed to stack, as
        # none of them are modified in this function

        # Register Map
        # $a0 = n1
        # $a1 = n2
        # $t0, contains backup of n1
        if:
            beq $a1, $zero, else # if n2 == 0, go to else

            # Push $ra to stack to preserve values
            addi $sp, $sp, -4 # Move pointer 4 bytes back
            sw $ra, 0($sp) # Save ra to current pointer location

            # Prepare arguments for function call
            move $t0, $a0 # backup n1 to t0
            move $a0, $a1 # set n2 as first argument for function
            divu $t0, $a1 # n1 / n2
            mfhi $a1 # Copy remainder from HI into second argument

            # Call gcd recursively
            jal gcd

            # Restore $ra
            lw $ra, 0($sp) # Load from current pointer location into $ra
            addi $sp, $sp, 4 # Move pointer 4 bytes forward

            j return # Return from function

        else:
            move $v0, $a0 # Move n1 to return register
            j return # Return from function

        return: 
            # Nothing is popped as nothing was pushed to stack

            jr $ra # Return from function

    
	# All memory structures are placed after the
	# .data assembler directive
	.data
    text1: .asciiz "\n G.C.D of "
    text2: .asciiz " and "
    text3: .asciiz " is "
    text4: .asciiz "."

	# The .word assembler directive reserves space
	# in memory for a single 4-byte word (or multiple 4-byte words)
	# and assigns that memory location an initial value
	# (or a comma separated list of initial values)
	#For example:
	#value:	.word 12
