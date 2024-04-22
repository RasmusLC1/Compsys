#include "memory.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>


struct cache_block{
    int tag;
    int data;
};

struct cache{
    uint32_t ways;
    uint32_t sets;
    uint32_t blockSize;
    struct cache_block cacheBlocks[1024][16]; //Define max size for the cache
};

struct input_data {
  int addr;
  int data;
};


struct cache Cache_Create(uint32_t ways, uint32_t sets, uint32_t blockSize);

void Cache_Write(struct cache *cache, struct input_data *inputData);