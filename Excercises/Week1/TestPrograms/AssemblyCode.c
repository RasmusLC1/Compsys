#include <stdio.h>

int add1(int a, int b){
    int c;
    c =a+b;
    return c;
}

int add2(int a, int b){
    b =b+a;
    return b;
}

int main(){
    int a, b, c;
    scanf("%d %d", &a, &b);
    c = add2(a,b);
    printf("%d", c);
    printf("\n");
    return 1;
}