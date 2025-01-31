#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "include/datatypes.h"
#include "include/errors.h"

/* #Queue datatype - Linked list
 * TODO: new methods; findByValue(); removeByValue();
 * TODO: FIX: consider changing int value to char *.
 * NOTE: we NEED to fetch nodes by ADDRESS and NOT BY FRGGIN INT VALUE!
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

bool isEmpty(Queue *q) { if (q->size == 0) { return true; } return false; }

/* peek node value */
int nodePeek(Node *node) { return node->value; }

int peek(Queue *q, bool *status) {
  /* if Queue is empty we can't peform a peek */
  if (isEmpty(q)) { *status = false; }

  *status = true;
  return q->head->value; 
}

/* adds new tail */
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

/* only removes head */
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
  raiseWarn(E_MALLOC, "expect free error");
  free(currentNode);
}

void queueExample() {
  Queue *newQ = mkQueue();
  bool status = false;

  // our objective is just to addNode and change its buffer 
  // and then safely free it
  addNode(newQ, 66);
  /* NOTE: always change buffer of tail */
  newQ->tail->buffer = "test here!";                // maybe malloc wasn't so usefull
  printf("%s\n", newQ->tail->buffer);               // prints tail (last node)

  /* error example */
  /*printf("expect error!\n");*/
  /*printf("%s\n", newQ->tail->buffer);*/

  /* causes memory leaks if not freed; keeps running if we don't do anything
  * TODO: findByValue() -> *node; otherwise we won't be able to free node buffers */
  /*free(newQ->head->buffer);*/
  printQueue(newQ, &status);
  destroyQueue(newQ);
}



/* #AST - Abstract Syntax Tree datatype */
TreeNode *addTreeNode(char *Buffer) {
  TreeNode *newTree = malloc(sizeof(TreeNode));
  if (newTree != NULL) {
    newTree->left = NULL;
    newTree->right = NULL;
    newTree->n_Buffer = Buffer;
  }
  return newTree;
}

TreeNode *getRootNode(TreeNode *node); 

/* tab printer; it's static to make that this abomination doesn't scape this file */
static void pTabs(int numTabs) { for (int i = 0; i < numTabs; i++) { printf("  "); }}

/* prints tree */
static void __fetchTree__(TreeNode *rootNode, int tabs, int isRight) {
  if (rootNode == NULL) {
    return;
  }
  pTabs(tabs);

  /* branch connector; if true > "└─" else false "├─"*/
  if (tabs > 0) { printf("%s", isRight ? "└─" : "├─");}
  /* just prints root node */
  printf("%s\n", rootNode->n_Buffer);

  /* prints left or right */
  if (rootNode->left || rootNode->right) {
    __fetchTree__(rootNode->left, (tabs + 1), 0);
    __fetchTree__(rootNode->right, (tabs + 1), 1);
  }
}

void fetchTree(TreeNode *rootNode) { 
  /* call it's recursive brother */
  __fetchTree__(rootNode, 0, 1); 
}

static void example_TreeNode() {
  TreeNode *n1 = addTreeNode("Program");
  TreeNode *n2 = addTreeNode("VarDeclaration");
  TreeNode *n3 = addTreeNode("INT");
  TreeNode *n4 = addTreeNode("'4'");
  TreeNode *n5 = addTreeNode("5");
  TreeNode *n6 = addTreeNode("6");

  n1->left = n2;
  n2->left = n3;
  n2->right = n4;

  fetchTree(n1);

  free(n1);
  free(n2);
  free(n3);
  free(n4);
  free(n5);
}
