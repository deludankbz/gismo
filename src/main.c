#include <stdlib.h>
#include "include/lexer.h"
#include "include/parser.h"
#include "include/io.h"

int main() {
  char *buffer = openFile("/home/deludank/Documents/Code/C/gismo/main.gis");
  Lexer *lex = lexInit(buffer);
  lexer(lex);

  parser_t *parsing = newParser(lex);
  parsing->NumericLiteral(parsing);

  destroyParser(parsing); destroyLexer(lex);
  free(buffer);
}
