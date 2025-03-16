#ifndef AST_H
#define AST_H

#include "datatypes.h"
#include "token.h"


/* LOOKUPS */
typedef enum {
  DEFAULT,
  COMMA,
  ASSIGN,
  LOGIC,
  RELATIONAL,
  ADDITIVE,
  MULT,
  UNARY,
  CALL,
  MEMBER,
  PRIMARY
} BindingPower;


/* AST
  NOTE:
    There should have been two types of nodes:
    Binary ones with two children nodes or 
    Multinode with n children nodes
*/


/* could this enum be used as a precedence order list? */
typedef struct AST_Node AST_Node;

typedef enum ASTNodeType {
  AST_BINARY,
  AST_NUMBER,
  AST_IDENTIFIER,
  AST_GROUPING,
  AST_PREFIX,
} ASTNodeType;


struct AST_Node {

  ASTNodeType type; 
  Token *content;

  /* if all the ast_nodes are null, we'll know that we reached a leaf (end) */
  AST_Node *n_left;
  AST_Node *n_right;
  /* OR */
  AST_Node **children;

};

Token* peekNext(Queue *q);

AST_Node *newASTNode(ASTNodeType type, Token *token, AST_Node *n_left, AST_Node *n_right);
ASTNodeType getPrecedence(Token* token) ;

AST_Node *parseExpression(Queue *tokens, ASTNodeType precedence);
AST_Node *parsePrimary(Queue *q);



#endif /* AST_H */
