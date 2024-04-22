#include <stdio.h>
#include <stdlib.h>
#include <string.h>


char textstring[100];

char *TextfileReader(void) {
    char filename[256]; 
    int c;
    int i = 0;
    FILE *file;
    printf("enter filename: \n");
    scanf("%s", filename);
    printf("\n");
    file = fopen(filename, "r");    
    if (file != NULL) {
        while ((c = getc(file)) != EOF){
            textstring[i] = c;
            i++; 
        }
    } 
    printf("\n");
    return textstring;
}





