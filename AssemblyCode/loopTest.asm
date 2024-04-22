addi x1,x1,10
Loop:
beq x1,zero,End
addi x1,x1,-1
jal zero, Loop
End: