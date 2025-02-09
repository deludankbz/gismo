#ifndef DATATYPES_H
#define DATATYPES_H

#include <stdlib.h>
#include <stdbool.h>


/* LINKED LIST (QUEUE)
 * TODO FIX: consider changing int value to a pointer for easier memory access & manipulation
 */


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


/* AST - ABSTRACT SYNTAX TREE DATATYPE
 *
 * NOTE: 
 *    doesn't work yet.
 * 
 * simple tree implementation; used directly by lexer
 * to store tokenized values.
 */


typedef struct TreeNode {
  /* n_Buffer - value to be stored */
  char *n_Buffer;

  /* tree only supports 2 children per node */
  struct TreeNode *left, *right;
  struct TreeNode *prev, *next;
} TreeNode;

typedef struct Tree {
  TreeNode *root; // absolute first
  TreeNode *tail; // last node created
} Tree;

static TreeNode *makeRoot(char *Buffer);
static Tree *makeTree(TreeNode *root, char *Buffer);
void addNode();


#endif // !DATATYPES_H
