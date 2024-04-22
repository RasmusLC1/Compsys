#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <math.h>

struct values{
    int a;
    int b;
    int c;
};

struct thread{
    char instruction;
    char value;
};
    

int main(){
    struct values graph[20][20];
    struct thread thread1[10];
    struct thread thread2[10];
    int instructions = Reader(thread1, thread2);
    Graph_Creator(graph, thread1, thread2, instructions);
    return 0;
}

int Reader(struct thread *thread1, struct thread *thread2){
    FILE *fptr;
    fptr = fopen("threads.txt", "r");
    char line[30];
    int i = 0;
    while (fgets(line, sizeof(line), fptr)){
        thread1[i].instruction = line[0];
        thread1[i].value = line[2];
        thread2[i].instruction = line[6];
        thread2[i].value = line[8];
        i++;
    }
    return i;
    
}


void Graph_Creator(struct values graph[20][20], struct thread *thread1, struct thread *thread2, int instructions){
    for (int i = 0; i < instructions; i++){
        for (int j = 0; j < instructions; j++){
            graph[i][j].a = 0;
            graph[i][j].b = 0;
            graph[i][j].c = 0;
        }
        
    }

    int a = 1, b = 1, c = 1;    
    switch (thread1[0].value){
            case 'a':
                if (thread1[0].instruction == 'P'){
                    a--;
                } else if (thread1[0].instruction == 'V'){
                    a++;
                }
                break;
            case 'b':
                if (thread1[0].instruction == 'P'){
                    b--;
                    
                } else if (thread1[0].instruction == 'V'){
                    b++;
                }
                break;
            case 'c':
                if (thread1[0].instruction == 'P'){
                    c--;
                } else if (thread1[0].instruction == 'V'){
                    c++;
                }
                
                break;
            default:
                break;
            }

    for(int i = 0; i < instructions; i++){
        switch (thread2[i].value){
            case 'a':
                if (thread2[i].instruction == 'P'){
                    a--;
                } else if (thread2[i].instruction == 'V'){
                    a++;
                }
                break;
            case 'b':
                if (thread2[i].instruction == 'P'){
                    b--;
                    
                } else if (thread2[i].instruction == 'V'){
                    b++;
                }
                break;
            case 'c':
                if (thread2[i].instruction == 'P'){
                    c--;
                } else if (thread2[i].instruction == 'V'){
                    c++;
                    
                }
                
                break;
            default:
                break;
            }
        graph[i][0].b = b;
        graph[i][0].a = a;
        graph[i][0].c = c;
            
    }
        
    
    int jIndex;


    for (int i = 0; i < instructions; i++){
        
        for (int j = 1; j < instructions; j++){
            jIndex = j-1;
            switch (thread1[j].value){
            case 'a':
                if (thread1[j].instruction == 'P'){
                    graph[i][j].a = graph[i][jIndex].a-1;
                    graph[i][j].c = graph[i][jIndex].c;
                    graph[i][j].b = graph[i][jIndex].b;
                } else if (thread1[j].instruction == 'V'){
                    graph[i][j].a = graph[i][jIndex].a+1;
                    graph[i][j].c = graph[i][jIndex].c;
                    graph[i][j].b = graph[i][jIndex].b;
                }
                break;
            case 'b':
                if (thread1[j].instruction == 'P'){
                    graph[i][j].b = graph[i][jIndex].b-1;
                     graph[i][j].a = graph[i][jIndex].a;
                    graph[i][j].c = graph[i][jIndex].c;
                    
                } else if (thread1[j].instruction == 'V'){
                    graph[i][j].b = graph[i][jIndex].b+1;
                    graph[i][j].a = graph[i][jIndex].a;
                    graph[i][j].c = graph[i][jIndex].c;
                }
                break;
            case 'c':
                if (thread1[j].instruction == 'P'){
                    graph[i][j].c = graph[i][jIndex].c-1;
                    graph[i][j].a = graph[i][jIndex].a;
                    graph[i][j].b = graph[i][jIndex].b;
                } else if (thread1[j].instruction == 'V'){
                    graph[i][j].c = graph[i][jIndex].c+1;
                    graph[i][j].a = graph[i][jIndex].a;
                    graph[i][j].b = graph[i][jIndex].b;
                }
                
                break;
            default:
                break;
            }

        }
        
    }



    for (int i = instructions-1; i != -1; i--){
        for (int j = 0; j < instructions; j++){
            printf("%d,%d,%d\t\t", graph[i][j].a, graph[i][j].b, graph[i][j].c );
        }
        putchar('\n');
        putchar('\n');
    }
    
}



