#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    remove("zFauxErrors.txt");
    remove("zFibErrors.txt");
    remove("zHistErrors.txt");
    printf("test\n");
    return 0;
}