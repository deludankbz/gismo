#ifndef TOKEN_H
#define TOKEN_H

#include <stddef.h>
#include "datatypes.h"
/* TODO: add more enums */

typedef enum {
  T_ARBITRARY,
  T_NUMBER,
  T_IDENT,
  T_EQUALS,
  T_OPENBLOCK, T_CLOSEBLOCK,

  T_BINARY,  // +, -, /, //, *, ** etc...  
  T_TERNARY, // Conditional; ==; !=; or, and etc...
  T_UNKOWN
} TokenType;

typedef struct Token {
  TokenType type;
  char *value;
} Token;

/* inherits struct base from 'Queue' */
typedef struct {
  Queue base;
  struct Token;
} TokenQueue ;

const char *makeToken(char *source);

char *concat(char *source, ...);

#endif // !TOKEN_H
