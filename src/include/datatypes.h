#include "token.h"
#include <stdlib.h>
#include <stdbool.h>

#ifndef DATATYPES_H
#define DATATYPES_H

/* LINKED LIST (QUEUE)
 * TODO FIX: consider changing int value to a pointer for easier memory access & manipulation
 */


typedef struct Node {
  int value;
  Token *tBuffer;
  struct Node *next;
} Node;

typedef struct {
  size_t size;
  int lenght; /* could cause poo poo shit */
  Node *head;
  Node *tail;
} Queue;

typedef struct Buffer {
  size_t buffsize;
  size_t lenght;
  char *buffer;
} Buffer;

Queue *createQueue();

size_t size(Queue *q);
bool isEmpty(Queue *q);

int peek(Queue *q, bool *status);

void addNode(Queue *q, int value, Token *newToken);
int removeNode(Queue *q, bool *status);
void destroyQueue(Queue *q);

void printQueue(Queue *q, bool *status);

#endif // !DATATYPES_H
