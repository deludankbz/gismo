#ifndef PARSER_H
#define PARSER_H

#include "ast.h"
#include "datatypes.h"
#include "lexer.h"
#include "token.h"


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
  Node* current_t;

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

  /* could return an AST_Node */
  AST_Program (*Program)(parser_t *self);
  AST_NumericLiteral (*NumericLiteral)(parser_t *self);
  void (*parse)(parser_t *self);
  void (*destroy)(parser_t *self);
};


/*==============*/
/* PARSER CLASS */
/*==============*/

parser_t *newParser(Lexer* lex);

#endif // !PARSER_H

