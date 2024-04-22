#include "cache.h"


//initialise empty cache
struct cache Cache_Create(uint32_t ways, uint32_t sets, uint32_t blockSize,
struct memory *mem){
    struct cache cache;
    cache.ways = ways;
    cache.sets = sets;
    cache.blockSize = blockSize;
    cache.mem = mem;
    for (uint32_t i = 0; i < sets; i++){
        for (uint32_t j = 0; j < ways; j++){
            cache.cacheBlocks[i][j].isModified = 0;
            cache.cacheBlocks[i][j].isValid = 0;
            cache.cacheBlocks[i][j].leastUsed = 0;
        }
    }
    return cache;
}


void Output_Message(struct cache *cache, struct input_data *inputData,
    int setIndex, int index, char* message){
    printf("%c %d %d %s",
        inputData->op, inputData->addr, inputData->data, message);

    cache->cacheBlocks[setIndex][index].leastUsed = inputData->counter;
    cache->cacheBlocks[setIndex][index].tag = inputData->addr;
    cache->cacheBlocks[setIndex][index].isValid = 1;
    for (uint32_t j = 0; j < cache->ways; j++){
        printf(", %d", setIndex*cache->ways+j);
    }
    putchar('\n');
}

//compare function for cache block lru
int Compare(const void *a, const void *b) {
  struct cache_block structA = *(struct cache_block *)a;
  struct cache_block structB = *(struct cache_block *)b;
  if (structA.leastUsed > structB.leastUsed) return -1;
  if (structA.leastUsed < structB.leastUsed) return 1;
  return 0;
}
    


void Cache_Read(struct cache *cache, struct input_data *inputData){
    const int setIndex = inputData->addr / cache->ways;

    //Qsort the line to have the lru be the first element moving right
    qsort(cache->cacheBlocks[setIndex], 4, sizeof(struct cache_block), Compare);

    //We use one for loop as our leftmost value is our most recently used
    for (uint32_t i = 0; i < cache-> ways; i++){
        //Handle hit and increment lru
        if (cache->cacheBlocks[setIndex][i].isValid == 1 
            && cache->cacheBlocks[setIndex][i].tag == inputData->addr
            && cache->cacheBlocks[setIndex][i].data == inputData->data){
            Output_Message(cache, inputData, setIndex, i, "HIT");
            return;
        // handle fill
        } else if (cache->cacheBlocks[setIndex][i].isValid == 0){
            cache->cacheBlocks[setIndex][i].data
                = memory_rd_w(cache->mem, inputData->addr);
            Output_Message(cache, inputData, setIndex, i, "FILL");

            return; 
        }
    }

    Cache_Write(cache, inputData);
    return;
}


void Cache_Write(struct cache *cache, struct input_data *inputData){
    const int setIndex = inputData->addr / cache->ways;

    //Qsort the line to have the lru be the first element moving right
    qsort(cache->cacheBlocks[setIndex], 4, sizeof(struct cache_block), Compare);

    //Handle evict
    for (uint32_t i = 0; i < cache-> ways; i++){
        if (cache->cacheBlocks[setIndex][i].isModified == 1
            && cache->cacheBlocks[setIndex][i].isValid == 1){

            memory_wr_w(cache->mem, inputData->addr,
                cache->cacheBlocks[setIndex][i].data);

            cache->cacheBlocks[setIndex][i].data = inputData->data;
            Output_Message(cache, inputData, setIndex, i, "EVICT");
            cache->cacheBlocks[setIndex][i].isModified = 0;
            return;
        }
    }

    //Handle discard
    for (uint32_t i = 0; i < cache-> ways; i++){
        if (cache->cacheBlocks[setIndex][i].isModified == 0
            && cache->cacheBlocks[setIndex][i].isValid == 1){
                
                cache->cacheBlocks[setIndex][i].isModified = 1;
                cache->cacheBlocks[setIndex][i].data = inputData->data;
                Output_Message(cache, inputData, setIndex, i, "DISCARD");
                return;
        }
    }
    printf("No data available in %d, use init or read\n", inputData->addr);
    return;
}