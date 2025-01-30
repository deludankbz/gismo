#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "include/datatypes.h"
#include "include/errors.h"

/* Queue datatype - Linked list
 */ 
Queue *mkQueue() {
  Queue *q = malloc(sizeof(Queue));
  if (!q) {raiseError(q, E_MALLOC, "malloc of q went wrong!\n");}

  q->head = NULL;
  q->tail = NULL;
  q->size = 0;

  return q;
}

size_t size(Queue *q) { return q->size; }

bool isEmpty(Queue *q) {
  if (q->size == 0) { return true; }
  return false;
}

int peek(Queue *q, bool *status) {
  /* if Queue is empty we can't peform a peek */
  if (isEmpty(q)) { *status = false; }

  *status = true;
  return q->head->value; 
}


void addNode(Queue *q, int value){
  Node *newNode = malloc(sizeof(Node));
  if (!newNode) {printf("addNode!\n");}
  newNode->value = value;
  newNode->next = NULL;

  if (isEmpty(q)) { 
    q->head = newNode; q->tail = newNode;
  } else {
    q->tail->next = newNode;
    q->tail = newNode;
  }

  q->size++;
}

int removeNode(Queue *q, bool *status) {
  if (isEmpty(q)) { *status = false; return 0; }
  *status = true;
  
  int value = q->head->value;
  Node *oldHead = q->head;

  if (q->size == 1) {
    q->head = NULL;
    q->tail = NULL;
  } else {
    q->head = q->head->next;
  }

  free(oldHead);
  return value;
}

void destroyQueue(Queue *q) {
  Node *currentNode = q->head;
  /* while cNode not NULL reach tail */
  while (currentNode != NULL) {
    Node *tempNode = currentNode;
    currentNode = currentNode->next;
    free(tempNode);
  }
  free(q);
}

// not implemented

/* TODO: better print or return char* string ¯_(ツ)_/¯ */
void printQueue(Queue *q, bool *status) {
  if (isEmpty(q)) { *status = false; return; }

  *status = true;

  Node *currentNode = q->head;

  printf("\n");
  while (currentNode != NULL) {
    printf("%i->", currentNode->value);
    currentNode = currentNode->next;
  }
  free(currentNode);

  printf("\n\n%i;%i", q->head->value, q->tail->value);
}

void exampleUsage() {
  Queue *newQ = mkQueue();
  bool status = false;

  int index = 1;
  while (newQ->size != 50) {
    addNode(newQ, index);
    index++;
  }

  printQueue(newQ, &status);
  destroyQueue(newQ);
  if (!newQ) {printf("newQ destroyed!\n");}
}

/*int main() {*/
/*  exampleUsage();*/
/*}*/
