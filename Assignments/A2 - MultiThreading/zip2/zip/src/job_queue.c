#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "job_queue.h"

int job_queue_init(struct job_queue *job_queue, int capacity) {
    job_queue -> is_destroyed = false;
    job_queue -> num_jobs = 0;
    job_queue -> max_capacity = capacity;
    pthread_mutex_init(&job_queue->job_queue_mutex, NULL);
    pthread_cond_init(&job_queue->push_block_cond, NULL);
    pthread_cond_init(&job_queue->pop_block_cond, NULL);
    return 0;
}

int job_queue_destroy(struct job_queue *job_queue) {
    if (job_queue->num_jobs > 0) {
      pthread_cond_broadcast(&job_queue->pop_block_cond);
    }
  job_queue->is_destroyed = true;
  return 0;
}

int job_queue_push(struct job_queue *job_queue, void *data) {
    assert(pthread_mutex_lock(&job_queue->job_queue_mutex) == 0);
    while (job_queue -> num_jobs >= job_queue -> max_capacity){
        pthread_cond_wait(&job_queue->pop_block_cond, &job_queue->job_queue_mutex);
    }
    job_queue -> job_array[job_queue -> num_jobs] = data;
    job_queue -> num_jobs += 1;
    assert(pthread_cond_signal(&job_queue->push_block_cond) == 0);
    assert(pthread_mutex_unlock(&job_queue->job_queue_mutex) == 0);
    return 0;
}

int job_queue_pop(struct job_queue *job_queue, void **data) {
  assert(pthread_mutex_lock(&job_queue->job_queue_mutex) == 0);
  while (job_queue->num_jobs <= 0) {
    if (job_queue->is_destroyed) {
      assert(pthread_mutex_unlock(&job_queue->job_queue_mutex) == 0);
      return -1;
    }
    pthread_cond_wait(&job_queue->push_block_cond, &job_queue->job_queue_mutex);
  }
  *data = job_queue -> job_array[0];
  job_queue->num_jobs -= 1;
  for (int i = 0; i < job_queue->num_jobs; i++){
    job_queue -> job_array[i] = job_queue -> job_array[i+1];
  }
  
  assert(pthread_cond_signal(&job_queue->pop_block_cond) == 0);
  assert(pthread_mutex_unlock(&job_queue->job_queue_mutex) == 0);
  return 0;
}
