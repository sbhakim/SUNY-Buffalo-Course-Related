        .data 0x10000000
input:  .asciiz "\nPlease Enter the number whose factorial is to be calculated: "
output: .asciiz "\nThe Factorial of the Number is: "


        .text
        .globl main

main: 
        # Reading the first integer 
        la $a0, input 
        li $v0, 4 
        syscall 

        li $v0, 5 
        syscall 
        add $a0, $v0, $zero   # moving the input value to $a0


        # Move factorial result into temp $t0 
        
        jal fact              # jal - jump and link (unconditional jump) 
        add $t0, $v0, $zero 


        # Priting out the result 

        la $a0, output 
        li $v0, 4
        syscall 

        add $a0, $t0, $zero 
        li $v0, 1 
        syscall 

end_prog: 
        li $v0, 10 
        syscall 

fact: 
        addi $sp, $sp, -4     # increment stack pointer, stack growing, stack TOP changed
        sw $ra, 0($sp)        # → value of $ra is stored in stack TOP, PUSH to stack
        addi $sp, $sp, -4     # increment stack pointer, stack growing, stack TOP changed
        sw $a0, 0($sp)        # → value of $a0 is stored in stack TOP, PUSH to stack

        slti $t0, $a0, 1      # $t0=1, if $a0 <= 1. most of the times $t0 = 0 
        beq $t0, $zero, L1    # This willl occur (n-1) times

        # after jumping (n-1) times to L1, only for once the following will be executed
        addi $v0, $zero, 1 

        lw $a0, 0($sp)        # ← POP the value of $a0 from the stack 
        addi $sp, $sp, 4      # decrement the stack pointer, stack shrink  
                              # after POP stack shrinks

        lw $ra, 0($sp)
        addi $sp, $sp, 4      # decrement the stack pointer, stack shrink  



        # if condition fullfils may not jump to L1 
        jr $ra 



L1: 
        addi $a0, $a0, -1    #  (n - 1) operation
        jal fact             # jal - jump and link (unconditional jump) 


        lw $a0, 0($sp)       # ← POP the value to $a0 from the stack  
        addi $sp, $sp, 4     # decrement the stack pointer, stack shrink  

        lw $ra, 0($sp)       # ← POP the value from the stack to $ra 
        addi $sp, $sp, 4     # decrement the stack pointer, stack shrink 

        mult $a0, $v0        # n*fact(n-1), $a0 and $v0 value unchanged, stored in HI, LO
        mflo $v0             # moves the lower 32-bit of the mult result to $v0 


        jr $ra 


        
