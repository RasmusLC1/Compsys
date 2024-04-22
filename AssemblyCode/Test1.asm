addi x5,x5,10
addi x6,x6,12
addi x28, x28, 19
addi x29, x29, 4
addi x10, x10, 8


#opg 2.1
addi x5, x5, -5
add x7,x6,x5


#opg 2.3
sub x5, x28, x29
slli x5, x5, 2 #Moves the digits 2 to the left
add x5, x10, x5 #adds values together
lb x5, 0(x5) #assign it to memory
sw x5, 32(x11) #Store it in memory

#B[8] = A[i?j];