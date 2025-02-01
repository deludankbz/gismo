#ifndef DATATYPES_H
#define DATATYPES_H

#include <stdlib.h>
#include <stdbool.h>

/* Queue - Linked List data type */
typedef struct Node {
  /* TODO: FIX consider changing int value to a pointer for easier memory access & manipulation */
  int value;
  char *buffer;
  struct Node *next;
} Node;

typedef struct {
  size_t size;
  Node *head;
  Node *tail;
} Queue;

typedef struct Buffer {
  size_t buffsize;
  size_t lenght;
  char * buffer;
} Buffer;

Queue *mkQueue();

size_t size(Queue *q);
bool isEmpty(Queue *q);

int vpeek(Queue *q, bool *status);
char *buffpeek(Queue *q, bool *status);

void addNode(Queue *q, int value);
int removeNode(Queue *q, bool *status);
void destroyQueue(Queue *q);

/* AST - Abstract Syntax Tree datatype.
 * simple tree implementation; used directly by lexer
 * to store tokenized values.
*/
typedef struct TreeNode {
  /* n_Buffer - value to be stored */
  char *n_Buffer;

  TreeNode **node;

  struct TreeNode *left;
  struct TreeNode *right;
} TreeNode;

TreeNode *addTreeNode(char *Buffer);


#endif // !DATATYPES_H
