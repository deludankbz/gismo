#include <stdlib.h>
#include "include/lexer.h"
#include "include/io.h"

/* Example comment */

int main() {
  char *buffer = openFile("/home/deludank/Documents/Code/C/gismo/main.gismo");
  Lexer *lex = lexInit(buffer);
  lexer(lex);

  free(lex); free(buffer);
}
