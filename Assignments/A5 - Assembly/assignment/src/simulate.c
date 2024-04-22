#include "simulate.h"




// Simuler RISC-V program i givet lager og fra given start adresse
long int simulate(struct memory *mem, struct assembly
*as, int start_addr, FILE *log_file) {
    int x_registers[33] = {0};
    int commands[10] = {0}; //0 = PC, 1 = END, 2 = counter 3=return for SB 
    commands[0] = start_addr;

    while (1){
        long instruction = memory_rd_w(mem, commands[0]);
        instruction_decoder(instruction, x_registers, mem, commands);
        commands[2]++;
        if (commands[1] == 1 ){
            break;
        }
        commands[0] += 4;
    }
    return commands[2];
}

void instruction_decoder(long instruction, int *x_registers,
struct memory *mem, int *commands) {
    uint32_t OPCode = instruction & OP_MASK;
    uint32_t funct7 = (instruction >> 25) & FUNCT7_MASK;

    int command;
    switch (OPCode){
        case I_TYPE:
            i_instruction(instruction, x_registers, mem);
            return;
        case IMMEDIATES:
            immediate_instruction(instruction, x_registers);
            return;
        case S_TYPE:
            store_instruction(instruction, x_registers, mem);
            return;
        case R_TYPE:
            if (funct7 == 1){
                m_instruction(instruction, x_registers);
            } else{
                register_instruction(instruction, x_registers);
            }
            return;
        case SB_TYPE:
            SB_instruction(instruction, x_registers, commands);
            return;
    }

    //Transition to if statement to instantiate variables
    if (OPCode == U_TYPE){
        uint32_t reg_dest =  (instruction >> 7) & RD_MASK;
        uint32_t imm = instruction >> 12;
        x_registers[reg_dest] = (imm << 12) & LUI_OFFSET;
    } else if (OPCode == UJ_TYPE){  
        uint32_t reg_dest = (instruction >> 7) & RD_MASK;
        uint32_t imm2 = (instruction >> 20) & SIGNEDBIN;
        uint32_t funct7 = (instruction >> 25) & FUNCT7_MASK;

        uint32_t offset = (((instruction & JAL1912) >> 20) |
                            ((instruction & JAL11) >> 9) |
                            (instruction & JAL101) |
                            ((instruction & JAL20) >> 13));

        int imm = JAL_COMPLEMENT | offset;
        int addr = commands[0] + imm - 4;


        if (reg_dest == 0){ //When jumping after SB instructions we do not link
            x_registers[reg_dest] = commands[3]; //as there is no return value
            commands[0] = (addr & JAL_PC);
            return;
        }
        x_registers[reg_dest] = commands[0]; //as there is no return value
        commands[0] = (addr & JAL_PC);
        return;


    } else if (OPCode == JALR){
        uint32_t rs1 = (instruction >> 15) & RS1_MASK;
        uint32_t imm = (instruction >> 20) & SIGNEDBIN;
        uint32_t addr = commands[0] + imm;
        commands[0] = x_registers[rs1];
        x_registers[rs1] = addr;
        return;
    } else if (OPCode == ECALL){
        ecall_instruction(x_registers, commands);
    } else{
        printf("\n\nINVALID INSTRUCTION %d\n", OPCode);
        exit(EXIT_FAILURE);
    }
}