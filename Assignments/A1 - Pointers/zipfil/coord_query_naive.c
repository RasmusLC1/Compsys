#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <stdint.h>
#include <errno.h>
#include <assert.h>

#include "record.h"
#include "coord_query.h"

struct naive_data {
  struct record *rs;
  int n;
};
//Sets up the data structure
struct naive_data* mk_naive(struct record* rs, int n) {
  struct naive_data *data = malloc(sizeof(struct naive_data));
  data -> rs = rs;
  data -> n = n;
  return data;
}

void free_naive(struct naive_data* data) {
  free(data);
}

const struct record* lookup_naive(struct naive_data *data, double lon, double lat) {
  double tmp = 9999.00; //Set the tmp value really high to ensure it's always overwritten first try
  double euclid;
  int ivalue = NULL;
  for (int i = 0; i < data -> n; i++){
    euclid = sqrt((data ->rs[i].lon - lon)+(data -> rs[i].lat - lat)); //Euclidian function from assignment description
    if(euclid < tmp){ //Check if the value of our current value and the previous closest to see if this is closer
      tmp = euclid; //Overwrite our previous closest
      ivalue = i; //Save the current i value
    }
  }
  return &data -> rs[ivalue]; //Return the address of the data pointing to the rs index closest to the given coordinates
}

int main(int argc, char** argv) {
  return coord_query_loop(argc, argv,
                          (mk_index_fn)mk_naive,
                          (free_index_fn)free_naive,
                          (lookup_fn)lookup_naive);
}
