#include "pipeline.h"

#define START_SIZE 20

int Reader(struct RiscVInstruction instruction[20]){
    FILE *fptr;
    fptr = fopen("instructions.txt", "r");
    char line[30];
    int i = 0;
    while (fgets(line, sizeof(line), fptr)){
        sscanf(line, "%s %s %s %s", &instruction[i].instruction[0],
        &instruction[i].instruction[1], &instruction[i].instruction[2],
        &instruction[i].instruction[3]);
        strcpy(instruction[i].fullInstruction, line);
        for (int j = strlen(line)-2; j <= START_SIZE; j++){
            instruction[i].fullInstruction[j] = ' ';
        }
        i++;
    }
    return i;
}

void Printer(struct RiscVInstruction instruction[20], int index){
    int idBool = 0, ifBool;
    //Setting up clock
    
    for (int i = 0; i <= START_SIZE-2; i++){
        putchar(' ');
    }

    for (int i = 0; i <= index*3; i++){
        printf("%6d", i+1);
    }
    putchar('\n');
    
    //forloop to run through all the instructions
    for (int i = 0; i < index; i++){
        printf("%s", instruction[i].fullInstruction);

            //indentation
            for (int n = 0; n < instruction[i].names[0].index-1; n++){
                printf("%6c", ' ');
            }
            if (instruction[i].instruction[0][0] == 'b'){
                    for (int j = i+1; j < index; j++){
                        for (int n = 0; n < 5; n++){
                            instruction[j].names[n].index++;
                        }
                    }
            }
            if (memcmp(instruction[i].instruction[0], "lw", 2) == 0){
                memcpy (instruction[i].names[2].name, "AG", 2);
                memcpy (instruction[i].names[4].name, instruction[i].names[3].name, 2);
                memcpy (instruction[i].names[3].name, "MM", 2);

            } else if (memcmp(instruction[i].instruction[0], "sw", 2) == 0){
                memcpy (instruction[i].names[2].name, "AG", 2);
                memcpy (instruction[i].names[3].name, "MM", 2);
            }
            for (int j = 0; j < 4; j++){
                printf("%6s", instruction[i].names[j].name);
            }
            if (memcmp(instruction[i].instruction[0], "lw", 2) == 0){
                printf("%6s", instruction[i].names[4].name);
            }
            putchar('\n');   
    }  
}

void PrinterStall(struct RiscVInstruction instruction[20], int index){
    int idBool = 0, ifBool;
    //Setting up clock
    
    for (int i = 0; i <= START_SIZE-2; i++){
        putchar(' ');
    }

    for (int i = 0; i <= index*3; i++){
        printf("%6d", i+1);
    }
    putchar('\n');
    
    //forloop to run through all the instructions
    for (int i = 0; i < index; i++){
        printf("%s", instruction[i].fullInstruction);

            //indentation
            for (int n = 0; n < instruction[i].names[0].index-1; n++){
                printf("%6c", ' ');
            }

            // //Checking for stalls
            for (int n = 1; n < 4; n++){
                if (memcmp(instruction[i].instruction[1],  instruction[i-1].instruction[n], 3) == 0
                    && instruction[i].instruction[1][0] == 'x'||
                    memcmp (instruction[i].instruction[2], instruction[i-1].instruction[n], 3) == 0
                    && instruction[i].instruction[2][0] == 'x'||
                    memcmp (instruction[i].instruction[3], instruction[i-1].instruction[n], 3) == 0
                    && instruction[i].instruction[3][0] == 'x'){
                    idBool = 1;    
                }
            }
            if (instruction[i].instruction[0][0] == 'b' && ifBool == 0){
                for (int j = i+1; j < index; j++){
                    for (int n = 0; n < 5; n++){
                        instruction[j].names[n].index++;
                    }
                }
            }
            printf("%6s", instruction[i].names[0].name);
            printf("%6s", instruction[i].names[1].name);
            if (ifBool == 1 ){
                for (int n = 1; n < 5; n++){
                    instruction[i].names[n].index += 1;
                }
                if (i % 2 != 0){
                    for (int j = i+1; j < index; j++){
                        for (int n = 0; n < 5; n++){
                            instruction[j].names[n].index += 1;
                        }
                    }    
                } else{
                    for (int j = i+1; j < index; j++){
                        for (int n = 0; n < 5; n++){
                            instruction[j].names[n].index += 1;
                        }
                    }
                }
                printf("%6s", ">>");
                ifBool = 0;
            }
            
            if (idBool == 1){
                for (int n = 2; n < 5; n++){
                    instruction[i].names[n].index += 1;
                    
                }
                printf("%6s", ">>");
                idBool = 0;
                ifBool = 1;
            }
            if (memcmp(instruction[i].instruction[0], "lw", 2) == 0){
                memcpy (instruction[i].names[2].name, "AG", 2);
                memcpy (instruction[i].names[4].name, instruction[i].names[3].name, 2);
                memcpy (instruction[i].names[3].name, "MM", 2);

            } else if (memcmp(instruction[i].instruction[0], "sw", 2) == 0){
                memcpy (instruction[i].names[2].name, "AG", 2);
                memcpy (instruction[i].names[3].name, "MM", 2);
            }
            for (int j = 2; j < 4; j++){
                printf("%6s", instruction[i].names[j].name);
            }
            if (memcmp(instruction[i].instruction[0], "lw", 2) == 0){
                printf("%6s", instruction[i].names[4].name);
            }
            putchar('\n');   
    }  
}

void IPC_Calculator (struct RiscVInstruction instruction[20], struct InstructionNames name, int index){
    float startIndex = 0, endIndex = 0, time = 0;
    float IPC = 0;
    for (int i = 0; i < index; i++){
        if (memcmp(instruction[i].names[2].name, name.name, 3) == 0){
            startIndex = instruction[i].names[2].index;
            break;
        } 
    }
    for (int i = index; i > 0; i--){
        if (memcmp(instruction[i].names[2].name, name.name, 3) == 0){
            endIndex = instruction[i].names[2].index;
            break;
        } 
    }

    time = endIndex - startIndex + 1;
    IPC =  index / time+1;
    printf("IPC calculated from EX is %d/%.1f = %.2f\n", index, time+1, IPC);
}


void Stage_Checker(struct RiscVInstruction instruction[20], int index){
    int FE, DE, EX, WB, AG, MM;
    for (int i = 0; i < index;){
        FE = 0, DE = 0, EX = 0, WB = 0, AG = 0, MM = 0;
        for (int n = 0; n < 3; n++){
            for (int j = 0; j < 5; j++){
                if (memcmp(instruction[i].instruction[j], "FE", 2) == 0){
                    FE++;
                } else if (memcmp(instruction[i].instruction[j], "DE", 2) == 0){
                    DE++;
                } else if (memcmp(instruction[i].instruction[j], "EX", 2) == 0){
                    EX++;
                } else if (memcmp(instruction[i].instruction[j], "WB", 2) == 0){
                    WB++;
                } else if (memcmp(instruction[i].instruction[j], "AG", 2) == 0){
                    AG++;
                } else if (memcmp(instruction[i].instruction[j], "MM", 2) == 0){
                    MM++;
            }
            i++;
            if (FE > 2){
                printf("More than two %s %s\n", instruction[i].names[0].name, instruction[i].fullInstruction);
                return;
            } else if (DE > 2){
                printf("More than two %s\n", instruction[i].names[1].name);
                return;
            } else if (EX > 2){
                printf("More than two %s\n", instruction[i].names[2].name);
                return;
            } else if (WB > 1){
                printf("More than two WB\n");
                return;
            } else if (AG > 1){
                printf("More than two AG\n");
                return;
            } else if (MM > 1){
                printf("More than two MM\n");
                return;
            }
         
            }  
        }
    }
    printf("All are according to restrictions\n");
}