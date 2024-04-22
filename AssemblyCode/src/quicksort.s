.text
init:
	# a0 stores array
        # a1 stores start
        # a2 stores end
        li s3, 2 # save the value 2 in s3
        addi sp, sp, -16 # allocate 4 words in the stack
        sw a1, 0(sp) # save start adress
        sw a2, 4(sp) # save end adress
        sw a0, 8(sp) # save array address
        jal ra, quicksort
        jal zero, end
quicksort:
        sub s4, a2, a1 # subtracts end-start and saves it in s4
	blt s4, s3, quicksort_return # checks if end-start < 2
	jal ra, partition # run partition
.include "partition.s"
        sw a0, 12(sp) # save q value from partition
        lw a0, 8(sp) # load array adress to a0
        lw a1, 0(sp) # reads start adress from the stack
        lw a2, 12(sp) # reads end adress from new q value
        jal ra, quicksort # first recursive call
	
        lw a1, 12(sp) # reads start adress from new q value
        lw a2, 4(sp) # reads end adress
        jal ra, quicksort # second recursive call
quicksort_return:
	addi sp, sp, 16 # set the stack back as it was
	#jalr zero, ra, 0 #return
	jal zero, end #return
end:
