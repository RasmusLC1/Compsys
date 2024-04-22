#ifndef __SIMULATE_H__
#define __SIMULATE_H__


#include "memory.h"
#include "assembly.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <time.h>
#include "decoder.h"

// Simuler RISC-V program i givet lager og fra given start adresse
long int simulate(struct memory *mem, struct assembly *as, int start_addr, FILE *log_file);

void instruction_decoder(long instruction, int *x_registers, struct memory *mem, int *commands);

//FieldsMask
#define OP_MASK                 0x7F //1111111
#define FUNCT3_MASK             0x7 //111
#define FUNCT7_MASK             0x7F //1111111
#define RD_MASK                 0x1F //11111
#define RS1_MASK                0x1F //11111
#define RS2_MASK                0x1F //11111
#define SIGNEDBIN             0xFFFFFFFF //11111111111111111111111111111111
                                           // extra bits needed to account for
                                           // signed binary
#define UNSIGNEDBIN_12               0xFFF//111111111111
#define UNSIGNEDBIN_5                0x1F //11111
#define UNSIGNEDBIN_6                0x3F //111111
#define LUI_OFFSET              0xfffff000 //11111111111111111111000000000000
//Jal definitions
#define JAL1912                0x7FE00000 //01111111111000000000000000000000 
#define JAL11                 0x100000 // 00000000000100000000000000000000
#define JAL101                 0xFF000  //00000000000011111111000000000000
#define JAL20                  0x1000 //00000000000000000001000000000000
#define JAL_COMPLEMENT         0xFFE00000 //11111111111100000000000000000000
#define JAL_PC                 0xFFFFF //11111111111111111111

//SB definitions
#define SB_BIT31           0x80000000 // 10000000000000000000000000000000
#define SB_BIT30_25        0x7E000000 // 01111110000000000000000000000000
#define SB_BIT11_8         0x1E00     // 00000000000000000000111100000000
#define SB_BIT7            0x100      // 00000000000000000000000010000000


// Formats
#define I_TYPE                 3
#define IMMEDIATES             19
#define S_TYPE                 35
#define R_TYPE                 51
#define M_TYPE                 51
#define SB_TYPE                99
#define U_TYPE                 55
#define UJ_TYPE                111
#define JALR                   103
#define ECALL                  115

#endif
