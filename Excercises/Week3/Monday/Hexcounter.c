#include <stdio.h>
#include <assert.h>

int main (){
    char filename[256];
    char test[100];
    int c;
    int i = 0;
    FILE *file;
    struct _IO_FILE *px;
    printf("enter filename: \n");
    scanf("%s", filename);
    printf("\n");
    file = fopen(filename, "r");
    px = file;    
    if (file != NULL) {
        while ((c = getc(file)) != EOF ){
             test[i] = c;
             printf("char address: %.2x\n", (int) c);
             i++;
        }
    } 
    printf("\n");
    printf("%s\n", test);
    printf("file address: %p\n", (void*)px);
    return 1;
}