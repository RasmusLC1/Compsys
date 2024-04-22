// Setting _DEFAULT_SOURCE is necessary to activate visibility of
// certain header file contents on GNU/Linux systems.
#define _DEFAULT_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fts.h>

// err.h contains various nonstandard BSD extensions, but they are
// very handy.
#include <err.h>

#include <pthread.h>

#include "job_queue.h"


const char *globalneedle;
pthread_mutex_t stdout_mutex = PTHREAD_MUTEX_INITIALIZER;


int fauxgrep_file(char const *path) {
  FILE *f = fopen(path, "r");

  if (f == NULL) {
    warn("failed to open %s", path);
    return -1;
  }

  char *line = NULL;
  size_t linelen = 0;
  int lineno = 1;

  while (getline(&line, &linelen, f) != -1) {
    if (strstr(line, globalneedle) != NULL) {
      printf("%s:%d: %s", path, lineno, line);
    }

    lineno++;
  }

  free(line);
  fclose(f);

  return 0;
}

void* Worker_thread(void *arg){
  struct job_queue *job = arg;
  while(1){
    char *line;
    if (job_queue_pop(job, (void**)&line) == 0) {
      fauxgrep_file(line);
      free(line);
    } else {
      break;
    }
  }

  return NULL;
}



int main(int argc, char * const *argv) {
  if (argc < 2) {
    err(1, "usage: [-n INT] STRING paths...");
    exit(1);
  }

  int num_threads = 4;
  char const *needle = argv[1];
  globalneedle = needle;
  char * const *paths = &argv[2];


  if (argc > 3 && strcmp(argv[1], "-n") == 0) {
    num_threads = atoi(argv[2]);
    if (num_threads < 1) {
      err(1, "invalid thread count: %s", argv[2]);
    }
  
    needle = argv[3];
    paths = &argv[4];

  } else {
    needle = argv[1];
    paths = &argv[2];
  }

  
  // assert(0); // Initialise the job queue and some worker threads here.
  struct job_queue jq;
  job_queue_init(&jq, 64);
  pthread_t *threads = calloc(num_threads, sizeof(pthread_t));
  for (int i = 0; i < num_threads; i++) {
    if (pthread_create(&threads[i], NULL, &Worker_thread, &jq) != 0) {
      err(1, "pthread_create() failed");
    }
  }



  // FTS_LOGICAL = follow symbolic links
  // FTS_NOCHDIR = do not change the working directory of the process
  //
  // (These are not particularly important distinctions for our simple
  // uses.)
  int fts_options = FTS_LOGICAL | FTS_NOCHDIR;

  FTS *ftsp;
  if ((ftsp = fts_open(paths, fts_options, NULL)) == NULL) {
    err(1, "fts_open() failed");
    return -1;
  }
  
  FTSENT *p;
  while ((p = fts_read(ftsp)) != NULL) {
    
    switch (p->fts_info) {
    case FTS_D:
      break;
    case FTS_F:
      job_queue_push(&jq, (void*)strdup(p->fts_path));
      break;
    default:
      break;
    }
  }
  // Shut down the job queue and the worker threads here.
  job_queue_destroy(&jq);
  // Wait for all threads to finish.  This is important, at some may
  // still be working on their job.
  for (int i = 0; i < num_threads; i++) {
    if (pthread_join(threads[i], NULL) != 0) {
      err(1, "pthread_join() failed");
    }
  }
  free(threads);
}
