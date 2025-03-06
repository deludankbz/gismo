#include "token.h"

#ifndef PARSER_H
#define PARSER_H


/*
 * ASSOCIATIVITY:
 *    can be either:
 *
 *    left-to-right
 *    right-to-left
*/


/* acts kinda like a boolean */
typedef enum {

  ASSOC_LEFT,
  ASSOC_RIGHT,

} Associativity;


typedef struct {

  TokenType type;
  int precedenceLevel;
  Associativity assoc;

} OperatorPrecedence;


#endif // !PARSER_H
