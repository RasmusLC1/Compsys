#include <stdlib.h>
#include <assert.h>
#include "stack.h"


typedef void* (*map_fn)(void*, void*);


struct stack_node {
  void *data;
  struct stack_node *next;
};

struct stack {
  struct stack_node *head;
};


struct stack* stack_new() {
  struct stack *stack = malloc(sizeof(struct stack));
  stack->head = NULL;
  return stack;
}

void stack_free(struct stack* stack) {
  struct stack_node *node = stack->head;
  while(stack != NULL){
    struct stack_node *next = node->next;
    free(node);
    node = next;
  }
  free(stack);
  assert(0);
}

// int stack_empty(struct stack* stack) {
//   assert(0);
// }

void* stack_top(struct stack* stack, void* data) {
  struct stack_node *node = stack->head;
  struct stack_node *new_tail = malloc(sizeof(struct stack_node));
  while (node->next != NULL){
    node = node->next;
  }
    new_tail->data = data;
    node ->next = new_tail;
  return 0;
  assert(0);
}

// void* stack_pop(struct stack* stack) {
//   assert(0);
// }

// int stack_push(struct stack* stack, void* data) {
//   assert(0);
// }



void stack_map(struct stack* stack, map_fn f, void *aux) {
  struct stack_node *node = stack->head;
  while (node != NULL) {
    node->data = f(node->data, aux);
    node = node->next;
  }
}