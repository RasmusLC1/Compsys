#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <stdint.h>
#include <errno.h>
#include <assert.h>

#include "record.h"
#include "id_query.h"

int *test = NULL; //global variable for quicksort and binary
struct naive_data *data;

struct naive_data {
  struct record *rs;
  int n;
};

int partition(int *array, int p, int j) {
    int pivot = array[p];
    int i=p-1;
    while (1) {
        do { j--; } while (pivot < array[j]);
            do { i++; } while (array[i] < pivot);
                if (i < j) {
                    int tmp = array[i]; //Swap the osm array around
                    array[i] = array[j];
                    array[j] = tmp;
                    struct record tmp2 = data -> rs[i]; //swap our rs array around 
                    data -> rs[i] = data -> rs[j];
                    data -> rs[j] = tmp2;
                } else {
                    return j+1;
                }
    }
}

void quicksort(int *arr, int start, int end) {
    if (end-start < 2) {
        return;
    }
    int q = partition(arr, start, end);
    quicksort(arr, start, q); //Left side of the recursive loop
    quicksort(arr, q, end);//right side of the recursive loop, goes into this staggered once the left side is complete
}

struct naive_data* mk_binary(struct record* rs, int n) {
    test = malloc(n*sizeof(int64_t));  
    data = malloc(sizeof(struct naive_data));
    data -> rs = rs;
    data -> n = n;
    for (int i = 0; i < n; i++){
        test[i] = data -> rs[i].osm_id;
    }
    quicksort(test, 0, n);
    return data;
}

int binarySearch(int64_t x, int low, int high) {
  while (low <= high) {
    int mid = low + (high - low) / 2;
    if (test[mid] == x){
      return mid;
    } else if (test[mid] < x) {
      low = mid + 1;
    }else
      high = mid - 1;
  }
  return -1;
}

void free_binary(struct naive_data* data) {
  free(data);
  free(test);
}

const struct record* lookup_binary(struct naive_data *data, int64_t needle) {
  int value;  
  value = binarySearch(needle, 0, data -> n);
  if (value == -1){
    return NULL;
  }
  return &data ->rs[value]; //Return the record that binary search found the needle in
}

int main(int argc, char** argv) {
  return id_query_loop(argc, argv,
                    (mk_index_fn)mk_binary,
                    (free_index_fn)free_binary,
                    (lookup_fn)lookup_binary);
}

