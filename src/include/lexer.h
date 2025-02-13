#ifndef LEXER_H
#define LEXER_H

#include "token.h"
#include <stddef.h>

/* LEXER */

typedef struct {
  char current;       // current char
  int i;              // counter
  size_t bufferSize;  // sizeof(const char *buffer)
  const char *buffer; // content
} Lexer;

/* standard init for collector */
extern Lexer *lexInit(char *source);

/* advances lexer's current char */
static void lexAdv(Lexer *lex);

/* advances lexer's current char x times */
static void lexCountedAdv(Lexer *lex, int times);
/* actual lexer function; the biggest surely */
void lexer(Lexer *lex);


/* 
 * COLLECTOR 
 * NOTE:
 *    All of these collector functions work the same way:
 *    - Loop
 *      - collect current char if it's "good type"
 *      - if not good type; gtfoh;
 */


typedef struct {
  char *collectorBuffer;
  size_t colLegnth;
  size_t colBuffSize;
} Collector;

/* standard init for collector */
Collector *collectorInit();

/* these collect chars until current isn't what they're supposed to collect */
char *collectNumber(Lexer *lex, Collector *col);
char *collectBlock(Lexer *lex, Collector *col, char closingBlock);
char *collectKeyword(Lexer *lex, Collector *col);
char *collectSinglechar(Lexer *lex);
char *collectDoublechar(Lexer *lex);

/* free collector's buffer */
void freeCollector(Collector *col);

#endif // !LEXER_H
