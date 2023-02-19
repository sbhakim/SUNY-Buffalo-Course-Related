      .data   0x10000000
num1: .word 9
num2: .word 5 

      .text
      .globl main 

main:
    la $t0, num1 
    lw $t1, 0($t0)
    lw $t2, 4($t0)


    slt $t3, $t2, $t1 

    beqz $t3, skip 

    #swap the two numbers 
    move $a0, $t1 
    move $t1, $t2
    move $t2, $a0


skip: 
    li $v0, 1 
    move $a0, $t1
    syscall 

    li $a0, 32 
    li $v0, 11 
    syscall
	

    li $v0, 1 
    move $a0, $t2 
    syscall 
   

    li $v0, 10 
    syscall 


