#include <stdio.h>
#include <stdlib.h>
#include "include/ast.h"
#include "include/lexer.h"
#include "include/io.h"

int main() {
  char *buffer = openFile("/home/deludank/workspace/C/gismo/main.gis");
  Lexer *lex = lexInit(buffer);
  lexer(lex);

  AST_Node *ast = parseExpression(lex->q, 0);
  /*printAST(ast, 0);*/
  int inode = 1;
  destroyAST(ast, &inode);
  printf("%d\n", inode);

  destroyLexer(lex);
  free(buffer);
}
