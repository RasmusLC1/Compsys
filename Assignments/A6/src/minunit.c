#include <stdio.h>
#include "minunit.h"
#include "cache.h"
#include <time.h>

int tests_run = 0;

static char* compare_test () {
    struct cache_block a;
    struct cache_block b;
    a.leastUsed = 1;
    b.leastUsed = 0;
    mu_assert("Compare test 1", Compare(&a, &b) == -1);
    a.leastUsed = 0;
    b.leastUsed = 1;
    mu_assert("Compare test 2", Compare(&a, &b) == 1);
    a.leastUsed = 0;
    b.leastUsed = 0;
    mu_assert("Compare test 3", Compare(&a, &b) == 0);
    return 0;
}

static char* qsort_test() {
    struct cache cache;
    int i, j, n = 1;
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            cache.cacheBlocks[i][j].leastUsed = i*j;
            mu_assert("Quicksort test 1",
                      cache.cacheBlocks[i][j].leastUsed == i*j);
        }
    }
    qsort(&cache.cacheBlocks[1], 4, sizeof(struct cache_block), Compare);
    mu_assert("Quicksort test 2", cache.cacheBlocks[n][0].leastUsed == 3);
    mu_assert("Quicksort test 3", cache.cacheBlocks[n][1].leastUsed == 2);
    mu_assert("Quicksort test 4", cache.cacheBlocks[n][2].leastUsed == 1);
    mu_assert("Quicksort test 5", cache.cacheBlocks[n][3].leastUsed == 0);
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            if (i != n) {
                mu_assert("Quicksort test 6",
                          cache.cacheBlocks[i][j].leastUsed == i*j);
            } else {
                mu_assert("Quicksort test 7",
                          cache.cacheBlocks[i][j].leastUsed != i*j);
            }
        }
    }
    return 0;
}

static char* create_cache_test() {
    struct memory *mem = memory_create();
    int ways = 4, sets = 128, blockSize = 16;
    struct cache cache;
    mu_assert("Create cache test 1", cache.ways != 4);
    mu_assert("Create cache test 2", cache.sets != 128);
    mu_assert("Create cache test 3", cache.blockSize != 16);
    cache = Cache_Create(ways, sets, blockSize, mem);
    for (int i = 0; i < sets; i++) {
        for (int j = 0; j < ways; j++) {
            mu_assert("Create cache test 4",
                      cache.cacheBlocks[i][j].leastUsed == 0);
            mu_assert("Create cache test 5",
                      cache.cacheBlocks[i][j].isValid == 0);
            mu_assert("Create cache test 6",
                      cache.cacheBlocks[i][j].isModified == 0);
        }
    }
    mu_assert("Create cache test 7", cache.ways == 4);
    mu_assert("Create cache test 8", cache.sets == 128);
    mu_assert("Create cache test 9", cache.blockSize == 16);
    return 0;
}

// cache read test
static char* cache_read_test() {
    struct memory *mem = memory_create();
    int ways = 4, sets = 128, blockSize = 16;
    struct cache cache;
    struct input_data inputData;
    cache = Cache_Create(ways, sets, blockSize, mem);
    inputData.addr = 20;
    inputData.data = 20;
    inputData.counter = 0;
    memory_wr_w(mem, inputData.addr, inputData.data);    
    Cache_Read(&cache, &inputData);
    inputData.counter++;
    const int setIndex = inputData.addr / cache.ways;
    qsort(&cache.cacheBlocks[setIndex], 4, sizeof(struct cache_block), Compare);
    
    mu_assert("cache read test 1", cache.cacheBlocks[setIndex][0].data == 20);
    mu_assert("cache read test 2", cache.cacheBlocks[setIndex][0].tag == 20);
    inputData.addr = 20;
    inputData.data = 34;

    //initialise new values
    memory_wr_w(mem, inputData.addr, inputData.data);

    //should fill
    Cache_Read(&cache, &inputData);
    inputData.counter++;
    qsort(&cache.cacheBlocks[setIndex], 4, sizeof(struct cache_block), Compare);

    mu_assert("cache read test 4", cache.cacheBlocks[setIndex][0].tag == 20);
    mu_assert("cache read test 5", cache.cacheBlocks[setIndex][0].data == 34);
    mu_assert("cache read test 3", cache.cacheBlocks[setIndex][1].tag == 20);
    mu_assert("cache read test 6", cache.cacheBlocks[setIndex][1].data == 20);

    //hit
    Cache_Read(&cache, &inputData);
    inputData.counter++;
    qsort(&cache.cacheBlocks[setIndex], 4, sizeof(struct cache_block), Compare);
    mu_assert("cache read test hit", cache.cacheBlocks[setIndex][0].tag == 20);
    mu_assert("cache read test hit", cache.cacheBlocks[setIndex][0].data == 34);
    mu_assert("cache read test hit", cache.cacheBlocks[setIndex][1].tag == 20);
    mu_assert("cache read test hit", cache.cacheBlocks[setIndex][1].data == 20);

    inputData.addr = 20;
    inputData.data = 20;

    //hit
    Cache_Read(&cache, &inputData);
    inputData.counter++;
    qsort(&cache.cacheBlocks[setIndex], 4, sizeof(struct cache_block), Compare);
    mu_assert("cache read test hit rev", cache.cacheBlocks[setIndex][1].tag == 20);
    mu_assert("cache read test hit rev", cache.cacheBlocks[setIndex][1].data == 34);
    mu_assert("cache read test hit rev", cache.cacheBlocks[setIndex][0].tag == 20);
    mu_assert("cache read test hit rev", cache.cacheBlocks[setIndex][0].data == 20);

    return 0;
}

// cache mem read test
static char * cache_read_blackbox_test() {
    struct memory *mem = memory_create();
    int ways = 4, sets = 128, blockSize = 16;
    struct cache cache;
    struct input_data inputData;
    cache = Cache_Create(ways, sets, blockSize, mem);
    inputData.addr = 20;
    inputData.data = 20;
    inputData.counter = 0;
    const int setIndex = inputData.addr / cache.ways;
    memory_wr_w(mem, inputData.addr, inputData.data);    

    for (int i = 0; i < 100; i++){
        Cache_Read(&cache, &inputData);
        inputData.counter++;
        qsort(&cache.cacheBlocks[setIndex], 4, sizeof(struct cache_block), Compare);
        
        mu_assert("cache read blackbox test", cache.cacheBlocks[setIndex][0].data == 20);
        mu_assert("cache read blackbox test", cache.cacheBlocks[setIndex][0].tag == 20);
        mu_assert("cache read blackbox test", cache.cacheBlocks[setIndex][0].isValid == 1);
        mu_assert("cache read blackbox test", cache.cacheBlocks[setIndex][0].leastUsed == i);
        mu_assert("cache read blackbox test", cache.cacheBlocks[setIndex][0].isModified == 0);
    }
    
    return 0;
}

// cache write test
static char* cache_write_test() {
    struct memory *mem = memory_create();
    int ways = 4, sets = 128, blockSize = 16;
    struct cache cache;
    struct input_data inputData;
    cache = Cache_Create(ways, sets, blockSize, mem);
    inputData.addr = 20;
    inputData.data = 20;
    inputData.counter = 0;
    const int setIndex = inputData.addr / cache.ways;

    memory_wr_w(mem, inputData.addr, inputData.data);    
    Cache_Read(&cache, &inputData);
    inputData.counter++;
    mu_assert("cache write test 1", cache.cacheBlocks[setIndex][0].data == 20);
    mu_assert("cache write test 1", cache.cacheBlocks[setIndex][0].tag == 20);
    mu_assert("cache write test 1", cache.cacheBlocks[setIndex][0].isValid == 1);
    mu_assert("cache write test 1", cache.cacheBlocks[setIndex][0].leastUsed == 0);
    mu_assert("cache write test 1", cache.cacheBlocks[setIndex][0].isModified == 0);


    //Discard test
    inputData.addr = 20;
    inputData.data = 52;
    Cache_Write(&cache, &inputData);
    inputData.counter++;
    mu_assert("cache write test 2", memory_rd_w(cache.mem, inputData.addr) == 20);
    mu_assert("cache write test 2", cache.cacheBlocks[setIndex][0].data == 52);
    mu_assert("cache write test 2", cache.cacheBlocks[setIndex][0].tag == 20);
    mu_assert("cache write test 2", cache.cacheBlocks[setIndex][0].isValid == 1);
    mu_assert("cache write test 2", cache.cacheBlocks[setIndex][0].leastUsed == 1);
    mu_assert("cache write test 2", cache.cacheBlocks[setIndex][0].isModified == 1);

    //evict test
    inputData.addr = 20;
    inputData.data = 32;
    Cache_Write(&cache, &inputData);
    inputData.counter++;
    mu_assert("cache write test 2", memory_rd_w(cache.mem, inputData.addr) == 52);
    mu_assert("cache write test 2", cache.cacheBlocks[setIndex][0].data == 32);
    mu_assert("cache write test 2", cache.cacheBlocks[setIndex][0].tag == 20);
    mu_assert("cache write test 2", cache.cacheBlocks[setIndex][0].isValid == 1);
    mu_assert("cache write test 2", cache.cacheBlocks[setIndex][0].leastUsed == 2);
    mu_assert("cache write test 2", cache.cacheBlocks[setIndex][0].isModified == 0);

    //discard test
    inputData.addr = 20;
    inputData.data = 43;
    Cache_Write(&cache, &inputData);
    inputData.counter++;
    mu_assert("cache write test 2", memory_rd_w(cache.mem, inputData.addr) == 52);
    mu_assert("cache write test 2", cache.cacheBlocks[setIndex][0].data == 43);
    mu_assert("cache write test 2", cache.cacheBlocks[setIndex][0].tag == 20);
    mu_assert("cache write test 2", cache.cacheBlocks[setIndex][0].isValid == 1);
    mu_assert("cache write test 2", cache.cacheBlocks[setIndex][0].leastUsed == 3);
    mu_assert("cache write test 2", cache.cacheBlocks[setIndex][0].isModified == 1);
    inputData.counter++;
    return 0;
}

// cache fill test with larger ways blackbox
static char* Cache_Fill_Test() {
    struct memory *mem = memory_create();
    int ways = 8, sets = 500, blockSize = 16;
    struct cache cache;
    struct input_data inputData;
    cache = Cache_Create(ways, sets, blockSize, mem);
    inputData.counter = 0;
    int setIndex; 
    for (int i = 0; i < 400; i += 4){
        inputData.data = 20;
        inputData.addr = i+4;
        setIndex = inputData.addr / cache.ways;
        srand(time(NULL));
        inputData.data = (rand() %  inputData.addr);
        memory_wr_w(cache.mem, inputData.addr, inputData.data);
        Cache_Read(&cache, &inputData);
        inputData.counter++;
        Cache_Read(&cache, &inputData);
        inputData.counter++;
        
        mu_assert("cache write test 2", memory_rd_w(cache.mem, inputData.addr) == inputData.data);
        mu_assert("cache write test 2", cache.cacheBlocks[setIndex][0].data == inputData.data);
        mu_assert("cache write test 2", cache.cacheBlocks[setIndex][0].tag == inputData.addr);
        mu_assert("cache write test 2", cache.cacheBlocks[setIndex][0].isValid == 1);
        mu_assert("cache write test 2", cache.cacheBlocks[setIndex][0].leastUsed == inputData.counter-1);
        mu_assert("cache write test 2", cache.cacheBlocks[setIndex][0].isModified == 0);
    }
    return 0;
}



static char * all_tests() {
    mu_run_test(compare_test);
    mu_run_test(qsort_test);
    mu_run_test(create_cache_test);
    mu_run_test(cache_read_test);
    mu_run_test(cache_read_blackbox_test);
    mu_run_test(cache_write_test);
    mu_run_test(Cache_Fill_Test);
    return 0;
}

int main(int argc, char **argv) {
    char *result = all_tests();
    if (result != 0) {
        printf("%s\n", result);
    }
    else {
        printf("ALL TESTS PASSED\n");
    }
    printf("Tests run: %d\n", tests_run);

    return result != 0;
}
