#include "record.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

// Sanity check to make sure we are reading the right kind of file.
int input_looks_ok(FILE *f) {
  char *line = NULL; //Starts at line 0
  size_t n;
  if (getline(&line, &n, f) == -1) { //If these values return -1 that means that the file has no content
    return -1;
  }

  int ret;
  if (strcmp(line, "name	alternative_names	osm_type	osm_id	class	type	lon	lat	place_rank	importance	street	city	county	state	country	country_code	display_name	west	south	east	north	wikidata	wikipedia	housenumbers\n") == 0) { //Checks with strcmp if the line given is equal to this string
    ret = 1; //The file is valid
  } else {
    ret = 0; //The file is invalid
  }

  free(line); //frees the line from memory once it's been checked
  return ret;
}

// Read a single record from an open file.  This is pretty tedious, as
// we handle each field explicitly. Each field is different things depending on what
// the object is, if it is a city, a street, name etc
int read_record(struct record *r, FILE *f) {
  char *line = NULL; //Sets the string line to be empty
  size_t n; //size_t = unsigned integer
  if (getline(&line, &n, f) == -1) { //Checks if the line is valid
    free(line); //If it's not then it's freed from memory
    return -1;
  }

  r->line = line; //Pointer to line

  char* start = line; //Set our start line to the current one
  char* end; //End is not delegated yet

  if ((end = strstr(start, "\t"))) { //Looks for the end of the start line which is given by a tab, which signals the start of the next line
    r->name = start; *end = 0; start = end+1; //Name is defined in the record.h file as a string, the pointer now points towards the
    //name, which is set to start value, end is reset to null and start becomes end +1
  }

  if ((end = strstr(start, "\t"))) {
    r->alternative_names = start; *end = 0; start = end+1;
  }

  if ((end = strstr(start, "\t"))) {
    r->osm_type = start; *end = 0; start = end+1;
  }

  if ((end = strstr(start, "\t"))) {
    r->osm_id = atol(start); *end = 0; start = end+1;
  }

  if ((end = strstr(start, "\t"))) {
    r->class = start; *end = 0; start = end+1;
  }

  if ((end = strstr(start, "\t"))) {
    r->type = start; *end = 0; start = end+1;
  }

  if ((end = strstr(start, "\t"))) {
    r->lon = atof(start); *end = 0; start = end+1;
  }

  if ((end = strstr(start, "\t"))) {
    r->lat = atof(start); *end = 0; start = end+1;
  }

  if ((end = strstr(start, "\t"))) {
    r->place_rank = atoi(start); *end = 0; start = end+1;
  }

  if ((end = strstr(start, "\t"))) {
    r->importance = atof(start); *end = 0; start = end+1;
  }

  if ((end = strstr(start, "\t"))) {
    r->street = start; *end = 0; start = end+1;
  }

  if ((end = strstr(start, "\t"))) {
    r->city = start; *end = 0; start = end+1;
  }

  if ((end = strstr(start, "\t"))) {
    r->county = start; *end = 0; start = end+1;
  }

  if ((end = strstr(start, "\t"))) {
    r->state = start; *end = 0; start = end+1;
  }

  if ((end = strstr(start, "\t"))) {
    r->country = start; *end = 0; start = end+1;
  }

  if ((end = strstr(start, "\t"))) {
    r->country_code = start; *end = 0; start = end+1;
  }

  if ((end = strstr(start, "\t"))) {
    r->display_name = start; *end = 0; start = end+1;
  }

  if ((end = strstr(start, "\t"))) {
    r->west = atof(start); *end = 0; start = end+1;
  }

  if ((end = strstr(start, "\t"))) {
    r->west = atof(start); *end = 0; start = end+1;
  }

  if ((end = strstr(start, "\t"))) {
    r->east = atof(start); *end = 0; start = end+1;
  }

  if ((end = strstr(start, "\t"))) {
    r->north = atof(start); *end = 0; start = end+1;
  }

  if ((end = strstr(start, "\t"))) {
    r->wikidata = start; *end = 0; start = end+1;
  }

  if ((end = strstr(start, "\t"))) {
    r->wikipedia = start; *end = 0; start = end+1;
  }

  if ((end = strstr(start, "\t"))) {
    r->housenumbers = start; *end = 0; start = end+1;
  }

  return 0;
}
//Reads the file given to it
struct record* read_records(const char *filename, int *n) {
  FILE *f = fopen(filename, "r"); //Opens the file
  *n = 0;

  if (f == NULL) {
    return NULL; //If file does not exists it returns 0
  }

  if (!input_looks_ok(f)) { //If the file is not good it returns null
    return NULL;
  }

  int capacity = 100;
  int i = 0;
  struct record *rs = malloc(capacity * sizeof(struct record)); //Allocates ememory for rs
  while (read_record(&rs[i], f) == 0) { //As long as the code runs recursively it will increment rs[i] with +1 to get all the different values
    i++;
    if (i == capacity) { //If i is greater than capacity then it doubles the capacity, this is to ensure effiencient space usage and imporve spaciality
      capacity *= 2;
      rs = realloc(rs, capacity * sizeof(struct record)); //Realocates the memory to match the updated capacity 
    }
  }

  *n = i; //n definition
  fclose(f); //Closes the file
  return rs;
}
//Frees the memory as it is no longer needed
void free_records(struct record *rs, int n) {
  for (int i = 0; i < n; i++) { //Goes through all the different rs elements and frees them
    free(rs[i].line);
  }
  free(rs);
}
