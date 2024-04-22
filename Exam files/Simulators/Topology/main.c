#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h> 

#define INFINITY 9999
#define MAX 6

struct Node{
    char name;
    int distance;
};


void Dijkstra(struct Node map[10][10], int n, int start, int index) {
  int cost[MAX][MAX], distance[MAX], pred[MAX];
  int visited[MAX], count, mindistance, nextnode, i, j;

  // Creating cost matrix with zeros to infinite
  for (i = 0; i < n; i++)
    for (j = 0; j < n; j++)
      if (map[i][j].distance == 0){
        cost[i][j] = INFINITY;
      }else{
        cost[i][j] = map[i][j].distance;
      }


  for (i = 0; i < n; i++) {
    distance[i] = cost[start][i];
    pred[i] = start;
    visited[i] = 0;
  }

  distance[start] = 0;
  visited[start] = 1;
  count = 1;
  

  int nameIndex[10];
  for (int i = 0; i < 10; i++){
    nameIndex[i] = 1;
  }
  
  while (count < n - 1) {
    mindistance = INFINITY;

    for (i = 0; i < n; i++)
      if (distance[i] < mindistance && !visited[i]) {
        mindistance = distance[i];
        nextnode = i;
      }

    visited[nextnode] = 1;
    for (i = 0; i < n; i++)
      if (!visited[i])
        if (mindistance + cost[nextnode][i] < distance[i]) {
          distance[i] = mindistance + cost[nextnode][i];
          nameIndex[i] = i;
          
          pred[i] = nextnode;
        }
    count++;
  }
  // Printing the distance
  for (i = 0; i < n; i++)
    if (i != start) {
      printf("%d, %c\t\t", distance[i], map[i][nameIndex[i]-1].name);
    }
}


int main() {

    FILE *fptr;
    fptr = fopen("map.txt", "r");
    char line[30];
    int index = 0;   
    
    struct Node map[10][10];
    struct Node mapholder[10][10];
    while (fgets(line, sizeof(line), fptr)){
        map[index][0].name = line[2];
        map[index][0].distance = line[4]-'0';
        map[index][1].name = line[6];
        map[index][1].distance = line[8]-'0';
        map[index][2].name = line[10];
        map[index][2].distance = line[12]-'0';
        map[index][3].name = line[14];
        map[index][3].distance = line[16]-'0';
        map[index][4].name = line[18];
        map[index][4].distance = line[20]-'0';
        map[index][5].name = line[22];
        map[index][5].distance = line[24]-'0';
        index++;
    }
    for (int i = 0; i < 6; i++){
        for (int j = 0; j < 6; j++){
            mapholder[i][j].name = map[i][j].name;
            mapholder[i][j].distance = 0;
        }
    }
    char letters[7] = {'A', 'B', 'C', 'D', 'E', 'F'};
    char insertLetters[7] = {' ',' ',' ',' ',' ',' '};
    int n = 6, u = 0, pathfound = 0;
    printf("step\tN’\t\tD(B),p(B)\tD(C),p(C)\tD(D),p(D)\tD(E),p(E)\tD(F),p(F)\n");
    for (int i = 0; i < 6; i++){
        for (int j = 0; j < 6; j++){
            mapholder[i][j].distance = map[i][j].distance;
        }
        insertLetters[i] = letters[i];
        printf("%d\t\t%s\t", i, insertLetters);

        Dijkstra(mapholder, n, u, i);
        putchar('\n');
    }

    return 0;
}