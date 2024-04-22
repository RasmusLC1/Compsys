#include "pipeline.h"


int main(){
    printf("Setup:\nperfect Branch prediction predicted in DE, takes one clock cycle and perfect cache hit\n");
    printf("load: FE DE AG MG Wb\nstore: FE DE AG MM\nandre: FE DE EX WB\n");
    printf("Fe:2, De:2, Ex:2, Ag:1, Mm:1, Wb:2\n");
    //Setting up structs
    printf("Write names of instructions, for example IF ID EX MEM WB\n");
    struct InstructionNames names[5]; 
    scanf("%s %s %s %s", &names[0].name, &names[1].name, &names[2].name, &names[3].name);
    struct RiscVInstruction instruction[20];
    int index = Reader(instruction);

    int scalarIndex = 0;
    //setting up index;
    for (int i = 0; i < index; i++){
        instruction[i].stallID = 0;
        instruction[i].stallIF = 0;
        memcpy (instruction[i].names, names, sizeof(struct InstructionNames)*5);
        if (i % 2 == 0){
            scalarIndex++;
        }
        for (int j = 0; j < 5; j++){
            instruction[i].names[j].index = scalarIndex+j;
            strcat(instruction[i].names[j].name, "");
        }
        
    }
    Printer(instruction, index);
    Stage_Checker(instruction, index);
    IPC_Calculator(instruction, names[3], index);
    return 0;
}