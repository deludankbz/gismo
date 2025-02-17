#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "include/datatypes.h"
#include "include/errors.h"


/* TOKEN STACK (QUEUE) */ 


Queue *createQueue() {
  Queue *newQueue = malloc(sizeof(Queue));
  if (!newQueue) { free(newQueue); raiseError(E_MALLOC, "malloc for newQueue went wrong!");}

  newQueue->head = NULL; newQueue->tail = NULL;
  newQueue->size = 0;
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

  newNode->value = value;
  newNode->tBuffer = newToken;
  newNode->next = NULL;

  /* special case if queue is empty */
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

void destroyQueue(Queue *q) {
  Node *currentNode = q->head;
  while (currentNode != NULL) {
    Node *temp = currentNode;
    currentNode = currentNode->next;
    free(temp->tBuffer->value);
    free(temp->tBuffer); free(temp);
  }

  free(q);
}

void printQueue(Queue *q, bool *status) {
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
