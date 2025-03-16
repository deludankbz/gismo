#include "include/ast.h"
#include "include/datatypes.h"
#include "include/errors.h"
#include "include/token.h"
#include <stdio.h>


bool status = false;

AST_Node *newASTNode(ASTNodeType type, Token *token, AST_Node *n_left, AST_Node *n_right) {
  AST_Node *node = malloc(sizeof(AST_Node));
  if (!node) { raiseError(E_MALLOC, "malloc for ast->node went wrong!\n"); }

  node->type = type;
  node->content = token;

  node->n_left = n_left;
  node->n_right = n_right;

  /* not handled yet */
  node->children = (void*)0;

  /*printf("newASTNode! :: [%d, %s]\n", node->type, node->content->value);*/
  return node;
}

Token* peekNext(Queue *q) {
  if (q->head) { return q->head->tBuffer; }
  return NULL;
}

ASTNodeType getPrecedence(Token* token) {
  if (token == NULL) return 0;

  switch(token->type) {
    case T_PLUS:
    case T_MINUS:
      return 10;

    case T_STAR:
    case T_SLASH:
    case T_PERCENT:
      return 20;

    default: return 0;
  }
}


AST_Node *parsePrimary(Queue *q) {
  Token *nToken = popNode(q, &status);

  if (!nToken) { raiseWarn(E_NULLTOKEN, "nulltoken!\n"); }
  switch(nToken->type) {

    case T_NUMBER:
      return newASTNode(AST_NUMBER, nToken, NULL, NULL);

    case T_IDENTIFIER:
      return newASTNode(AST_IDENTIFIER, nToken, NULL, NULL);

    /* add these stupid fucking curly brackets; I HATE YOU CLANGD */
    case T_LPAREN: {
      AST_Node *expr = parseExpression(q, 0);
      Token *closing = popNode(q, &status);
      if (!closing || closing->type != T_RPAREN) { raiseError(E_SYNTAX, "Expected ')'\n") ; }
      return newASTNode(AST_GROUPING, nToken, expr, NULL);
    }

    case T_MINUS: {
      AST_Node *right = parseExpression(q, 30);
      return newASTNode(AST_PREFIX, nToken, right, NULL);
    }
    
    /* ? should run a clean-up after this function */
    default: raiseError(E_SYNTAX, "Unexpected nToken in primary: %d\n");
  }
}

AST_Node *parseExpression(Queue *q, ASTNodeType precedence) {
  AST_Node *left = parsePrimary(q);

  /* probally poo poo */
  while (1) {
    if (isEmpty(q)) { break; }

    Token *peek = peekNext(q);
    int tokenPrec = getPrecedence(peek);

    if (tokenPrec < precedence) { break; } 
    Token *op = popNode(q, &status);

    AST_Node *right = parseExpression(q, tokenPrec + 1);
    left = newASTNode(AST_BINARY, op, left, right);
  }

  return left;
}


void printAST(AST_Node *node, int indent) {
  for (int i = 0; i < indent; i++) { printf("  "); }
  if (!node) { printf("leaf!\n"); return; }

  if (node->type == AST_NUMBER) {
    printf("NUMBER(%s)\n", node->content->value);

  } else if (node->type == AST_IDENTIFIER) {
    printf("IDENTIFIER(%s)\n", node->content->value);

  } else if (node->type == AST_BINARY) {
    printf("BINARY_OP(%s)\n", node->content->value);

  } else if (node->type == AST_GROUPING) {
    printf("GROUPING\n");

  } else if (node->type == AST_PREFIX) {
    printf("PREFIX(%s)\n", node->content->value);
  }

  printf("Unknown AST node type\n");
  printAST(node->n_left, indent + 1);
  printAST(node->n_right, indent + 1);
}

void destroyAST(AST_Node *node, int *count) {
  if (!node) { return; }
  else {
    *count += 1;
    destroyAST(node->n_left, count);
    destroyAST(node->n_right, count);
  }
}
