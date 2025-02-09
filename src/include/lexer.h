#ifndef LEXER_H
#define LEXER_H

#include <stddef.h>
#include "token.h"


/* ===== */
/* LEXER */

typedef struct {
  char current;           // current char
  int i;                  // counter
  size_t bufferSize;      // sizeof(const char *buffer) 
  const char *buffer;     // content
} Lexer;

/* standard init for collector. */
extern Lexer *lexInit(char *source);

/* advances lexer's current char. */
static void lexAdv(Lexer *lex);

/* actual lexer function; the biggest surely. */
void lexer(Lexer *lex);


/* ========= */
/* COLLECTOR */

typedef struct {
  char* collectorBuffer;
  size_t colLegnth;
  size_t colBuffSize;
} Collector;

/* standard init for collector */
Collector *collectorInit();

/* these collect chars until current isn't what they're supposed to collect. */
char *collectNumber(Lexer *lex, Collector *col);
char *collectString(Lexer *lex, Collector *col, char c);
char *collectKeyword(Lexer *lex, Collector *col);

void *freeCollector (Collector *col);

#endif // !LEXER_H
