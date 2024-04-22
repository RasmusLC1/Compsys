#include "memory.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "cache.h"



int main(int argc, char *argv[]){
    if (argc != 4) {
      printf("Wrong input\n");
      exit(1);
    }
    uint32_t ways = atoi(argv[1]);
    uint32_t sets = atoi(argv[2]);
    uint32_t blockSize = atoi(argv[3]);

    if (ways > 16 || sets % 2 != 0 || sets > 1024 ||
       blockSize % 2 != 0 || blockSize < 4){
          printf("Invalid values for cache\n");
          exit(1);
    }
    
    //Setting up memory and cache
    struct input_data inputData;
    inputData.counter = 0;
    struct memory *mem = memory_create();
    struct cache cache = Cache_Create(ways, sets, blockSize, mem);

    while(1){
      //getting user input
      printf("Write command:\n");
      scanf("%s %x %x", &inputData.op, &inputData.addr, &inputData.data);
      inputData.counter++;
      
      //exit condition
      if (inputData.op == 'e'){
            printf("Exiting program\n");
            break;

      //Check if input is valid
      } else if (inputData.addr % 4 != 0){
        printf("Invalid address %d\n", inputData.addr);
      }else if (sizeof(inputData.data)>blockSize){
        printf("Input: %d is too large\n", inputData.data);
      
      
      //Init
      } else if (inputData.op == 'i'){
      memory_wr_w(mem, inputData.addr, inputData.data);
      printf("completed the following command: %c %d %d INIT\n",
        inputData.op, inputData.addr, inputData.data);

      //Read
      } else if (inputData.op == 'r'){
        Cache_Read(&cache, &inputData);

      //Write
      } else if (inputData.op == 'w'){
        Cache_Write(&cache, &inputData);

      //Faulty input
      } else{
        printf("Invalid input: %c %d %d\n",
        inputData.op, inputData.addr, inputData.data);
      }
    }
    memory_delete(mem);
}