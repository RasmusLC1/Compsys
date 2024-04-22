#include "cache.h"


//initialise empty cache
struct cache Cache_Create(uint32_t ways, uint32_t sets, uint32_t blockSize){
    struct cache cache;
    cache.ways = ways;
    cache.sets = sets;
    cache.blockSize = blockSize;
    return cache;
}

void Cache_Read(struct cache *cache, struct input_data *inputData){
    const int setIndex = inputData->addr;
    
    //We use one for loop as our leftmost value is our most recently used
    for (uint32_t i = 0; i < cache-> ways; i++){
        //Handle hit and increment lru
        if (cache->cacheBlocks[setIndex][i].tag == inputData->addr
            && cache->cacheBlocks[setIndex][i].data == inputData->data){
            printf("HIT %6c", ' ');
            for (int j = cache->ways; j > 0; j--){
                cache->cacheBlocks[setIndex][j].tag = cache->cacheBlocks[setIndex][j-1].tag;
                cache->cacheBlocks[setIndex][j].data = cache->cacheBlocks[setIndex][j-1].data;
            }
            cache->cacheBlocks[setIndex][0].tag = inputData->addr;
            cache->cacheBlocks[setIndex][0].data = inputData->data;
            return;
        } 
    }
    
    
    for (int j = cache->ways; j > 0; j--){
        cache->cacheBlocks[setIndex][j].tag = cache->cacheBlocks[setIndex][j-1].tag;
        cache->cacheBlocks[setIndex][j].data = cache->cacheBlocks[setIndex][j-1].data;
    }
    cache->cacheBlocks[setIndex][0].tag = inputData->addr;
    cache->cacheBlocks[setIndex][0].data = inputData->data;
    printf("MISS %6c", ' ');

    return;
}

