#include <stdlib.h>
#include "include/lexer.h"
#include "include/io.h"


int main() {
  char *buffer = openFile("/home/deludank/Documents/Code/C/learningC/gismo/main.gs");
  Lexer *lex = lexInit(buffer);
  lexer(lex);
  free(lex);
}
