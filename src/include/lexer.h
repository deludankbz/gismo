#ifndef LEXER_H
#define LEXER_H

#include <stddef.h>
#include "token.h"

/* Lexer and needle because i thought of a needle pointing to char */
// consider exchanging star of nCont to needle if goes wrong
typedef struct {
  char current;           // current char
  int i;                  // counter
  size_t bufferSize;      // sizeof(const char *buffer) 
  const char *buffer;     // content
} Lexer;

typedef struct {
  size_t buffsize;
  size_t lenght;
  char * buffer;
} Clipboard;

/* LEXER */
/* This function recieves a source char * and loops through each
char until it reaches '\0' */
extern Lexer *lexInit(char *source);

static void lexAdv(Lexer *lex);
/*static void *lexSkip(Lexer *lex);*/

void *lexer(Lexer *lex);

/* CLIPBOARD */
Clipboard *clipInit(int iSize);

void freeClip(Clipboard *clip); 

void clearBuffer(Clipboard *clip);

void saveToClip(Clipboard *clip, char c);

#endif // !LEXER_H
