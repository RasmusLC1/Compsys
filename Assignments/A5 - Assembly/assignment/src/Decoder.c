#include "Decoder.h"



void i_instruction(long code, int* x_registers, struct memory *mem){
    uint32_t reg_dest = (code >> 7) & RD_MASK;
    uint32_t funct3 = (code >> 12) & FUNCT3_MASK;
    uint32_t rs1 = (code >> 15) & RS1_MASK;
    int imm = (code >> 20) & SIGNEDBIN;
    switch (funct3){
    case 0:   //LB
        x_registers[reg_dest] = memory_rd_b(mem, imm+x_registers[rs1]);
        return;
    case 1: //LH
        x_registers[reg_dest] = memory_rd_h(mem, imm+x_registers[rs1]);
        return;
    case 2: //LW
        x_registers[reg_dest] = memory_rd_w(mem, imm+x_registers[rs1]);
        return;
    case 4: //LBU
        imm = (code >> 20) & UNSIGNEDBIN_12;
        x_registers[reg_dest] = memory_rd_b(mem, imm+x_registers[rs1]);
        return;
    case 5: //LHU
        imm = (code >> 20) & UNSIGNEDBIN_12;
        x_registers[reg_dest] = memory_rd_h(mem, imm+x_registers[rs1]);
        return;
    default:
        return;
    }
}
void immediate_instruction(long code, int* x_registers){
    uint32_t reg_dest = (code >> 7) & RD_MASK;
    uint32_t funct3 = (code >> 12) & FUNCT3_MASK;
    uint32_t rs1 = (code >> 15) & RS1_MASK;
    uint32_t funct7 = (code >> 25) & FUNCT7_MASK;
    int imm = (code >> 20) & UNSIGNEDBIN_12;
    uint32_t bit31 = (code >> 31) & 1;

    if (bit31 == 1) {
        int offset = (code >> 19) & UNSIGNEDBIN_12;
        imm = offset - imm;
    }

    switch (funct3){
    case 0:
        if (rs1 == 0){ //li
            x_registers[reg_dest] = 0 + imm;
        } else{ //addi
            x_registers[reg_dest] = x_registers[rs1] + imm;
        }
        return;
    case 1: //SLLI
        x_registers[reg_dest] = x_registers[rs1] << imm;
        return;
    case 2: //SLTI
        if (x_registers[rs1] < imm){
            x_registers[reg_dest] = 1;
        } else{
            x_registers[reg_dest] = 0;
        }
        return;
    case 3: //SLTUI
        if (x_registers[rs1] < imm){
            x_registers[reg_dest] = 1;
        } else{
            x_registers[reg_dest] = 0;
        }
        return;
    case 4: //XORI
        x_registers[reg_dest] = x_registers[rs1] ^ imm;
        return;
    case 5:
        if (funct7 == 0){ //SRLI
            x_registers[reg_dest] = x_registers[rs1] >> imm;
            return;
        } else if (funct7 == 32){ //SRAI
            x_registers[reg_dest] = x_registers[rs1] >> imm;
            return;            
        } else{
            return;
        }
    case 6: //ORI
        x_registers[reg_dest] = x_registers[rs1] | imm;
        return;
    case 7: //ANDI
        x_registers[reg_dest] = x_registers[rs1] & imm;
        return;
    default:
        return;
    }
}

void store_instruction(long code, int* x_registers, struct memory *mem){
    uint32_t rs1 = (code >> 15) & RD_MASK;
    uint32_t funct3 = (code >> 12) & FUNCT3_MASK;
    uint32_t rs2 = (code >> 20) & RS2_MASK;
    uint32_t imm = (code >> 7) & UNSIGNEDBIN_6;
    
    switch (funct3){ //SB
        case 0:
            memory_wr_b(mem, imm+x_registers[rs1], x_registers[rs2]);
            return;
        case 1: //SH        //DOESN't WORK gets wrong IMM value
            memory_wr_h(mem, imm+x_registers[rs1], x_registers[rs2]);
            return;
        case 2: //SW
            memory_wr_w(mem, imm+x_registers[rs1], x_registers[rs2]);
            return;
        default:
            return;
    }
}

void register_instruction(long code, int* x_registers){
    uint32_t reg_dest = (code >> 7) & RD_MASK;
    uint32_t rs1 = (code >> 15) & RS1_MASK;
    uint32_t rs2 = (code >> 20) & RS2_MASK;
    uint32_t funct7 = (code >> 25) & FUNCT7_MASK;
    uint32_t funct3 = (code >> 12) & FUNCT3_MASK;

    if (funct7 == 0){
        switch (funct3){
            case 0: //ADD
                x_registers[reg_dest] = x_registers[rs1] + x_registers[rs2]; 
                return;
            case 1: //SLL
                x_registers[reg_dest] = x_registers[rs1] << x_registers[rs2]; 
                return;
            case 4: //XOR
                x_registers[reg_dest] = x_registers[rs1] ^ x_registers[rs2]; 
                return;
            case 5: //SRL
                x_registers[reg_dest] = x_registers[rs1] >> x_registers[rs2]; 
                return;
            case 6: //OR
                x_registers[reg_dest] = x_registers[rs1] | x_registers[rs2];
                return;
            case 7: //AND
                x_registers[reg_dest] = x_registers[rs1] & x_registers[rs2];
                return;
            default:
                return;
        }
    } else if(funct7 == 32){
        if (funct3 == 0){ //SUB
            x_registers[reg_dest] = x_registers[rs1] - x_registers[rs2];
            return;
        } else if (funct3 == 1){ //SRA
            x_registers[reg_dest] = x_registers[rs1] >> x_registers[rs2];
            return;
        }
    }
}

void SB_instruction(long code, int* x_registers, int* commands){
   // Defines last 20 bits of instruction code
    uint32_t bit31 = (code >> 31) & 1;
    uint32_t bit31offset;
    
    if (bit31 == 1) {
        bit31offset = 0xFFFFF000;
    } else {
        bit31offset = 0;
    }

    // Define type of branch condition, and what is to be compared
    uint32_t rs1 = (code >> 15) & RS1_MASK;
    uint32_t rs2 = (code >> 20) & RS2_MASK;
    uint32_t funct3 = (code >> 12) & FUNCT3_MASK;
    
    // Translates instruction to immediate
    int offset = (((code & SB_BIT31) >> 19) |
                 ((code & SB_BIT30_25) >> 20) |
                 ((code & SB_BIT11_8) >> 7) |
                 ((code & SB_BIT7) << 4)) | bit31offset;

    int immediate = 0xFE000F80 | offset;
    int address;
    if (bit31offset == 0) {
        address = commands[0] + offset;
    } else {
        address = commands[0] + immediate;
    }


    switch (funct3) {
        case 0: //BEQ
            if (x_registers[rs1] == x_registers[rs2]) {
                commands[3] = commands[0]; 
                commands[0] = address-4;
            }
            return;
        case 1: //BNE        
            if (x_registers[rs1] != x_registers[rs2]) {
                commands[3] = commands[0]; 
                commands[0] = address-4;
            }
            return;
        case 4: //BLT
            if (rs1 < rs2) {
                commands[3] = commands[0]; 
                commands[0] = address-4;
            }
            return;
        case 5: //BGE
            if (rs1 >= rs2) {
                commands[3] = commands[0]; 
                commands[0] = address-4;
            }
            return;
        case 6: //BLTU
            if (rs1 < rs2) {
                commands[3] = commands[0]; 
                commands[0] = address-4;
            }
            return;
        case 7: //BGEU
            if (rs1 >= rs2) {
                commands[3] = commands[0]; 
                commands[0] = address-4;
            }
            return;
        default:
            return;
        }
}

void m_instruction(long code, int* x_registers){
    uint32_t reg_dest = (code >> 7) & RD_MASK;
    uint32_t funct3 = (code >> 12) & FUNCT3_MASK;
    uint32_t rs1 = (code >> 15) & RS1_MASK;
    uint32_t rs2 = (code >> 20) & RS2_MASK;

    switch (funct3) {
        case 0: //MUL
            x_registers[reg_dest] = x_registers[rs1] * x_registers[rs2];
            return;
        case 1: //MULH
            x_registers[reg_dest] = x_registers[rs1] * x_registers[rs2];
            return;
        case 2: //MULHSU
            x_registers[reg_dest] = x_registers[rs1] * x_registers[rs2];
            return;
        case 3: //MULHU
            x_registers[reg_dest] = x_registers[rs1] * x_registers[rs2];
            return;
        case 4: //DIV
            x_registers[reg_dest] = x_registers[rs1] / x_registers[rs2];
            return;
        case 5: //DIVU
            x_registers[reg_dest] = x_registers[rs1] / x_registers[rs2];
            return;
        case 6: //REM
            x_registers[reg_dest] = x_registers[rs1] % x_registers[rs2]; 
            return;
        case 7: //REMU
            x_registers[reg_dest] = x_registers[rs1] % x_registers[rs2]; 
            return;
        default:
            return;
        }
}


void ecall_instruction(int* x_registers, int* commands){
    char str[20];
    int i = 0;
    int ch;
    switch (x_registers[17]) {
        case 1:
            while((ch = getchar()) != '\n' && ch != EOF ) {
                str[i++] = ch;
            }
            str[i] = '\0';
            x_registers[17] = *str; //Doesn't work, tried with
                                    // x_registers[17] = getchar() as well
            return;
        case 2:
            putchar(x_registers[16]);
            return;
        case 3:
            commands[1] = 1;
            return;
        case 93:
            commands[1] = 1;
            return;
        default:
            return;
    }
}

