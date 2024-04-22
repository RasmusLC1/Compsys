#include <stdio.h>
#include <stdlib.h>
#include <string.h>



void *TextfileReader(FILE *file, FILE *file2) {
    char *textstring = malloc(sizeof(FILE)*100);
    int c;
    int i = 0;    
    if (file != NULL) {
        while ((c = getc(file)) != EOF){
            textstring[i] = c;
            i++; 
        }
        fprintf(file2 ,"fail:\n%s\n_________________\n", textstring);

    }
    free (textstring);
    return NULL;

}


void CompareFiles(FILE *file1, FILE *file2, FILE *file3){
    char ch1 = getc(file1);
    char ch2 = getc(file2);
    int error = 0, pos = 0, line = 1;
    while (ch1 != EOF && ch2 != EOF){
        pos++;
        if (ch1 == '\n' && ch2 == '\n'){
            line++;
            pos = 0;
        }
        if (ch1 != ch2){
            error++;
            break; 
        }
        ch1 = getc(file1);
        ch2 = getc(file2);
    }
    if (error > 0){
        TextfileReader(file1, file3);
    }
    
}

int main(){
    FILE *logFaux, *logFauxcomp, *FauxErrors, *logFib, *logFibcomp, *FibErrors, *loghistcomp, *loghist, *HistErrors;
    
    
    logFaux = fopen("logFaux.txt", "r");
    logFauxcomp = fopen("logFauxcomp.txt", "r");
    FauxErrors = fopen("zFauxErrors.txt", "a");

    CompareFiles(logFaux, logFauxcomp, FauxErrors);
    fclose(logFaux);
    fclose(logFauxcomp);
    fclose(FauxErrors);


    logFib = fopen("logFib.txt", "r");
    logFibcomp = fopen("logFibcomp.txt", "r");
    FibErrors = fopen("zFibErrors.txt", "a"); 
    CompareFiles(logFib, logFibcomp, FibErrors);
    
    fclose(logFib);
    fclose(logFibcomp);
    fclose(FibErrors);



    loghist = fopen("loghist.txt", "r");
    loghistcomp = fopen("loghistcomp.txt", "r");
    HistErrors = fopen("zHistErrors.txt", "a");

    CompareFiles(loghist, loghistcomp, HistErrors);
    
    fclose(loghistcomp);
    fclose(loghist);
    fclose(HistErrors);
    return 0;
}