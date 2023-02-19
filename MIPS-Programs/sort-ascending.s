# The program is verified using QtSpim 9.1.23

# Problem Description: Two values is initialized. The program will check which value is smaller.  
# Then prints out the numbers in ascending order. 
      
      
      .data   0x10000000
num1: .word 9
num2: .word 5 

      .text
      .globl main 

main:
    la $t0, num1 
    lw $t1, 0($t0)	
    lw $t2, 4($t0)


    slt $t3, $t2, $t1     # slt - set less than 

    beqz $t3, print 	   # branch if equal to 0
	
    #swap the two numbers 
    move $a0, $t1 
    move $t1, $t2
    move $t2, $a0


print: 
    # printout the first number
    li $v0, 1 		 
    move $a0, $t1
    syscall 
	
    # print out a space 
    li $a0, 32 
    li $v0, 11 
    syscall
	
    # printout the second number
    li $v0, 1 
    move $a0, $t2 
    syscall 
   
    # exit from the program
    li $v0, 10 
    syscall 


