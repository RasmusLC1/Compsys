        .text

        .globl _start
_start:
        lui a0,0x11
        jal ra,1004
        ret
SB:
        beqz a1, 65772
        bne a1, a2, 65776
        bne a1, a1, 65780
        blt a1, a1, 65784
        bge a1, a1, 65788
        bltu a1, a1, 65792
        bgeu a1, a1, 65796

LoadStore:
        lb a0,8(a1)
        lh a0,12(a1)
        lw a0,8(a1)
        lbu a0,8(a1)
        sb a2,8(a1)
        sh a2,12(a1)
        sw a2,8(a1)

logic:
        xori ra, a1, 100
        andi ra, a1, 100
        xor a2, a1, a1
        or a2, a1, a1
        ori ra, a1, 100
        and a2, a1, a1


Shifting:
        sltiu ra, a1, 100
        slti ra, a1, 100
        slli ra, a1, 5
        srli ra, a1, 5
        srai ra, a1, 5
        sll a2, a1, a1
        slt a2, a1, a1
        sltu a2, a1, a1
        srl a2, a1, a1
        sra a2, a1, a1

Arithmetics:
        addi a1, a1, 10
        addi a1,a1,-12
        addi a2, a2, 10
        addi a1, a1, 4
        addi a1, a1, -10
        addi a1, a1, -5
        add a2, a0, a1
        sub a2, a0, a1

extension:
        mul a2, a1, a1
        mulh a2, a1, a1
        mulhsu a2, a1, a1
        mulhu a2, a1, a1
        div a2, a1, a1
        divu a2, a1, a1
        rem a2, a1, a1
        remu a2, a1, a1

