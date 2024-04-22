To run copy the instructions into instructions.txt and sanitize them, remove commas and parantheses and add space between each.

addi x4 x4 1
slli x11 x4 5
add  x11 x16 x11
lw	 x11 8 x11
slli x12 x4 2
add	 x12 x17 x12
sw   x11 0 x12
bge  x9 x4 Loop

Write make and specifiy the instruction names such as FE DE EX MM WB and press enter.

The output can be found in output.txt

NB if you want stalls included, then change printer on line 26 in main to PrinterStall(instruction, index);