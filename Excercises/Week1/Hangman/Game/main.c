#include <stdio.h>
/* To use the functions defined in Functions.c I need to #include Functions.h */
#include "Functions.h"
#include "TextfileReader.h"
char textstring[100];


int sumtest(){
    int a, b, c;
    printf("Insert two numbers: ");
    if(scanf("%d %d", &a, &b)!=2){
        fputs("Invalid input", stderr);
    } else{
        c = Sub(a, b);
    }
    return c;  
}

int main(void){
    TextfileReader();
    printf("%s", textstring);
    return 0;
}

