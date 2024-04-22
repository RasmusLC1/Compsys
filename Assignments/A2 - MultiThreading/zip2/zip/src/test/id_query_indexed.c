#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <stdint.h>
#include <errno.h>
#include <assert.h>

#include "record.h"
#include "id_query.h"

struct index_record {
    int64_t osm_id;
    const struct record *rs;
};

struct indexed_data {
    struct index_record *irs;
    int n;
};

struct index_record* buildindex(struct record *rs, int n){
    struct index_record *irs = malloc(n * sizeof(struct index_record)); //Assign n*the amount of index we have as we use a for loop
    for (int i = 0; i < n; i++){
        irs[i].osm_id = i; //overwrites the osmid value with a new i value for the indexed record
    }
    irs -> rs = rs; //Point irs to rs
    return irs;
}

struct indexed_data* mk_indexed(struct record* rs, int n) {
    struct indexed_data *idata = malloc(sizeof(struct indexed_data));
    struct index_record *irs = malloc(n * sizeof(struct index_record));
    irs = buildindex(rs, n); //helper function
    idata -> irs = irs; //idata points towards irs
    idata -> n = n; //point it towards the size of the array
    return idata;
}

void free_indexed(struct indexed_data* data) {
  free(data);
}

const struct record* lookup_indexed(struct indexed_data *data, int64_t needle) {
  for (int i = 0; i < data->n; i++){
    if (data -> irs[i].osm_id == needle){ //We can look up the index value, say 500 then it finds the 500th index
        return &data -> irs -> rs[i]; //Get the index from rs[i]
    }
  }
  return NULL;
}

int main(int argc, char** argv) {
    return id_query_loop(argc, argv,
            (mk_index_fn)mk_indexed,
            (free_index_fn)free_indexed,
            (lookup_fn)lookup_indexed);
}
