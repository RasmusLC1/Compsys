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

struct Node{
    struct record *record;
    struct Node *left;
    struct Node *right;
    struct Node *previous;
    int index;
    double point;
    int axis;
};

struct naive_data *data;

int partition(int p, int j) {
    double pivot = sqrt(data -> rs[p].lat + data -> rs[p].lon);
    int i=p-1;
    while (1) {
        do { j--; } while (pivot < sqrt(data -> rs[j].lat + data -> rs[j].lon)); //Compare our pivot to the osm_id which has been typecast to int to prevent segmentation fault
          do { i++; } while (sqrt(data -> rs[i].lat + data -> rs[i].lon) < pivot);
              if (i < j) {
                  struct record tmp2 = data -> rs[i]; //swap our rs array around 
                  data -> rs[i] = data -> rs[j];
                  data -> rs[j] = tmp2;
              } else {
                  return j+1;
              }
    }
}

void quicksort(int start, int end) {
    if (end-start < 2) {
        return;
    }
    int q = partition(start, end);
    quicksort(start, q); //Left side of the recursive loop
    quicksort(q, end);//right side of the recursive loop, goes into this staggered once the left side is complete
}


struct Node* kdtree(struct record *points, int start, int end, int axis){
    if (end <= start){
      return NULL;
    }
    struct Node *node = malloc(sizeof(struct Node));
    int n = start + (end - start)/2;
    axis = (axis + 1) % 2;
    node -> previous = node;
    node -> record = points;
    node -> index = n;
    node -> axis = axis;
    node -> point = sqrt(points[n].lon + points[n].lat);
    node -> left = kdtree(points, start, n, axis);
    node -> right = kdtree(points, n+1, end, axis);
    return node;
}

struct naive_data* mk_kdtree(struct record* rs, int n) {
  data = malloc(n*sizeof(struct naive_data));
  struct Node *root = malloc(sizeof(struct Node));
  data -> rs = rs;
  quicksort(0, n);
  root = kdtree(data -> rs, 0, n, 0);
  data -> node = root;
  return data;
}

void free_kdtree(struct naive_data* data) {
  free(data);
}



int LookUp(struct Node *root, struct Node *closest, double target){
  if (root -> index == NULL){
    return NULL;
  } else if ((target - root -> point) < (target - closest -> point)){
    closest = root;
    // printf("closest: %f\nleft: %f\nright: %f\n", target - closest -> point, target - root -> left -> point, target - root -> right -> point);
  } 
  if (target - root -> left -> point < 0 || target - root -> right -> point < 0){
    printf("%f", target - closest -> point);
    return closest -> index;
  }
  if (target - root -> left -> point < target - root -> right -> point){
    root = root -> left;
    // printf("left\nvalue: %f\n", root -> point);
    LookUp(root, closest, target);
  } else{
    root = root -> right;
    // printf("right\nvalue: %f\n", root -> point);
    LookUp(root, closest, target);
  }
}


const struct record* lookup_kdtree(struct naive_data *data, double lon, double lat) {
  struct Node *closest = malloc(sizeof(struct Node));
  int test;
  test = LookUp(data -> node, closest, sqrt(lon+lat));
  return &data -> rs[test];
}

int main(int argc, char** argv) {
  return coord_query_loop(argc, argv,
                          (mk_index_fn)mk_kdtree,
                          (free_index_fn)free_kdtree,
                          (lookup_fn)lookup_kdtree);
}
