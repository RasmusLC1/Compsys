#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <math.h>

struct Table {
    int address;
    int originalValue;
    int step1;
    int step2;
};

struct Block{
    int footer;
    int header;
    int value;
    int allocated;
};

int main(){
    struct Table table[20];
    int index = Table_Creator(table);
    int addr,coalescing;
    printf("Is there immediate coalescing 1 for yes 0 for no\n");
    scanf("%d", &coalescing);
    char type[10];
    for (int i = 1; i < 3; i++){
        printf("Instruction %d, free or malloc?\n", i);
        scanf("%s", &type);
        
        if (memcmp(&type, "free", 4) == 0){
            printf("What is the address for the footer\n");
            scanf("%x", &addr);
            Free_Calculator(table, index, addr, coalescing);
        } else if (memcmp(type, "malloc", 4) == 0 || memcmp(type, "realloc", 4) == 0){
            printf("What is the address for the footer\n");
            scanf("%x", &addr);
            Malloc_Calculator(table, index, addr, coalescing);
        } else{
            i--;
        }
        printf("Addr\t\tOriginalVal  \tStep1\t\t   Step2\n");
        for (int j = 0; j < index; j++){
            printf("%8x\t%8x\t%8x\n", table[j].address, table[j].originalValue, 
            table[j].step1, table[j].step2);
            table[j].originalValue = table[j].step1;
            table[j].step1 = table[j].step2;
        }
        putchar('\n');
        
    }
    
    return 0;
}


//Setting up Page table
int Table_Creator(struct Table table[20]){
    unsigned int index;
    int i = 0;

    FILE *fptr;
    fptr = fopen("input.txt", "r");
    char line[50];

    while (fgets(line, sizeof(line), fptr)){
        sscanf(line, "%X %X %X %X\n", &table[i].address, &table[i].originalValue, 
        &table[i].step1, &table[i].step2);
        i++;
    }
    printf("Original\tAddress\t   \tStep1\t\t   Step2\n");
    for (int j = 0; j < i; j++){
        printf("%8x\t%8x\t%8x\n", table[j].address, table[j].originalValue, 
        table[j].step1, table[j].step2);
    }
    putchar('\n');
    return i;
}

void Malloc_Calculator(struct Table table[20], int index, int addr, int coalescing){
    
    struct Block block[10];
    int blockIndex = 0;

    //Finding footer
    int footerIndex = 99, headerIndex, footerBinSize, footerBin, headerBin,
        headerBinSize, decSize, blockSize, previousBin, checkFree;
    for (int i = 0; i < index; i++){
        if (addr == table[i].address){
            footerIndex = i+1;
        }
    }
    if (footerIndex == 99){
        printf("Didn't find footer %x\n", addr);
        exit(1);
    }
    int payloadSize;
    printf("Size of malloc:\n");
    scanf("%d", &payloadSize);
    payloadSize = payloadSize+8;
    if (payloadSize % 8 != 0){
        for (int i = 0; i < 8; i++){
            payloadSize++;
            printf("table[footerIndex-payloadSize/4].step1 %d\n", table[footerIndex-payloadSize/4].step1);
            if (payloadSize % 8 == 0){
                for (int j = 0; j < 10; j++){
                    if (table[footerIndex-payloadSize/4].step1 == 0){
                        printf("PAYLOADSIZE %d %x\n", payloadSize, table[footerIndex-payloadSize/4].originalValue);
                        headerIndex = footerIndex-payloadSize/4;
                        payloadSize += 4;
                        break;
                    }
                    payloadSize++;
                }
                
                
                
                break;
            }
        }
        
    } else{
        headerIndex = footerIndex+1 - payloadSize/4;
    }


    //Getting rows getting binary footerIndex and setting the last 3 digits to 0
    footerBin = Dec2Bin(payloadSize);

    //setting last 3 digits to 0
    footerBinSize = footerBin-(footerBin % 1000);

    //Back to dec
    decSize = Bin2Dec(footerBinSize);

    //Calculate amount of rows
    int standardrows = decSize/4;

    //Finding Header
    
    headerBin = Dec2Bin(headerIndex,table[headerIndex].originalValue);
    headerBinSize = payloadSize/4-(payloadSize/4 % 1000);

    blockSize = Bin2Dec(headerBinSize);
    int freerows = blockSize/4;
    int loopIndex = index;
    int alreadyChecked[20] = {0};    
    int headerPrevIndex = table[index-1].originalValue;

    //Checking if there is anything at bottom of heap
    for (unsigned j = index ; j-- >  footerIndex + 1;){
        if (table[j].step1 == 0 && alreadyChecked[j] == 0){
            table[j].step1 = table[j].originalValue;
            int step1Bin = Dec2Bin(table[j].step1);

            step1Bin -= (step1Bin % 1000);
            if (j == index-1){
                previousBin = Dec2Bin(table[0].originalValue);
                if (previousBin % 10 == 1){
                    step1Bin += 10;
                }
            } else{
                previousBin = Dec2Bin(table[j+1].step1);
                if (previousBin % 10 == 1 && j != index-1){
                step1Bin += 10;
                }
            }
            block[blockIndex].allocated = 0;
            checkFree = Dec2Bin(table[j].originalValue);
            if (checkFree % 10 == 1){
                step1Bin += 1;
                block[blockIndex].allocated = 1;
            }
            table[j].step1 = Bin2Dec(step1Bin);
            headerPrevIndex = table[j].step1;
            for (int i = footerIndex+1; i < j; i++){
                if (table[i].step1 == 0 && alreadyChecked[i] == 0){
                    table[i].step1 = table[j].step1;
                    block[blockIndex].footer = j;
                    block[blockIndex].header = i;
                    block[blockIndex].value = table[i].step1;
                    blockIndex++;
                    alreadyChecked[i] = 1;
                    for (int n = i; n < j; n++){
                        if (table[n].step1 == 0 && alreadyChecked[n] == 0){
                            table[n].step1 = table[n].originalValue;
                            alreadyChecked[n] = 1;

                        }
                    }
                    break;
                }
            }
        }
    }

    //setting header and footer
    int binSize = Dec2Bin(payloadSize);
    binSize -= (binSize % 1000);
    int headerPrevIndexBin =Dec2Bin(headerPrevIndex);
    if (headerPrevIndexBin % 10 == 1){
        binSize += 10;
    }
    binSize++;
    decSize = Bin2Dec(binSize);
    printf("%x\n", decSize);
    // exit(0);
    table[footerIndex+1].step1 = decSize;
    table[headerIndex].step1 = decSize;
    alreadyChecked[footerIndex] = 1;
    alreadyChecked[headerIndex] = 1;

    block[blockIndex].allocated = 0;
    block[blockIndex].footer = footerIndex;
    block[blockIndex].header = headerIndex;
    block[blockIndex].value = table[headerIndex].step1;
    blockIndex++;

    for (unsigned j = footerIndex ; j-- >  footerIndex - payloadSize/4+1;){
            table[j].step1 = table[j].originalValue;
        
    }
    table[footerIndex].step1 = decSize;
    table[headerIndex].step1 = decSize;
    

    //Handle above the designated header and footer
    for (unsigned j = headerIndex+1 ; j-- >  0;){
         if (table[j].step1 == 0 && alreadyChecked[j] == 0){
            table[j].step1 = table[j].originalValue;
            int step1Bin = Dec2Bin(table[j].step1);

            step1Bin -= (step1Bin % 1000);
            
            previousBin = Dec2Bin(table[j+1].step1);


            if (previousBin % 10 == 1 && j != index-1){
                step1Bin += 10;
            }
            block[blockIndex].allocated = 0;
            checkFree = Dec2Bin(table[j].originalValue);
            if (checkFree % 10 == 1){
                step1Bin += 1;
                block[blockIndex].allocated = 1;
            }
            table[j].step1 = Bin2Dec(step1Bin);
            headerPrevIndex = table[j].step1;
            for (int i = j; i-- >  0;){
                if (table[i].step1 == 0 && alreadyChecked[i] == 0){
                    table[i].step1 = table[j].step1;
                    alreadyChecked[i] = 1;

                    
                    block[blockIndex].footer = j;
                    block[blockIndex].header = i;
                    block[blockIndex].value = table[i].step1;
                    blockIndex++;

                    for (int n = i; n < j; n++){
                        if (table[n].step1 == 0 && alreadyChecked[n] == 0){
                            table[n].step1 = table[n].originalValue;
                            alreadyChecked[n] = 1;

                        }
                    }
                    break;
                }
            }
        }
    }

    //Coalescing
    int newSize = 0, newRows, prevBin;
    if (coalescing == 1){        
        for (int i = 0; i < blockIndex-1; i++){
            int prevBinFirst = prevBin =Dec2Bin(table[block[i].header].step1);
            int prevBinSecond = prevBin =Dec2Bin(table[block[i+1].footer].step1);  
            if (prevBinFirst % 10 == 0 && prevBinSecond % 10 == 0){
                table[block[i].footer].step1 = table[block[i].header].step1;
                int newLength = block[i].footer-block[i+1].header+1;
                table[block[i].footer].step1 = newLength*4;
                table[block[i+1].header].step1 = newLength*4;
                int prevBin = Dec2Bin(table[block[i].footer+1].step1);

                //Check if previous is free
                if (prevBin % 10 == 1){
                    table[block[i].footer].step1 += 2;
                    table[block[i+1].header].step1 +=2;
                }
                prevBin = Dec2Bin(table[block[i+1].header].originalValue);
                if (prevBin % 10 == 1){
                    table[block[i].footer].step1 += 1;
                    table[block[i+1].header].step1 += 1;
                }
                for (int k = block[i+1].header+1; k < block[i].footer; k++){
                    table[k].step1 = table[k].originalValue;
                }
                break;
            }

        }    
    }
}

void Free_Calculator(struct Table table[20], int index, int addr, int coalescing){
    
    struct Block block[10];
    int blockIndex = 0;

    //Finding footer
    int footerIndex = 99, headerIndex, footerBinSize, footerBin, headerBin,
        headerBinSize, decSize, blockSize, previousBin;
    for (int i = 0; i < index; i++){
        if (addr == table[i].address){
            footerIndex = i+1;
        }
    }
    if (footerIndex == 99){
        printf("Didn't find footer %x\n", addr);
        exit(1);
    }

    //Getting rows getting binary footerIndex and setting the last 3 digits to 0
    footerBin = Dec2Bin(table[footerIndex].originalValue);

    //setting last 3 digits to 0
    footerBinSize = footerBin-(footerBin % 1000);

    //Back to dec
    decSize = Bin2Dec(footerBinSize);

    //Calculate amount of rows
    int standardrows = decSize/4;

    //Finding Header
    headerIndex = footerIndex-standardrows+1;
    
    headerBin = Dec2Bin(table[headerIndex].originalValue);
    headerBinSize = footerBin-(footerBin % 1000);

    blockSize = Bin2Dec(headerBinSize);
    int freerows = blockSize/4;
    int loopIndex = index;
    int alreadyChecked[20] = {0};    
    int headerPrevIndex = table[index-1].originalValue;


    //Checking if there is anything at bottom of heap
    for (unsigned j = index ; j-- >  footerIndex + 1;){
        if (table[j].step1 == 0 && alreadyChecked[j] == 0){
            table[j].step1 = table[j].originalValue;
            int step1Bin = Dec2Bin(table[j].step1);

            step1Bin -= (step1Bin % 1000);
            if (j == index-1){
                previousBin = Dec2Bin(table[0].originalValue);
                if (previousBin % 10 == 1){
                    step1Bin += 10;
                }
            } else{
                previousBin = Dec2Bin(table[j+1].step1);
                if (previousBin % 10 == 1 && j != index-1){
                step1Bin += 10;
                }
            }
            block[blockIndex].allocated = 0;
            if (j != headerIndex || j != footerIndex){
                step1Bin += 1;
                block[blockIndex].allocated = 1;
            }
            table[j].step1 = Bin2Dec(step1Bin);
            headerPrevIndex = table[j].step1;
            for (int i = footerIndex+1; i < j; i++){
                if (table[i].step1 == 0 && alreadyChecked[i] == 0){
                    table[i].step1 = table[j].step1;
                    block[blockIndex].footer = j;
                    block[blockIndex].header = i;
                    block[blockIndex].value = table[i].step1;
                    blockIndex++;
                    alreadyChecked[i] = 1;
                    for (int n = i; n < j; n++){
                        if (table[n].step1 == 0 && alreadyChecked[n] == 0){
                            table[n].step1 = table[n].originalValue;
                            alreadyChecked[n] = 1;

                        }
                    }
                    break;
                }
            }
        }
    }

    //setting header and footer
    int binSize = Dec2Bin(decSize);
    binSize -= (binSize % 1000);
    int headerPrevIndexBin =Dec2Bin(headerPrevIndex);
    if (headerPrevIndexBin % 10 == 1){
        binSize += 10;
    }
    decSize = Bin2Dec(binSize);
    table[footerIndex].step1 = decSize;
    table[headerIndex].step1 = decSize;
    alreadyChecked[footerIndex] = 1;
    alreadyChecked[headerIndex] = 1;

    block[blockIndex].allocated = 0;
    block[blockIndex].footer = footerIndex;
    block[blockIndex].header = headerIndex;
    block[blockIndex].value = table[headerIndex].step1;
    blockIndex++;

    for (unsigned j = footerIndex ; j-- >  footerIndex - freerows+2;){
            table[j].step1 = table[j].originalValue;
    }
    

    //Handle above the designated header and footer
    for (unsigned j = headerIndex+1 ; j-- >  0;){
         if (table[j].step1 == 0 && alreadyChecked[j] == 0){
            table[j].step1 = table[j].originalValue;
            int step1Bin = Dec2Bin(table[j].step1);

            step1Bin -= (step1Bin % 1000);
            
            previousBin = Dec2Bin(table[j+1].step1);


            if (previousBin % 10 == 1 && j != index-1){
                step1Bin += 10;
            }
            block[blockIndex].allocated = 0;
            int prevBlockBin = Dec2Bin(table[j].originalValue);
            if (prevBlockBin % 10 == 1){
                step1Bin += 1;
                block[blockIndex].allocated = 1;
            }
            table[j].step1 = Bin2Dec(step1Bin);
            headerPrevIndex = table[j].step1;
            for (int i = 0; i < j; i++){
                if (table[i].step1 == 0 && alreadyChecked[i] == 0){
                    table[i].step1 = table[j].step1;
                    alreadyChecked[i] = 1;

                    
                    block[blockIndex].footer = j;
                    block[blockIndex].header = i;
                    block[blockIndex].value = table[i].step1;
                    blockIndex++;

                    for (int n = i; n < j; n++){
                        if (table[n].step1 == 0 && alreadyChecked[n] == 0){
                            table[n].step1 = table[n].originalValue;
                            alreadyChecked[n] = 1;

                        }
                    }
                    break;
                }
            }
        }
    }

    //Coalescing
    int newSize = 0, newRows, prevBin;
    if (coalescing == 1){        
        for (int i = 0; i < blockIndex-1; i++){
            int prevBinFirst = prevBin =Dec2Bin(table[block[i].header].step1);
            int prevBinSecond = prevBin =Dec2Bin(table[block[i+1].footer].step1);  
            if (prevBinFirst % 10 == 0 && prevBinSecond % 10 == 0){
                table[block[i].footer].step1 = table[block[i].header].step1;
                int newLength = block[i].footer-block[i+1].header+1;
                table[block[i].footer].step1 = newLength*4;
                table[block[i+1].header].step1 = newLength*4;
                int prevBin = Dec2Bin(table[block[i].footer+1].step1);
                if (prevBin % 10 == 1){
                    table[block[i].footer].step1 += 2;
                    table[block[i+1].header].step1 +=2;
                }
                prevBin = Dec2Bin(table[block[i+1].header].originalValue);
                if (prevBin % 10 == 1){
                    table[block[i].footer].step1 += 1;
                    table[block[i+1].header].step1 += 1;
                }
                for (int k = block[i+1].header+1; k < block[i].footer; k++){
                    table[k].step1 = table[k].originalValue;
                }
                break;
            }

        }    
    }
}



int Bin2Dec(int n){
    long long dec = 0, i = 0, rem;
    while (n!=0) {
        rem = n % 10;
        n /= 10;
        dec += rem * pow(2, i);
        ++i;
    }

    return dec;
}

int Dec2Bin(long long n){
  int bin = 0;
  int rem, i = 1;

  while (n!=0) {
    rem = n % 2;
    n /= 2;
    bin += rem * i;
    i *= 10;
  }

  return bin;
}
