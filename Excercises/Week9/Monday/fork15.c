#include "csapp.h"

int i = 0;

void try(){
    pid_t fork1 = Fork();
    if (fork1 == 0){
        pid_t fork2 = Fork();
        pid_t fork3 = Fork();
        i++;
        printf("\nTest %d", i);
        return;
    }
}


int main(){
    try();
    i++;
    printf("Test %d\n", i);
    exit (0);
}