#include <stdio.h>
#include <string.h>

int main (int argc, char* argv[]){
    char* word[20];
    if (argc <= 1 ){
        printf("Wrong Number\n");
        // scanf("%s",word[5]);
        // int length = sizeof word;
        // main(length+1,word);
    }
    else{
        for (int j = 0; j < 2; j++){
            for (int i = 1; i < argc; i++){
                word[i] = argv[i];
                printf("%s ", word[i]);
            }
            memset(word, 0, argc);
            printf("\n");
        }
    }
}
