#ifndef PARSER_H
#define PARSER_H

#include "token.h"


/*
  PARSER
 */

typedef struct Parser {
  Token **tokens;   /*parsed tokens*/
  int pos;
} Parser ;

Parser *initParser();

void Parse(Token token);

#endif // !PARSER_H
