init:
	li a0,0 #value that needs to be saved
	li a1,1 #fib val 1
	li a2,0 #fib val 2
	li a3,30 #n værdi
	addi sp, sp, -12 #free 12 bits 
	jal ra, fib
	jal zero, end
fib:
	beq a3, zero, fib_return #Checks if n value is 0
	addi a3, a3,-1 #Countdown n value
	sw a2, 4(sp) #store a2 in 4
	sw ra, 8(sp) #store ra in 8
	add a0, a1, a2 #adds the values to a0
	sw a0, 0(sp) #store a0 in 0
	lw a1, 4(sp) #load a1 from 4, a1 value
	lw a2, 0(sp) #load a2 from 0, a0 value
	jal zero, fib #return to fib
fib_return:
	lw ra, 8(sp) #return to original pointer address
	addi, sp, sp, 12 #Move the point back
	jalr zero, ra, 0 
end:
