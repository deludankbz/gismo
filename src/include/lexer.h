#ifndef LEXER_H
#define LEXER_H

#include <stddef.h>
#include "token.h"

typedef struct {
  char current;           // current char
  int i;                  // counter
  size_t bufferSize;      // sizeof(const char *buffer) 
  const char *buffer;     // content
} Lexer;

/* LEXER */
/* standard init function; returns a lexer object */
extern Lexer *lexInit(char *source);

/* advance current char and increase count */
static void lexAdv(Lexer *lex);

char *collectNumber(Lexer *lex);
char *collectString(Lexer *lex);
char *collectKeyword(Lexer *lex);

/* This function recieves a source char * and loops through each
char until it reaches \n;\0;\0 */
void lexer(Lexer *lex);

#endif // !LEXER_H
