.text
partition:
	# array in a0
        # p in a1
        # r in a2
        slli t0, a1, 2 	# p times 4 to correspond with a word
        add t0, a0, t0 	# save pivot index in t0
        lw t0, 0(t0) 	# load pivot value from t0 and overwrite to save in t0
        addi t1, a1, -1 # define i in t1 where i = p-1
        add t2, zero, a2 # define j in t2 where j = r 
j_dec:
	addi t2, t2, -1 # decrement j
	slli t3, t2, 2 	# multiply with 4 to get the word of j
	add t3, t3, a0  # save the address of index j from array
	lw t4, 0(t3) 	# save the array[j] of index j in t3 using load word
	blt t0, t4, j_dec # checks pivot < array[j]
i_inc:
	addi t1, t1, 1 #increment i
	slli t5, t1, 2 	# multiply with 4 to get the word of i
	add t5, t5, a0  # save the address of index i from array
	lw t6, 0(t5) 	# save the array[i] of index i in t4 using load word
	blt t6, t0, i_inc # checks array[i] < pivot
partition_check:
        blt t1, t2, partition_switch 	# checks i < j
	jal zero, partition_return 	# in order to end function go to return
partition_switch:
	sw t4, 0(t5) # array[i] = array[j]
	sw t6, 0(t3) # array[j] = tmp/array[i]
	jal zero, j_dec # loop back to partition
partition_return:
	addi a0, t2, 1 # save j+1 in a0