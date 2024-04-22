#include <stdio.h>
#include <assert.h>

int ex1(){
    int x;
    int *p;
    p = &x;
    *p = 0;
    return x;
}

int ex2(){
    int x;
    int *p;
    int **pp;
    pp = &p;
    p = &x;
    **pp = 0;
    return x;
}
int ex3(){
    int x, y;
    int *p = &y;
    p = &x;
    *p = 0;
    p = &y;
    *p = 1;
    return x;
}
int ex4(){
    int x, y = 0;
    int* arr[2];
    arr[0] = &x;
    arr[1] = arr[0];
    *(arr[1]) = 1;
    *(arr[0]) = *(arr[0]) - 1;
    return (x+y);
}

int main(){
    int x = ex4();
    printf("%d", x);
    printf("\n");
    return 0;
}