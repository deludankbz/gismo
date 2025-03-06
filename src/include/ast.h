#ifndef AST_H
#define AST_H

#include "token.h"
#include <stdint.h>

/* AST */

typedef enum NodeType {
  PROGRAM,
  LITERAL,
  IDENTIFIER,
  BIN_EXPR,

} NodeType;

typedef struct {} Stmt;

typedef struct {} Expr;

typedef struct Node {
  struct {
    NodeType type;
    uint32_t numNodes;
  };
  Token token;
} Node;

typedef struct AST {
  Node *nodes;
  int numNodes;
} AST ;

static void initAST();


#endif // !AST_H
