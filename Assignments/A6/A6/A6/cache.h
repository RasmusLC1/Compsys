#ifndef __CACHE_H__
#define __CACHE_H__

#define MAX_W 16 // Maximum number of ways in the cache
// #define S ; // Number of sets
// #define B; // Block size
#define  MAX_S 1024
#define  MAX_B 16 // Block size

struct cache_block;

struct cache_set;

struct cache;

// Initialize data in memory
void init(struct memory *mem, int addr, int data, char op);

// Creates a new cache and returns a pointer to it
struct cache *cache_create(int W, int S, long long B, struct memory *mem);

// Deletes a cache and frees its memory
void cache_delete(struct cache *cache);

// Gets the index of the set for a given memory address
int cache_get_set_index(struct cache *cache, int addr);

// Gets the tag for a given memory address
int cache_get_tag(struct cache *cache, int addr);

// Reads a word from the cache
void cache_read(struct cache *cache, int addr, char op);

// Writes a word to the cache
void cache_write(struct cache *cache, int addr, int data, char op);
#endif
