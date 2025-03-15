#ifndef AST_H
#define AST_H

#include "token.h"
#include <stdint.h>


/* AST */


typedef enum {
  AST_BINARY,
  AST_NUMBER,
  AST_IDENTIFIER,
  AST_GROUPING,
  AST_PREFIX,
} ASTNodeType;


typedef struct ASTNode {
  ASTNodeType type;
  Token *token;
  struct ASTNode *left;   
  struct ASTNode *right;  
} ASTNode;


#endif 
