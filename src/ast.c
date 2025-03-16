#include "include/ast.h"
#include "include/datatypes.h"
#include "include/errors.h"
#include "include/token.h"


bool status = false;

AST_Node *newASTNode(ASTNodeType type, Token *token, AST_Node *n_left, AST_Node *n_right);

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

  if (!nToken) { raiseError(E_NULLTOKEN, "nulltoken!\n"); }
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

AST_Node *parseExpression(Queue *tokens, ASTNodeType precedence) {
  AST_Node *left = parsePrimary(tokens);

  for (;;) {

    Token *peek = peekNext(tokens);
    int tokenPrec = getPrecedence(peek);

    if (tokenPrec < precedence) { break; } 
    Token *op = popNode(tokens, &status);

    AST_Node *right = parseExpression(tokens, tokenPrec + 1);
    left = newASTNode(AST_BINARY, op, left, right);
  }
  return left;
}


void printAST(AST_Node *node, int indent) {
    for (int i = 0; i < indent; i++) printf("  ");
    if (!node) { printf("leaf!\n"); return; }
    
    switch (node->type) {

        case AST_NUMBER:
            printf("NUMBER(%s)\n", node->content->value);
            break;

        case AST_IDENTIFIER:
            printf("IDENTIFIER(%s)\n", node->content->value);
            break;

        case AST_BINARY:
            printf("BINARY_OP(%s)\n", node->content->value);
            break;

        case AST_GROUPING:
            printf("GROUPING\n");
            break;

        case AST_PREFIX:
            printf("PREFIX(%s)\n", node->content->value);
            break;

        default: printf("Unknown AST node type\n");
    }

    printAST(node->n_left, indent + 1);
    printAST(node->n_right, indent + 1);
}
