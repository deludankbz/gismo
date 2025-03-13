#ifndef LEXER_H
#define LEXER_H

#include "datatypes.h"
#include "token.h"
#include <stddef.h>


/* COLLECTOR STRUCT */


typedef struct {
  char *collectorBuffer;
  size_t colLegnth;
  size_t colBuffSize;
} Collector;


/* LEXER STRUCT */


typedef struct {
  char current;       /* current char */
  int i;              /* counter */
  size_t bufferSize;  /* sizeof(const char *buffer) */
  const char *buffer; /* buffer content */
  
  Collector *col;
  Queue *q;
} Lexer;


/* LEXER */


/* standard init for collector */
extern Lexer *lexInit(char *source);

/* advances lexer's current char */
static void lexAdv(Lexer *lex);

/* advances lexer's current char x times */
static void lexCountedAdv(Lexer *lex, int times);

/* actual lexer function; the biggest surely */
void lexer(Lexer *lex);

void destroyLexer(Lexer *lex);


/* COLLECTOR */


/* standard init for collector */
Collector *collectorInit();

char *collectNumber(Lexer *lex, Collector *col);
char *collectBlock(Lexer *lex, Collector *col, char closingBlock);
char *collectKeyword(Lexer *lex, Collector *col);
char *collectSinglechar(Lexer *lex);
char *collectDoublechar(Lexer *lex);

/* free collector's buffer */
void freeCollector(Collector *col);

#endif // !LEXER_H
