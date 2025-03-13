#ifndef PARSER_H
#define PARSER_H

#include "datatypes.h"
#include "lexer.h"


/* PARSER
    NOTE:
    Floats should be handled by the parser;
    e.g:
        0.5 -> | 0 | . | 5 | -> parse() -> Node (float: 0.5)
        .8 ->  | 0 | . | 8 | -> parse() -> Node (float: 0.8)
                 ^ parser should add 0 in-front of '.'
*/


typedef struct parser_t parser_t;

struct parser_t {
  Queue* tokens;
  Token* current_t;

  /* Backus-Naur Form */
  /*
   * Program
   *  : NumericLiteral
   *  ;
   *
   * NumericLiteral:
   *  : NUMBER
   *  ;
   */

  /*=========*/
  /* METHODS */
  /*=========*/

  void (*Program)(parser_t *self);
  void (*NumericLiteral)(parser_t *self);
} ;


/*==============*/
/* PARSER CLASS */
/*==============*/

parser_t *newParser(Lexer* lex);

void destroyParser(parser_t* parserObj);

#endif // !PARSER_H

