#ifndef DATATYPES_H
#define DATATYPES_H

#include <stdlib.h>
#include <stdbool.h>

typedef struct Node {
  int value;
  struct Node *next;
} Node;

typedef struct {
  size_t size;
  Node *head;
  Node *tail;
} Queue;

/* TODO: put into tokens.h
 * inherits struct base from 'Queue'
 */
typedef struct TokenQueue {
  Queue base;
  struct tokenContent;
} TokenQueue;

/* C reates token */
Queue *mkQueue();

size_t size(Queue *q);
bool isEmpty(Queue *q);
int peek(Queue *q, bool *status);

void addNode(Queue *q, int value);
int removeNode(Queue *q, bool *status);
void destroyQueue(Queue *q);


#endif // !DATATYPES_H
