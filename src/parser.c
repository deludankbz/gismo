#include <stddef.h>
#include <stdio.h>
#include "include/parser.h"


/* PARSER
    NOTE:
    Floats should be handled by the parser;
    e.g:
        0.5 -> | 0 | . | 5 | -> parse() -> Node (float: 0.5)
        .8 ->  | 0 | . | 8 | -> parse() -> Node (float: 0.8)
                 ^ parser should add 0 in-front of '.'
*/


/*=========*/
/* METHODS */
/*=========*/

void impl_Program(parser_t* self) { printf("Program was ran!\n"); }
void impl_NumericLiteral(parser_t* self) { printf("NumericLiteral was ran!\n"); }


/*==============*/
/* PARSER CLASS */
/*==============*/

parser_t *newParser(Lexer *lex) {
  parser_t *newPaserObj = malloc(sizeof(parser_t));
  if (!newPaserObj) { return NULL; }

  /* method reg */
  newPaserObj->Program = impl_Program;
  newPaserObj->NumericLiteral = impl_NumericLiteral;
  return newPaserObj;
}

void destroyParser(parser_t* parserObj) { free(parserObj); }

