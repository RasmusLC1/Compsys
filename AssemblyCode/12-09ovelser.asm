init:
	li a0,0 #value that needs to be saved
	li a1,1
	li a2,5 #n værdi
	jal ra, fib
	jal zero, end
fib:
	addi sp, sp, -8
	jal, zero, fib_loop
fib_loop:
	beq a2, zero, fib_return
	sw ra, 4(sp)
	sw a0, 0(sp)
	addi a3, a1, 0
	add a0,a0,a1
	addi a1, a0,0 
	addi a0, a3,0
	addi a2, a2, -1
	jal zero, fib
fib_return:
	lw ra, 4(sp)
	addi, sp, sp, 8
	jalr zero, ra, 0
end: