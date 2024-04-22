#include "memory.h"
#include "cache.h"
#include <stdio.h>
#include <stdlib.h>
//#include <string.h>
// #include <time.h>

int main(int argc, char *argv[])
{
    int W = atoi(argv[1]);
    printf("W to int is: %d\n", W);
    int S = atoi(argv[2]);
    printf("S to int is: %d\n", S);
    long long B = atoi(argv[3]);
    printf("B to int is: %lld \n", B);
    struct memory *mem = memory_create();

    struct cache* new_cache = cache_create(W, S, B, mem);
    
    // WHERE DO WE GET OUR op, addr, data FROM????
    char op;
    int addr;
    long data;

    while(1) {
        printf("Enter \"op addr data\" or several lines like that: \n");
        scanf("%c %d %ld", &op, &addr, &data); fflush(stdout);
            if (op == 'i') {
                init(mem, addr, data, op);
            } else if (op == 'r' && (addr % 4 == 0)) {
                cache_read(new_cache, addr, op);
            } else if (op == 'w' && (addr % 4 == 0)) {
                cache_write(new_cache, addr, data, op);
            } else {
                printf("ERROR: The written op \"%c\" is an invalid input\n", op);
            }
    }
    memory_delete(mem);
    cache_delete(new_cache);
}
