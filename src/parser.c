#include <stdlib.h>
#include <stdlib.h>
#include "include/parser.h"
#include "include/errors.h"


/*
  PARSER:

  NOTE FIX: Parser *initParser()
 
  if raiserError exits the program on !p->tokens; it wont free p.
  thats not only a problem here functions inside lexer.c and token.c have the 
  same problem
*/


Parser *initParser() {
  Parser *p = malloc(sizeof(Parser));
  if (!p) { free(p); raiseError(E_MALLOC, "malloc() for Parser interface went wrong!"); }
  p->tokens = malloc(sizeof(p->tokens));
  if (!p->tokens) { free(p->tokens); raiseError(E_MALLOC, "malloc() for p->tokens interface went wrong!"); }

  return p; 
}

void Parse(Token token) {
}
