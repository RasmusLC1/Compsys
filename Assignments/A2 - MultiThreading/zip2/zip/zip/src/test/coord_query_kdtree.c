#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <stdint.h>
#include <errno.h>
#include <assert.h>
#include <math.h>
#include "record.h"
#include "coord_query.h"


struct naive_data {
  struct record *rs;
  struct Node *node;
  int n;
};
struct naive_data *data;
struct Node{
    struct record *record;
    struct Node *left, *right;
    int index;
    double lat, lon;
    int axis;
};


int cmpfunc (const void * a, const void * b)
{
    return ( *(int*)a - *(int*)b );
}




struct Node* kdtree(int start, int end, int axis){
    if (end <= start){
      return NULL;
    }
    struct Node *node = malloc(sizeof(struct Node));
    int n = start + (end - start)/2;
    axis = (axis + 1) % 2;
    node -> record = data -> rs;
    node -> index = n;
    node -> axis = axis;
    node -> lat = data -> rs[n].lat;
    node -> lon = data -> rs[n].lon;
    double test;
    if (axis == 1){
      test = data -> rs -> lat;
      void qsort(test, start, end, cmpfunc);
    }else if (axis == 0){
      test = data -> rs -> lon;
      void qsort(test, start, end, cmpfunc);
    }
    node -> left = kdtree(start, n, axis);
    node -> right = kdtree(n+1, end, axis);
    return node;
}

struct naive_data* mk_kdtree(struct record* rs, int n) {
  data = malloc(n*sizeof(struct naive_data));
  struct Node *root = malloc(sizeof(struct Node));
  data -> rs = rs;
  root = kdtree(0, n, 0);
  // for (int i = 0; i < 7; i++){
  //   printf("lat: %f\n", root -> record[root -> index].lat);
  //   printf("lon: %f\n", root -> record[root -> index].lon);
  //   root = root -> left;
  // }
  data -> node = root;
  return data;
}

void free_kdtree(struct naive_data* data) {
  free(data);
}





int LookUp(struct Node *closest, double lat, double lon, struct Node *root){
  
  if (root == NULL){
    return closest -> index;
  }
  double diff;
  if (root -> axis == 0){
    if (( lon - root -> lon) < (lon - closest -> lon )){
      closest = root;
    } 
    diff = root -> lon - lon;
  } 
  
  else if (root -> axis == 1){
    if ((lat -  root -> lat) < (lat - closest -> lat)){
    closest = root;
    } 
    diff = root -> lat - lat;
  }
  // printf("lat: %f\nlon: %f\n", root -> lat, root -> lon);
  
  // radius = sqrt(pow(root -> lon - lon, 2)+pow(root -> lat - lat, 2));
  float  radius = sqrt(pow(data ->rs[closest -> index].lon - lon, 2)+pow(data -> rs[closest -> index].lat - lat, 2)); //Euclidian function from assignment description
  printf("%f", radius);
  if (diff >= 0 || radius > fabs(diff)){
    // printf("left\n\n");
    root = root -> left;
    LookUp(closest, lon, lat, root);
  }
  if (diff <=  0 || radius > fabs(diff)){
    // printf("right\n\n");
    root = root -> right;
    LookUp(closest, lon, lat, root);
  }
}


const struct record* lookup_kdtree(struct naive_data *data, double lon, double lat) {
  struct Node *root = malloc(sizeof(struct Node));
  root = data -> node;
  struct Node *closest = malloc(sizeof(struct Node));
  int test = NULL;
  printf("test: %d\n", test);
  test = LookUp(closest, lon, lat, root);
  printf("test2 %d\n", test);
  return &data -> rs[test];
}

int main(int argc, char** argv) {
  return coord_query_loop(argc, argv,
                          (mk_index_fn)mk_kdtree,
                          (free_index_fn)free_kdtree,
                          (lookup_fn)lookup_kdtree);
}
