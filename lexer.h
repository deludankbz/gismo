#include <stddef.h>

typedef enum {
  T_NUMBER,
  T_IDENT,
  T_EQUALS,
  T_OPENPAREN, T_CLOSEPAREN,

  T_BINARY, // +, -, /, //, *, ** etc...  
  T_TERNARY // Conditional; ==; !=; or, and etc...
} TokenType;

typedef struct {
  TokenType type;
  char *value;

  int line;     // for debugging lines
  int column;   // for debugging columns
} Token;

/* This function recieves a source object and loops through each
char until it reaches '\0' */
extern Token *tokenize(const char *source, size_t *arrTokenSize);

