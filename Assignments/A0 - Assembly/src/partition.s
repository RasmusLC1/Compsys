partition:
	slli a1, a1, 2 #shift it left twice to account for using words, so x4 a1
	slli a2, a2, 2 #shift it left twice to account for using words, so x4 a2
	add t1, a0, a1 #p = A[i]
	lw t1, 0(t1) #load the word on the given address
	addi a1, a1,-4 #i = p-1
decreasej:
	addi a2, a2, -4
	add t3, a0, a2 #array value
        lw t3, 0(t3)
        blt t1, t3, decreasej
increasei:
	addi a1, a1, 4
	add t2, a0, a1 #array value
        lw t2, 0(t2)
        blt t2, t1, increasei
ifstatement:
	blt a1, a2, store
	jal, s1, partitionfinish
store:
	add t4, zero, t2 #int tmp = array[i]; 
	add t2, zero, t3 #array[i] = array[j];
	add t3, zero, t4 #array[j] = tmp;
	add t5, a0, a1 #get the position of A[i] in array
	sw t2, 0(t5) #store the new value of A[i] 
	add t6, a0, a2 #get the position of A[j] in array
	sw t3, 0(t6) #store the new value of A[j] 
	jal s1, decreasej
partitionfinish:
	add s1, zero, a2 #store q value
	srli s1, s1, 2
	addi s1, s1, 1 #j+1
	sw s1, 8(sp)