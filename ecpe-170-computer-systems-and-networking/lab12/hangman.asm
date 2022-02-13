# A Stub to develop assembly code using QtSPIM

	# Declare main as a global function
	.globl main 

	# All program code is placed after the
	# .text assembler directive
	.text 		

# The label 'main' represents the starting point
main:
    # Register map throughout the program
    # s0 - word_length
    # s1 - used_letters_length
    # s2 - wrong_counter
    # s3 - state

    # Get length of WORD_GUESS and store it
    # inside word_length
    # Register map
    # i is not needed, will be replaced with pointer arithmetic
    # t0 - WORD_GUESS's address
    # t1 - value at WORD_GUESS's address
    li $s0, 0 # word_length = 0
    li $s1, 0 # used_letters_length = 0
    li $s2, 0 # wrong_counter = 0
    la $t0, WORD_GUESS # Store WORD_GUESS's address in t1

    while:
        lbu $t1, 0($t0) # load char of size 1 byte at address $t0 into $t1
        beq $t1, $zero, endwhile # if char == null, exit while 
        # if not null...
        addi $t0, $t0, 1 # Move pointer forward
        addi $s0, $s0, 1 # Increment word_length
        j while
    endwhile:

    # Fill word_buffer with '_'s to word length and null terminate
    # Register map
    # $t0 - i = 0
    # $t1 - word_buffer's address
    # $t2 - '_'
    li $t0, 0 # i = 0
    la $t1, word_buffer # Store word_buffer's address in t1
    li $t2, '_'
    for:
        bge $t0, $s0, endfor # if i >= word_length, exit for
        sb $t2, 0($t1) # Store char '_' of size 1 byte in $t2 to address at $t1
        addi $t1, 1 # Increment word_buffer pointer 
        addi $t0, 1 # Increment i
        j for
    endfor:
    # No need to null terminate as spaces are 0 by default, 0 = '\0'

    # Print "Welcome to Hangman"
    li $v0, 4
    la $a0, welcome
    syscall

    # Print "Implemented by Kaung"
    li $v0, 4
    la $a0, welcome2
    syscall

    # State of the game
    # 0 - not won, 1 - won, 2 - lost
    li $s3, 0 # state = 0

    # Run game loop
    # Register map
    # $t0 - c
    # $t1 - '0'
 
    while_0:
        bne $s3, $zero, endwhile_0 # if state != 0, exit while
        jal print_game # Call print_game()
        jal user_input # Call user_input()
        move $t0, $v0 # c = user_input()
        if_c:
            li $t1, '0' # Load '0' into t1 for if comparison
            bne $t0, $t1, end_c # if c != '0', exit if
            # if equals...
            # Exit program
            li $v0, 10
	        syscall
        end_c:
        move $a0, $t0 # Set c as first argument
        jal check_game # Call check_game(c)
        move $s3, $v0 # state = check_game(c)
        j while_0
    endwhile_0:

    # Check whether user has won or lost and
    # print relevant message
    # Register map
    # $t0 = 1, for if comparison
    li $t0, 1 # t0 = 1 for if comparison
    if_won:
        bne $s3, $t0, else_won # if state != 1, goto else
        jal print_game

        # Print "Congratulations - you win!"
        li $v0, 4
        la $a0, win
        syscall

        j endif_won
    else_won:
        jal print_game

        # Print "You lose - out of moves!"
        li $v0, 4
        la $a0, lose
        syscall
    endif_won:

	# Exit the program by means of a syscall.
	# There are many syscalls - pick the desired one
	# by placing its code in $v0. The code for exit is "10"

	li $v0, 10 # Sets $v0 to "10" to select exit syscall
	syscall # Exit

    # Functions

    # Prints the ascii art for hangman
    print_game:
        # No registers are pushed to stack as no $s registers are used
        # Register map
        # t0 - Contains numbers for if and switch comparisons
        li $v0, 4
        la $a0, art1
        syscall

        # Prints word_buffer which stores the word but replaced with '_'s
        li $v0, 4
        la $a0, word_buffer
        syscall

        li $v0, 4
        la $a0, art2
        syscall

        # Prints art with head if wrong_counter >= 1, else no head
        li $t0, 1
        blt $s2, $t0, else # if wrong_counter < 1, goto else 
        if:
            li $v0, 4
            la $a0, art3_1_a
            syscall
            j endif
        else:
            li $v0, 4
            la $a0, art3_1_b
            syscall
        endif:

        li $v0, 4
        la $a0, art3_2
        syscall
        
        # Prints missed letters
        li $v0, 4
        la $a0, missed_letters
        syscall

        # First switch statement
        switch:
            # Check for cases and goto them
            li $t0, 2
            beq $s2, $t0, case_2 # if wrong_counter == 2, goto case_2

            li $t0, 3
            beq $s2, $t0, case_3 # if wrong_counter == 3, goto case_3

            li $t0, 4
            beq $s2, $t0, case_4_5_6 # if wrong_counter == 4, goto case_4_5_6

            li $t0, 5
            beq $s2, $t0, case_4_5_6 # if wrong_counter == 5, goto case_4_5_6

            li $t0, 6
            beq $s2, $t0, case_4_5_6 # if wrong_counter == 6, goto case_4_5_6

            # if doesnt match with cases above, fall into default
            default:
                li $v0, 4
                la $a0, art4_a
                syscall
                j endswitch

            case_2:
                li $v0, 4
                la $a0, art4_b
                syscall
                j endswitch

            case_3:
                li $v0, 4
                la $a0, art4_c
                syscall
                j endswitch

            case_4_5_6:
                li $v0, 4
                la $a0, art4_d
                syscall
        endswitch:

        # Second switch statement
        switch_2:
            # Check for cases and goto them
            li $t0, 5
            beq $s2, $t0, case_5 # if wrong_counter == 5, goto case_5

            li $t0, 6
            beq $s2, $t0, case_6 # if wrong_counter == 6, goto case_6

            # if doesnt match with cases above, fall into default
            default_2:
                li $v0, 4
                la $a0, art5_a
                syscall
                j endswitch_2

            case_5:
                li $v0, 4
                la $a0, art5_b
                syscall
                j endswitch_2

            case_6:
                li $v0, 4
                la $a0, art5_c
                syscall
        endswitch_2:

        li $v0, 4
        la $a0, art6
        syscall

        li $v0, 4
        la $a0, art7
        syscall

        jr $ra # Return from function
    
    # Gets user input and returns it
    user_input:
        # No registers are pushed to stack as no $s registers are used
        # Register map
        # v0 - return register, contains user input char
        # t0 - c, user input
        # t1 - '0' for if comparison
        # t2 - i = 0
        # t3 - 26 for for comparison
        # t4 - accept array address
        # t5 - loaded character from ACCEPT array

        li $t1, '0' # '0' for if comparison
        li $t3, 26 # 26 for for comparison

        # Start of infinite while loop
        while_inf:
            # Print "Enter next character (A-Z), or 0 (zero) to exit: "
            li $v0, 4
            la $a0, enter_c
            syscall

            # Read char from user input
            li $v0, 12
            syscall
            move $t0, $v0 # Move read_char results into t0

            # # Print char debug
            # move $a0, $t0
            # li $v0, 11
            # syscall

            if_0:
                bne $t0, $t1, endif_0 # if c != '0' exit if
                # if equals...
                move $v0, $t0 # move '0' to return register
                jr $ra # return from function
            endif_0:

            la $t4, ACCEPT # Load address of accept array

            li $t2, 0 # i = 0
            for_input:
                bge $t2, $t3, endfor_input # if i >= 26, exit for

                if_accept:
                    lbu $t5, 0($t4) # Load char from address of ACCEPT array
                    bne $t5, $t0, endif_accept # if ACCEPT[i] != c, exit if 
                    # if equals...
                    move $v0, $t5 # Move ACCEPT[i] to return register
                    jr $ra # Return from function
                endif_accept:

                addi $t2, $t2, 1 # Increment i
                addi $t4, $t4, 1 # Increment ACCEPT's pointer
                j for_input
            endfor_input:

            # Print "Enter next character (A-Z), or 0 (zero) to exit: "
            li $v0, 4
            la $a0, invalid_c
            syscall
            
            j while_inf
        endwhile_inf:

    # Checks if input char is used or not, and if the game is won or lost
    # Returns game state
    check_game:
        # No registers are pushed to stack as no $s registers are used
        # Register map
        # a0 - first function char c
        # v0 - function return, contains game state
        # t0 - 1st argument c
        # t1 - i = 0, for for loops
        # t2 - word_replaced = 0, whether a word was replaced or not
        # t3 - used_letters, missed_letters & word_buffer address
        # t4 - WORD_GUESS address
        # t5 - temporary char from loaded from arrays
        # t6 - another temp char
        # t7 - temp int for if comparisons
        move $t0, $a0 # Move first argument into t0
        
        li $t1, 0 # i = 0
        la $t3, used_letters # load address of used_letters into t3
        for_used:
            bge $t1, $s1, endfor_used # if i >= used_letters_length, exit for
            
            if_used:
                lbu $t5, 0($t3) # load char at used_letters[i] into t5
                bne $t5, $t0, endif_used # if used_letters[i] != c, exit if
                # if equals...
                # Print "- Letter already used -"
                li $v0, 4
                la $a0, used_c
                syscall

                li $v0, 0 # Return 0
                jr $ra # Return from function
            endif_used:
            
            addi $t1, $t1, 1 # increment i
            addi $t3, $t3, 1 # increment used_letters pointer
            j for_used
        endfor_used:

        # New letter, add to used letters and increment length
        la $t3, used_letters # Reload address of used_letters into t3 because it was modified
        add $t3, $t3, $s1 # used_letters[used_letters_length]
        sb $t0, 0($t3) # Save c to used_letters[used_letters_length]
        addi $s1, $s1, 1 # Increment used_letters_length

        # Replace words in word_buffer if exists
        li $t2, 0 # word_replaced = 0
        la $t4, WORD_GUESS # Load address of WORD_GUESS into t4
        la $t3, word_buffer # Load address of word_buffer into t3
        li $t1, 0 # i = 0
        for_replaced:
            bge $t1, $s0, endfor_replaced # if i >= word_length, exit for
            
            if_replaced:
                lbu $t5, 0($t4) # Load char at WORD_GUESS[i] into t5
                bne $t5, $t0, endif_replaced # if WORD_GUESS[i] != c, exit if
                # if equals...
                sb $t0, 0($t3) # Save c to word_buffer[i]
                li $t2, 1 # word_replaced = 1
            endif_replaced:

            addi $t1, $t1, 1 # Increment i
            addi $t3, $t3, 1 # Increment word_buffer pointer
            addi $t4, $t4, 1 # Increment WORD_GUESS pointer
            j for_replaced
        endfor_replaced:

        # If no words were replaced, wrong letter picked
        # Increment wrong_counter and add to missed_letters
        if_replaced_2:
            bne $t2, $zero, else_replaced_2 # if word_replaced != 0, goto else
            la $t3, missed_letters # Load missed_letters's address into t3
            add $t3, $t3, $s2 # missed_letters[wrong_counter]
            sb $t0, 0($t3) # missed_letters[wrong_counter] = c
            addi $s2, $s2, 1 # Increment wrong_counter
            # No need to null terminate as spaces are 0 by default, 0 = '\0'

            if_6:
                li $t7, 6
                bne $s2, $t7, endif_6 # if wrong_counter != 6, exit if
                # if equals...
                li $v0, 2 # Return 2
                jr $ra # Return from function
            endif_6:

            li $v0, 0 # Return 0
            jr $ra # Return from function 
        else_replaced_2:
            li $t1, 0 # i = 0
            la $t4, WORD_GUESS # Load WORD_GUESS's address into t4
            la $t3, word_buffer # Load word_buffer's address into t3
            for_won:
                bge $t1, $s0, endfor_won # if i >= word_length, exit for

                if_equals:
                    
                    lbu $t5, 0($t4) # Load char at WORD_GUESS's address into t5
                    lbu $t6, 0($t3) # Load char at word_buffer's address into t6
                    beq $t5, $t6, endif_equals # if WORD_GUESS[i] == word_buffer[i], exit if
                    # if not equal...
                    li $v0, 0 # Return 0
                    jr $ra # Return from function
                endif_equals:

                addi $t1, $t1, 1 # Increment i
                addi $t3, $t3, 1 # Increment word_buffer pointer
                addi $t4, $t4, 1 # Increment WORD_GUESS pointer
                j for_won
            endfor_won:
            li $v0, 1 # Return 0
            jr $ra # Return from function

	# All memory structures are placed after the
	# .data assembler directive
	.data
    WORD_GUESS: .asciiz "HANGMAN" # The word to guess
    ACCEPT: .asciiz "ABCDEFGHIJKLMNOPQRSTUVWXYZ" # List of alphabets to accept
    word_buffer: .space 46 # word_buffer[46]
    used_letters: .space 26 # used_letters[26]
    missed_letters: .space 7 # missed_letters[7]

    # Messages
    welcome: .asciiz "Welcome to Hangman!\n"
    welcome2: .asciiz "Implemented by Kaung\n\n"
    enter_c: .asciiz "Enter next character (A-Z), or 0 (zero) to exit: "
    invalid_c: .asciiz "\n- Invalid input -\n"
    used_c: .asciiz "\n- Letter already used -\n"
    win: .asciiz "\nCongratulations - you win!\n"
    lose: .asciiz "\nYou lose - out of moves!\n"

    # Ascii art for hangman
    art1: .asciiz "\n   |-----|   Word: "
    art2: .asciiz "\n   |     |\n"
    art3_1_a: .asciiz "   O     |   "
    art3_1_b: .asciiz "         |   "
    art3_2: .asciiz "Misses: "
    art4_a: .asciiz "\n         |\n         |\n"
    art4_b: .asciiz "\n   |     |\n   |     |\n"
    art4_c: .asciiz "\n  \|     |\n   |     |\n"
    art4_d: .asciiz "\n  \|/    |\n   |     |\n"
    art5_a: .asciiz "         |\n"
    art5_b: .asciiz "  /      |\n"
    art5_c: .asciiz "  / \    |\n"
    art6: .asciiz "         |\n"
    art7: .asciiz " ---------\n"

    # Newline
    newline: .asciiz "\n"
    