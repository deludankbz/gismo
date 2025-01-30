#ifndef TOKEN_H
#define TOKEN_H

#include <stddef.h>
/* TODO: add more enums
*/
typedef enum {
  T_ARBITRARY,
  T_NUMBER,
  T_IDENT,
  T_EQUALS,
  T_OPENPAREN, T_CLOSEPAREN,

  T_BINARY,  // +, -, /, //, *, ** etc...  
  T_TERNARY, // Conditional; ==; !=; or, and etc...
  T_UNKOWN
} TokenType;

typedef struct Token {
  TokenType type;
  char *value;
} Token;

#endif // !TOKEN_H
