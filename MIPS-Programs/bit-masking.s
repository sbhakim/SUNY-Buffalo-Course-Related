Design an algorithm for a MIPS QTSPIM function called extract_bit that takes two inputs: a 32-bit word 
stored in $a0, and an integer stored in $a1. The function should return the bit at the $a1-th position 
of $a0, where the bit positions are numbered 0 to 31 starting from the right side (LSB). The output of 
the function should be stored in $v0 and should be either 0 or 1. As an example, if we store the value 
b1101 1010 1010 0101 1000 1011 1001 0001 in $a0, set $a1 to 3, then the expected result in $v0 should 
be 0.


.data
prompt: .asciiz "Enter a 32-bit word: "
bit_prompt: .asciiz "Enter a bit position (0-31): "
result: .asciiz "The bit value is: "
newline: .asciiz "\n"

.text
main:
    # Prompt the user to enter the 32-bit word
    li $v0, 4 # syscall code for printing a string
    la $a0, prompt # the string to print
    syscall

    # Read the 32-bit word from the user
    li $v0, 5 # syscall code for reading an integer
    syscall
    move $a0, $v0 # move the input to $a0

    # Prompt the user to enter the bit position
    li $v0, 4 # syscall code for printing a string
    la $a0, bit_prompt # the string to print
    syscall

    # Read the bit position from the user
    li $v0, 5 # syscall code for reading an integer
    syscall
    move $a1, $v0 # move the input to $a1

    # Call the extract_bit function and store the result in $v0
    jal extract_bit

    # Print the result
    li $v0, 4 # syscall code for printing a string
    la $a0, result # the string to print
    syscall

    li $v0, 1 # syscall code for printing an integer
    move $a0, $v1 # the value to print
    syscall

    # Print a newline
    li $v0, 4 # syscall code for printing a string
    la $a0, newline # the string to print
    syscall

    # Exit the program
    li $v0, 10 # syscall code for exiting
    syscall

extract_bit:
    # Save the return address on the stack
    addi $sp, $sp, -4
    sw $ra, 0($sp)

    # Load the inputs into registers
    move $t0, $a0 # $t0 will store the 32-bit word
    move $t1, $a1 # $t1 will store the bit position

    # Shift the 32-bit word to the right by the bit position
    srl $t0, $t0, $t1

    # Get the least significant bit (LSB) of the result
    andi $v1, $t0, 1

    # Restore the return address from the stack
    lw $ra, 0($sp)
    addi $sp, $sp, 4

    # Return to the calling function
    jr $ra
