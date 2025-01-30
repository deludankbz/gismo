#ifndef DATATYPES_H
#define DATATYPES_H

#include <stdlib.h>
#include <stdbool.h>

/* Queue - Linked List data type */
typedef struct Node {
  int value;
  char *buffer;
  struct Node *next;
} Node;

typedef struct {
  size_t size;
  Node *head;
  Node *tail;
} Queue;

Queue *mkQueue();

size_t size(Queue *q);
bool isEmpty(Queue *q);

int vpeek(Queue *q, bool *status);
char *buffpeek(Queue *q, bool *status);

void addNode(Queue *q, int value);
int removeNode(Queue *q, bool *status);
void destroyQueue(Queue *q);

#endif // !DATATYPES_H
