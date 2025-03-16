#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "include/datatypes.h"
#include "include/errors.h"
#include "include/token.h"


/* TOKEN STACK (QUEUE) */ 


Queue *createQueue() {
  Queue *newQueue = malloc(sizeof(Queue));
  if (!newQueue) { free(newQueue); raiseError(E_MALLOC, "malloc for newQueue went wrong!");}

  newQueue->head = NULL; newQueue->tail = NULL;
  newQueue->size = 0;
  newQueue->lenght = 0;
  return newQueue;
}

size_t size(Queue *q) { return q->size; }

bool isEmpty(Queue *q) { return (q->size == 0); }

int peek(Queue *q, bool *status) {
  if (isEmpty(q)) { *status = false; return NULL; }
  *status = true;
  return q->head->value;
}

void addNode(Queue *q, int value, Token *newToken) {
  Node *newNode = malloc(sizeof(Node));
  if (!newNode) {free(newNode); raiseError(E_MALLOC, "malloc for newNode went wrong!");}

  newNode->value = value;
  newNode->tBuffer = newToken;
  newNode->next = NULL;

  /* Special case if queue is empty */
  if (isEmpty(q)) { q->head = newNode; q->tail = newNode; }
  else { q->tail->next = newNode; q->tail = newNode; }
  q->size++;
}

int removeNode(Queue *q, bool *status) {
  if (isEmpty(q)) {*status = false; return NULL; }
  *status = true;

  int value = q->head->value;
  Node *oldHead = q->head;

  if (q->size == 1) { q->head = q->tail = NULL; }
  else { q->head = q->head->next; }

  free(oldHead); q->size--;
  return value;
}

/* pop the node; return token */
Token *popNode(Queue *q, bool *status) {
  if (isEmpty(q)) {*status = false; return NULL; }
  *status = true;

  int value = q->head->value;
  Node *oldHead = q->head;

  if (q->size == 1) { q->head = q->tail = NULL; }
  else { q->head = q->head->next; }

  Token *token = oldHead->tBuffer;
  if (!token) { raiseWarn(E_NULLTOKEN, "nullToken @ queue->id: %d\n", oldHead->value); return NULL; }

  free(oldHead); q->size--;
  return token;
}

void destroyQueue(Queue *q) {
  Node *currentNode = q->head;
  while (currentNode != NULL) {
    Node *temp = currentNode;
    currentNode = currentNode->next;
    /* Don't free tBuffer if it's type EOF 
     * since it's value is stored on the stack and not on the heap
     * we can't free it. */
    if (temp->tBuffer->type != T_EOF) {free(temp->tBuffer->value);}
    free(temp->tBuffer); free(temp);
  }

  free(q);
}

void printQueue(Queue *q, bool *status) {
  printf("----\n");

  if (isEmpty(q)) {
    *status = false; return;
  } else {
    *status = true;
    Node *currentNode = q->head;

    printf("TOKEN STACK:\n");
    while (currentNode != NULL) {
      if (currentNode->tBuffer != NULL) { 
        printf("[\x1b[1;95m%d\x1b[0m: ( \x1b[1;36m%d\x1b[0m : \x1b[1;32m%s\x1b[0m )]\n", 
        currentNode->value, 
        currentNode->tBuffer->type, 
        currentNode->tBuffer->value);
      }
      currentNode = currentNode->next;
    }
  }
}
