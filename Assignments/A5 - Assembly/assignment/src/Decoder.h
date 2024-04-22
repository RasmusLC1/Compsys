#include "simulate.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

//Fidning which 

void i_instruction(long code, int* x_registers, struct memory *mem);

void immediate_instruction(long code, int* x_registers);

void store_instruction(long code, int* x_registers, struct memory *mem);

void register_instruction(long code, int* x_registers);

void SB_instruction(long code, int* x_registers, int* commands);

void m_instruction(long code, int* x_registers);

void ecall_instruction(int* x_registers, int* commands);


