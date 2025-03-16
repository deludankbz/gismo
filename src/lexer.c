#include <ctype.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "include/datatypes.h"
#include "include/errors.h"
#include "include/lexer.h"
#include "include/token.h"


/* LEXER
    TODO:
    Add more doublechars.
    Handle buffer overflow in most of collector functions.

    FIXED:
    Strings like '"' will cause the lexer to crash.

 */

Lexer *lexInit(char *source) {
  Lexer *lex = malloc(sizeof(Lexer));
  if (!lex) { free(lex); raiseError(E_MALLOC, "malloc() for Lexer interface went wrong!"); }

  Collector *col = collectorInit();
  if (!col) { free(col); raiseError(E_MALLOC, "collectorInit() went wrong!");}
  lex->col = col;

  Queue *newQ = createQueue(); bool status = false; int tokenCounter = 1;
  if (!newQ) { free(newQ); raiseError(E_MALLOC, "createQueue() went wrong!");}
  lex->q = newQ;

  lex->buffer = source;
  lex->bufferSize = strlen(lex->buffer) + 1;
  lex->i = 0;
  lex->current = source[lex->i];

  return lex;
}

void lexAdv(Lexer *lex) {
  lex->i++;
  lex->current = lex->buffer[lex->i];
}

void lexCountedAdv(Lexer *lex, int times) {
  if (times > 0) {
    lex->i += times;
    lex->current = lex->buffer[lex->i];
  } else (lexAdv(lex));
}

void destroyLexer(Lexer *lex) {
  destroyQueue(lex->q);
  free(lex->col->collectorBuffer); free(lex->col);
  free(lex);
}


/* COLLECTOR
    TODO:
    handle buffer overflow for collector functions.

    NOTE:
    functions with more than one raiseError will cause memory leaks since
    they'll quit when called and whatever is below them wont get executed
    afterwards
*/


Collector *collectorInit() {
  /* collector has a buffer with max size of 128 chars */
  Collector *col = malloc(sizeof(Collector));
  /* TODO: make this mofo a global mofo */
  col->colBuffSize = 128;
  col->colLegnth = 0;

  col->collectorBuffer = calloc(col->colBuffSize, sizeof(char));

  if (!col->collectorBuffer) { free(col->collectorBuffer); raiseError(E_MALLOC, "failed to allocate memory for collectorBuffer."); }
  if (!col) { free(col); raiseError(E_MALLOC, "malloc() for Collector interface went wrong!"); }

  return col;
}

void freeCollector(Collector *col) {
  for (int i = 0; i < col->colBuffSize ;i++) { col->collectorBuffer[i] = '\0'; }
}

char *collectBlock(Lexer *lex, Collector *col, char closingBlock) {
  /* FIX: -  WILL CAUSE BUFFFER OVERFLOW!!! */
  lexAdv(lex);
  for (int i = 0; lex->current != closingBlock; i++) {
    if (lex->current != '\0') {
      col->collectorBuffer[i] = lex->current;
      lexAdv(lex);
    } else {
      return "\0";
    }
  }
  lexAdv(lex);
  return col->collectorBuffer;
}

char *collectSinglechar(Lexer *lex) {
  char pos_singlechar[2] = { lex->current,  '\0' };

  switch (lex->current) {

    /* Single-character symbols */
    case '(':  return "(";;
    case ')':  return ")";
    case '{':  return "{";
    case '}':  return "}";
    case '[':  return "[";
    case ']':  return "]";
    case ';':  return ";";
    case ',':  return ",";
    case '.':  return ".";

    /* Quotes */
    case '"':  return "\"";
    case '\'':  return "'";

    /* Operators */
    case '+':  return "+";
    case '-':  return "-";
    case '*':  return "*";
    case '/':  return "/";
    case '%':  return "%";
    case '&':  return "&";
    case '|':  return "|";
    case '^':  return "^";
    case '!':  return "!";
    case '=':  return "=";
    case '<':  return "<";
    case '>':  return ">";

    /* for unexpected characters */
    default:  return NULL;
  }
}

/* doublechar's operators */
/* TODO: works but, at what cost? please revisit this in the future. */
char *collectDoublechar(Lexer *lex) {
  char pos_doublechar[3] = { lex->current, lex->buffer[lex->i + 1], '\0' };
  
  if (strcmp(pos_doublechar, "==") == 0) { lexCountedAdv(lex, 2); return strdup(pos_doublechar); }
  else if (strcmp(pos_doublechar, "!=") == 0) { lexCountedAdv(lex, 2); return strdup(pos_doublechar); }
  /* repeat boiler plate ... */

  return NULL;
}

char *collectKeyword(Lexer *lex, Collector *col) {
  for (int i = 0; isalpha(lex->current); i++) {
    if (i > col->colBuffSize) {
      /* FIX: handle buffer overflow */
      printf("keyword too large!\n");
      return col->collectorBuffer;
    } else {
      col->collectorBuffer[i] = lex->current;
      lexAdv(lex);
    }
  }
  return col->collectorBuffer;
}

char *collectNumber(Lexer *lex, Collector *col) {
  /* FIX: -  WILL CAUSE BUFFFER OVERFLOW!!! */
  for (int i = 0; isdigit(lex->current); i++) {
    col->collectorBuffer[i] = lex->current;
    lexAdv(lex);
  }
  return col->collectorBuffer;
}


/* LEXER FUNCTION */


void lexer(Lexer *lex) {
  bool status = false;
  int tokenCounter = 0;

  while (!(lex->i >= lex->bufferSize + 1)) {
    TokenType cmpDoublechar = checkDoublechar(lex->current, lex->buffer[lex->i + 1]);
    TokenType cmpSinglechar = checkSymbol(lex->current);

    /* check for SPACE or newLine */
    if (lex->current == 32 || lex->current == 10) {
      lexAdv(lex);

    } else if (isdigit(lex->current)) { /* collects numbers */
      char *tempNumber = collectNumber(lex, lex->col);
      Token *digitToken = generateToken(strdup(tempNumber), T_NUMBER);
      addNode(lex->q, tokenCounter, digitToken);
      
      /*printf("digit!\n");*/
      freeCollector(lex->col);
      tokenCounter++;

    } else if (isalpha(lex->current)) { /* collects keywords */
      char *tempAlpha = collectKeyword(lex, lex->col);
      Token *alphaToken = generateToken(strdup(tempAlpha), T_IDENTIFIER);
      addNode(lex->q, tokenCounter, alphaToken);

      freeCollector(lex->col);
      tokenCounter++;

    } else if (lex->current == '"' || lex->current == '\'') {
      char *tempBlock = collectBlock(lex, lex->col, lex->current);
      Token *blockToken = generateToken(strdup(tempBlock), T_STRING);
      addNode(lex->q, tokenCounter, blockToken);
      
      freeCollector(lex->col);
      tokenCounter++;

    } else if (cmpDoublechar != T_ARBITRARY) { /* check if current is start of block char */
      char *tempDoublechar = collectDoublechar(lex);
      Token *doublecharToken = generateToken(strdup(tempDoublechar), cmpDoublechar);
      addNode(lex->q, tokenCounter, doublecharToken);

      if (tempDoublechar == NULL) {continue;}

    } else if (cmpSinglechar != T_ARBITRARY){
      /* FIX NOTE: STOP WITH THESE NASTY CASTS BRO. not. cool. dude. */
      char *tempSymbol = collectSinglechar(lex);
      Token *symbolToken = generateToken(strdup(tempSymbol), cmpSinglechar);
      addNode(lex->q, tokenCounter, symbolToken);

      lexAdv(lex);
      tokenCounter++;
    } else if (lex->current == '\0' && lex->buffer[lex->i + 1] == '\0') { /* ends program if EOF detected */
      /*Token *eof = generateToken("\0", T_EOF, sizeof(char));*/
      /*addNode(lex->q, tokenCounter, eof);*/

      printQueue(lex->q, &status);
      printf("token iterations :: %d\n", tokenCounter);
      lex->q->lenght = tokenCounter;
      break;
      /*destroyQueue(lex->q);*/
      /**/
      /*free(lex->col->collectorBuffer); free(lex->col);*/
      /*return lex;*/
    } else {
      printf("'%c': unknown!\n", lex->current);
      lexAdv(lex);
      freeCollector(lex->col);
    }
  }
  
  /*free(lex->col->collectorBuffer);*/
  /*free(lex->col);*/
  /*return lex;*/
}
