 .data

# Test data.  If you change the number of words, make sure to also
# change the argument passed in a2 to partition.

array:
        .word 100
        .word 100
        .word 100000
        .word 255
        .word 0
        .word 123
        .word 4
        .word 50
        .word 22
        .word 65
        .word 3
        .word 12
.text
test:
        la a0, array      # address of array
        addi a1, zero, 0  # start element
        addi a2, zero, 12  # number of elements
        #jal ra, partition # call partition
        jal ra, init # call partition
        jal zero, end     # jump to end
#.include "partition.s"
.include "quicksort.s"
#end:
.text

