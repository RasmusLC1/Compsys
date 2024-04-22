#include "memory.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>


struct cache_block{
    int tag;
    int leastUsed;
    int isModified;
    int isValid;
    int data;
};

struct cache{
    uint32_t ways;
    uint32_t sets;
    uint32_t blockSize;
    struct cache_block cacheBlocks[1024][16]; //Define max size for the cache
    struct memory *mem;
};

struct input_data {
  char op;
  int addr;
  int data;
  int counter; 
};


struct cache Cache_Create(uint32_t ways, uint32_t sets, uint32_t blockSize,
  struct memory *mem);

void Cache_Write(struct cache *cache, struct input_data *inputData);

void Cache_Read(struct cache *cache, struct input_data *inputData);

int Compare(const void *a, const void *b);