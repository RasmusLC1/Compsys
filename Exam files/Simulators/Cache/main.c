#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <math.h>
#include "cache.h"
#include "memory.h"

int Bin2Dec(long n){
    long dec = 0, i = 0, rem;
    while (n!=0) {
        rem = n % 10;
        n /= 10;
        dec += rem * pow(2, i);
        ++i;
    }

    return dec;
}

long long  Dec2Bin(int n){
  long long  bin = 0;
  long long rem, i = 1, k = 0;
  while (n!=0) {
    rem = n % 2;
    n /= 2;
    bin += rem * i;
    i *= 10;
  }
  return bin;
}


int ptSize = 0;

int main(){
    int addr[30] = {0};
    int offsetprint = log2(32);
    int setPrint = 16 * 1024 / 32;
    setPrint = log2(setPrint);
    printf("offset %d %d\n", offsetprint, setPrint);
    int offset, set, ways, blockSize, blockNum, elements, index, tagOffset, tag, largestIndex = 0;
    elements = Reader(addr);
    
    //getting specifications
    printf("Amount of blocks:\n");
    scanf("%d", &blockNum);
    printf("Size of blocks:\n");
    scanf("%d", &blockSize);
    printf("Number of ways:\n");
    scanf("%d", &ways);

    //calculating the offset, set and tag
    set = blockSize * blockNum;
    printf("TotalSize of cache: %d\n", set);
    set = log2(set);
    offset = log2(blockSize);
    tagOffset = 16 - set - offset;
    set = 16 - tagOffset - offset;
    printf("%d %d %d \n", tagOffset, set, offset);
    long long addrBin;

    //Creating cache
    struct cache cache = Cache_Create(ways, blockNum, blockSize);
    struct input_data inputData;

    printf("%6s%12s%6s%6s%12s\n", "Status", "Addr", "Tag", "Index", "Cache");
    
    for (int i = 0; i < elements; i++){
        if (addr[i] == 0){
            printf("MISS %6c", ' ');
        } else{
            addrBin = Dec2Bin(addr[i]);
            index = Index_Finder(addrBin, offset, tagOffset);
            tag = Tag_Finder(addrBin, tagOffset, set);
            if (tag > largestIndex){
                largestIndex = tag;
            }
            if (addr[i] > 1000){
                printf("Address to big to handle automaticaly, please enter tag and index\n");
                scanf("%d %d", &tag, &index);
            }
            inputData.addr = index;
            inputData.data = tag;
            Cache_Read(&cache, &inputData);
        }

        printf("%6x %6x %6x", addr[i], tag, index);
        for (int k = 0; k <= largestIndex; k++){
            printf("%6d:{", cache.cacheBlocks[k][0].tag);
            for (int j = 0; j < ways/2+1; j++){
                printf("%d,", cache.cacheBlocks[k][j].data);
            }
            putchar('}');
        }
        putchar('\n');
    }
    
    
    return 0;
}

//setting up TBL
int Reader(int addr[]){
    int i = 0;
    FILE *fptr;
    fptr = fopen("input.txt", "r");
    char line[30];
    while (fgets(line, sizeof(line), fptr)){
        sscanf(line,"%x", &addr[i]);
        printf("%x\n", addr[i]);
        i++;
    }
    return i;
}

int Index_Finder(int addrBin, int offset, int tag){
    addrBin = addrBin / pow(10, offset);
    int newTag = pow(10, tag);
    addrBin = addrBin % newTag;
    int index = Bin2Dec(addrBin);
    return index;
}

int Tag_Finder(int addrBin, int tag, int set){
    int tagReturn;
    addrBin /= pow(10, set-1); 
    tagReturn = Bin2Dec(addrBin);
    return tagReturn;
}

