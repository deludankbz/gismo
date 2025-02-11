#include <ctype.h>
#include <regex.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "include/errors.h"
#include "include/lexer.h"

/* FIX:
 *    handle buffer overflow for collector functions.
 */

/* LEXER DECLARATIONS
 *
 * NOTE: for collect functions:
 *    sizeof() Vs strlen() - sizeof is a "compile-time function", running
 *    it multiple times (likely in a loop), could and will cause performance
 * issues as well safety issues like buffer overflow attacks.
 *
 * DONE: refactor stuff like buffer col_maxNumSize ... into their own collector
 * struct.
 *
 */

void lexAdv(Lexer *lex) {
  lex->i++;
  lex->current = lex->buffer[lex->i];
}

Lexer *lexInit(char *source) {
  /* lex needs to free */
  Lexer *lex = malloc(sizeof(Lexer));
  if (!lex) {
    raiseError(lex, E_MALLOC, "failed to allocate memory for Lexer.");
  }
  lex->buffer = source;
  lex->bufferSize = strlen(lex->buffer) + 1; // sizeof buffer plus '\0'
  lex->i = 0;
  lex->current = source[lex->i];

  return lex;
}

/* COLLECTOR
 * DILEMA:
 *    make a giant buffer and loop through it manually vs using free and malloc?
 *
 *    I think making a giant buffer would be better.
 *    Imagine that the buffer is the token were currently in; if we had like 10
 *    tokens per line, And 200 lines, that adds up to the overhead. imagine
 *    calling free + malloc 2000 times.
 */

Collector *collectorInit() {
  /* collector has a buffer with max size of 128 chars */
  Collector *col = malloc(sizeof(Collector));
  col->colBuffSize = 128;
  col->colLegnth = 0;

  col->collectorBuffer = calloc(col->colBuffSize, sizeof(char));
  if (!col->collectorBuffer) {
    raiseError(col->collectorBuffer, E_MALLOC,
               "failed to allocate memory for collectorBuffer.");
  }
  if (!col) {
    raiseError(col, E_MALLOC, "failed to allocate memory for Collector.");
  }

  return col;
}

void *freeCollector(Collector *col) {
  memset(col->collectorBuffer, '\0', col->colBuffSize);
  return NULL;
}

char *collectString(Lexer *lex, Collector *col, char c) {
  /* FIX: -  WILL CAUSE BUFFFER OVERFLOW!!! */
  lexAdv(lex);
  for (int i = 0; lex->current != c; i++) {
    col->collectorBuffer[i] = lex->current;
    lexAdv(lex);
  }
  lexAdv(lex);
  return strdup(col->collectorBuffer);
}

char *collectKeyword(Lexer *lex, Collector *col) {
  for (int i = 0; isalpha(lex->current); i++) {
    if (i > col->colBuffSize) {
      /* handle buffer overflow */
      printf("keyword too large!\n");
      return strdup(col->collectorBuffer);
    } else {
      col->collectorBuffer[i] = lex->current;
      lexAdv(lex);
    }
  }
  return strdup(col->collectorBuffer);
}

char *collectNumber(Lexer *lex, Collector *col) {
  /* FIX: -  WILL CAUSE BUFFFER OVERFLOW!!! */
  for (int i = 0; isdigit(lex->current); i++) {
    col->collectorBuffer[i] = lex->current;
    lexAdv(lex);
  }
  return strdup(col->collectorBuffer);
}

/* LEXER FUNCTION
 */
void lexer(Lexer *lex) {
  /* COLLECTOR INIT */
  Collector *col = collectorInit();
  if (!col) {
    raiseError(col, E_MALLOC, "malloc for collector went wrong!\n");
  }

  printf("\n----\n");
  while (!(lex->i >= lex->bufferSize + 1)) {
    /* check for SPACE or newLine */
    if (lex->current == 32 || lex->current == 10) {
      lexAdv(lex);
    }

    /* collects numbers */
    else if (isdigit(lex->current)) {
      char *tempNumber = collectNumber(lex, col);
      printf("%s is number!\n", tempNumber);
      freeCollector(col);
      free(tempNumber);
    }

    /* collects keywords */
    else if (isalpha(lex->current)) {
      char *tempAlpha = collectKeyword(lex, col);
      printf("%s is alpha!\n", tempAlpha);
      freeCollector(col);
      free(tempAlpha);
    }

    /* NOTE collectString can be useful for collecting stuff inside blocks */
    else if (lex->current == '"') {
      char *tempKeyword = collectString(lex, col, '"');
      printf("%c is quotes!\n", '"');
      printf("%s is string!\n", tempKeyword);
      printf("%c is quotes!\n", '"');
      freeCollector(col);
      free(tempKeyword);
    }

    /* check for blocks of text inside of '"([{*/
    else if (lex->current == '(') {
      char *tempParents = collectString(lex, col, ')');
      printf("%c is paren.!\n", '(');
      printf("%s is inside parens!\n", tempParents);
      printf("%c is paren.!\n", ')');
      freeCollector(col);
      free(tempParents);
    }

    /* ends program if EOF detected */
    else if (lex->current == '\0' && lex->buffer[lex->i + 1] == '\0') {
      printf("reached EOF!\n");
      return;
      freeCollector(col);
    } else {
      printf("%c is symbol!\n", lex->current);
      lexAdv(lex);
      freeCollector(col);
    }
  }
  free(col->collectorBuffer);
  free(col);
}
