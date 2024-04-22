#include "pipeline.h"


int main(){
    printf("Setup:\nperfect Branch prediction predicted in DE and perfect cache hit\n");

    printf("load: Fe De Ex Mm Wb\nstore: Fe De Ex Mm\nandre: Fe De Ex Wb\nFe: 1, De: 1, Ex: 1, Mm: 1, Wb: 1\n\n");
    
    struct InstructionNames names[5]; 
    scanf("%s %s %s %s %s", &names[0].name, &names[1].name, &names[2].name, &names[3].name, &names[4].name);
    struct RiscVInstruction instruction[20];
    int index = Reader(instruction);

    int scalarIndex = 0;
    //setting up index;
    for (int i = 0; i < index; i++){
        instruction[i].stallID = 0;
        instruction[i].stallIF = 0;
        memcpy (instruction[i].names, names, sizeof(struct InstructionNames)*5);
        for (int j = 0; j < 5; j++){
            instruction[i].names[j].index = i+j+1;
            strcat(instruction[i].names[j].name, "");
        }
        
    }
    PrinterStall(instruction, index);
    IPC_Calculator(instruction, names[2], index);
    
    return 0;
}