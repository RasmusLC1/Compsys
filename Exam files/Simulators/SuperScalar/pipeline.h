#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <math.h>

struct InstructionNames{
    char name[5];
    int index;
};

struct RiscVInstruction{
    struct InstructionNames names[5];
    char instruction[4][6];
    char fullInstruction[20];
    int stallID;
    int stallIF;
};



void Printer(struct RiscVInstruction instruction[20], int index);
void PrinterStall(struct RiscVInstruction instruction[20], int index);
int Reader(struct RiscVInstruction instruction[20]);