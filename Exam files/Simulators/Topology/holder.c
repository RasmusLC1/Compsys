#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h> 


#define V 6

struct Destinations{
    char name;
    int distance;
};

struct Node{
    char name;
    int distance;
};



int minDistance(int dist[], bool sptSet[]) {
   int min = INT_MAX, min_index;
   for (int v = 0; v < V; v++)
   if (sptSet[v] == false && dist[v] <= min)
      min = dist[v], min_index = v;
   return min_index;
}

int printSolution(int dist[], int n) {
   printf("Vertex Distance from Source\n");
   for (int i = 0; i < V; i++)
      printf("%d \t %d\n", i, dist[i]);
}


void dijkstra(struct Node map[10][10], int src) {
   int dist[V];
   bool sptSet[V];
   for (int i = 0; i < V; i++)
      dist[i] = INT_MAX, sptSet[i] = false;
      dist[src] = 0;
   for (int count = 0; count < V - 1; count++) {
      int u = minDistance(dist, sptSet);
      sptSet[u] = true;
      for (int v = 0; v < V; v++){
         if (!sptSet[v] && map[u][v].distance && dist[u] != INT_MAX &&
            dist[u] + map[u][v].distance < dist[v]) dist[v] = dist[u] + map[u][v].distance;
      }
      printSolution(dist, V);
   }
}
int main() {

    FILE *fptr;
    fptr = fopen("map.txt", "r");
    char line[30];
    int index = 0;   
    
    struct Node map[10][10];

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
            printf("%d,%c\t", map[i][j].distance, map[i][j].name);
        }
        putchar('\n');
        
    }
    
   dijkstra(map, 0);
   return 0;
}