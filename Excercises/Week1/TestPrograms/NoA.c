#include <stdio.h>
#include <string.h>

int main (int argc, char* argv[]){
    int aFound = 0;
    for (int i = 1; i < argc; i++){
        if (argv[i][0] == 'a'){
            printf("A found\n");
            aFound = 1;
            break;
        }
    }
    if (aFound == 0){
        for (int j = 1; j < argc; j++){
            puts(argv[j]);
        }     
    } 
}
