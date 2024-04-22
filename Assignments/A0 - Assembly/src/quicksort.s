.data
array:
        .word 100
        .word 100
        .word 100000
        .word 255
        .word 0
        .word 123
        .word 4
        .word 50
.text
init:
	la a0, array # a0 stores array
	li a1, 0 # a1 stores start
	li a2, 8 # a2 stores end
	li a4, 2
	addi sp, sp, -12
	sw ra, 0(sp)
	sw a1, 4(sp)
        sw a2, 8(sp)
QuickSort:
        sub a3, a2, a1
        blt a3, a4, end
        jal ra, partition
        
        
        jal ra, QuickSort
        addi s3, s3, -1
        lw, a1, 4(sp)
        
        jal ra, QuickSort
        lw t0, 12(sp)
        add a0, t0, a0
        jal zero, return
        .include "partition.s"
return:
	lw ra, 0(sp)
	lw a2, 8(sp)
        lw a1, 4(sp)
        addi sp, sp, 16
        jalr zero, ra, 0
end:
	jalr zero, ra, 0
