#include "memory.h"
#include "cache.h"
#include <stdio.h>
#include <stdlib.h>

//bool check of a power of 2
// bool IsPowerOfTwo(ulong x) {
//     return (x != 0) && ((x & (x - 1)) == 0);
// }

struct cache_block
{
  int valid; // Checks if the block is valid
  int tag; // The tag the block has
  int data[MAX_B]; // The data in the block
};

struct cache_set
{
  struct cache_block blocks[MAX_W]; // Array of cache blocks
};

struct cache
{
  int W; // Number of ways in the cache
  int S; // Number of sets
  int B; // Block size
  struct cache_set sets[MAX_S]; // Array of cache sets
  struct memory *mem; // Pointer to main memory
};

// Initialize data in memory
void init(struct memory *mem, int addr, int data, char op) {
    if (addr % 4 == 0) {
        memory_wr_w(mem, addr, data);
        printf("op: %c, addr: %d, data: %d, INIT\n", op, addr, data);
    } else {
        printf("ERROR: addr is not divisible by 4\n");
    }
}

// Creates a new cache and returns a pointer to it
struct cache *cache_create(int W, int S, long long B, struct memory *mem) {
    if (W > 17) {
    printf("ERROR: W must not be bigger than 16\n");
    return NULL;
    }

    if ((S & (S - 1)) != 0) {
    printf("S is %d \n", S); fflush(stdout);
    printf("ERROR: S must be a power of 2\n");
    return NULL;
    }

    if ((B & (B - 1)) != 0 || B < 4) {
      printf("ERROR: B must be a power of 2 and at least 4\n");
      return NULL;
    }

    struct cache *cache = malloc(sizeof(struct cache));
    cache->W = W;
    cache->S = S;
    cache->B = B;
    cache->mem = mem;
    for (int i = 0; i < S; i++)
    for (int j = 0; j < W; j++) {
        cache->sets[i].blocks[j].valid = 0;
    }

    return cache;
}

// Deletes a cache and frees its memory
void cache_delete(struct cache *cache) {
    free(cache);
}

// Gets the index of the set for a given memory address
int cache_get_set_index(struct cache *cache, int addr) {
    return (addr / cache->B) % cache->S;
}

// Gets the tag for a given memory address
int cache_get_tag(struct cache *cache, int addr) {
    return addr / (cache->S * cache->B);
}

// Reads a word from the cache
void cache_read(struct cache *cache, int addr, char op) {
    int set_index = cache_get_set_index(cache, addr);
    int tag = cache_get_tag(cache, addr);

    for (int i = 0; i < cache->W; i++)  {
        if (cache->sets[set_index].blocks[i].valid && cache->sets[set_index].blocks[i].tag == tag) {
            // Block is valid and has the correct tag, so we can return the data from the cache
            long data = cache->sets[set_index].blocks[i].data[(addr / 4) % cache->B];
            // We need to print the real lru-order
            printf("op: %c, addr: %d, data: %ld, HIT, lru_order\n", op, addr, data);
            break;
        }
    }
    
    // Block is not valid or has the wrong tag, so we need to load it from main memory
    int cache_miss_index = 0;
    for (int i = 1; i < cache->W; i++) {
        if (!cache->sets[set_index].blocks[i].valid) {
            // Replace the first invalid block
            cache_miss_index = i;
            break;
        }
    }

    cache->sets[set_index].blocks[cache_miss_index].valid = 1;
    cache->sets[set_index].blocks[cache_miss_index].tag = tag;

    for (int i = 0; i < cache->B; i++) {
        cache->sets[set_index].blocks[cache_miss_index].data[i] = 
            memory_rd_w(cache->mem, (tag * cache->S * cache->B + set_index * cache->B + i) * 4);
        }
    int data = cache->sets[set_index].blocks[cache_miss_index].data[(addr / 4) % cache->B];
    cache_write(cache, addr, data, op);
}

// Writes a word to the cache
void cache_write(struct cache *cache, int addr, int data, char op) {
    int set_index = cache_get_set_index(cache, addr);
    int tag = cache_get_tag(cache, addr);
    for (int i = 0; i < cache->W; i++) {
        if (cache->sets[set_index].blocks[i].valid && 
                cache->sets[set_index].blocks[i].tag == tag) {
            
            // Write the data to main memory
            memory_wr_w(cache->mem, addr, data);

            // Block is valid and has the correct tag, so we can update the data in the cache
            cache->sets[set_index].blocks[i].data[(addr / 4) % cache->B] = data;

            printf("op: %c, addr: %d, data: %d, EVICT, lru_order\n", op, addr, data);
            
        return;
      }
    }

    // Block is not valid or has the wrong tag, so we need to load it from main memory
    int cache_miss_index = 0;
    for (int i = 1; i < cache->W; i++) {
        if (!cache->sets[set_index].blocks[i].valid) {
        // Replace  the first invalid block
        cache_miss_index = i;
        break;
        }
    }

    cache->sets[set_index].blocks[cache_miss_index].valid = 1;
    cache->sets[set_index].blocks[cache_miss_index].tag = tag;

    for (int i = 0; i < cache->B; i++) {
        cache->sets[set_index].blocks[cache_miss_index].data[i] = 
            memory_rd_w(cache->mem, (tag * cache->S * cache->B + set_index * cache->B + i) * 4);
        }

    cache->sets[set_index].blocks[cache_miss_index].data[(addr / 4) % cache->B] = data;

    printf("op: %c, addr: %d, data: %d, FILL, lru_order\n", op, addr, data);
    return;

    // At some point we shoudl DISCARD: 
    //printf("op: %c, addr: %d, data: %ld, EVICT, lru_order\n", op, addr, data);
}
