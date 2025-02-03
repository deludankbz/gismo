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
  struct T_INT{
    TokenType type;

  };
  TokenType type;
  char *value;
} Token;

/* inherits struct base from 'Queue' */
const char *makeToken(char *source);

static char *concat(char *source, ...);

#endif // !TOKEN_H
