#include <ctype.h>
#include <regex.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "include/datatypes.h"
#include "include/errors.h"
#include "include/lexer.h"
#include "include/token.h"


/* LEXER
 * FIX:
 *    Add support for float numbers in Collector. 
 */


Lexer *lexInit(char *source) {
  /* lex needs to free */
  Lexer *lex = malloc(sizeof(Lexer));
  if (!lex) { free(lex); raiseError(E_MALLOC, "malloc() for Lexer interface went wrong!"); }
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


/* 
 * COLLECTOR
 *
 * FIX:
 *    handle buffer overflow for collector functions.
 */


Collector *collectorInit() {
  /* collector has a buffer with max size of 128 chars */
  Collector *col = malloc(sizeof(Collector));
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
    col->collectorBuffer[i] = lex->current;
    lexAdv(lex);
  }
  lexAdv(lex);
  return strdup(col->collectorBuffer);
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
/* TODO: works but, at what cost? please revist this in the future. */
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
      /* handle buffer overflow */
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
  Collector *col = collectorInit();
  if (!col) { free(col); raiseError(E_MALLOC, "collectorInit() went wrong!");}
  Queue *newQ = createQueue(); bool status = false; int tokenCounter = 1;
  if (!newQ) { free(newQ); raiseError(E_MALLOC, "createQueue() went wrong!");}

  printf("\n----\n");

  while (!(lex->i >= lex->bufferSize + 1)) {
    TokenType cmpDoublechar = checkDoublechar(lex->current, lex->buffer[lex->i + 1]);
    TokenType cmpSinglechar = checkSymbol(lex->current);

    /* check for SPACE or newLine */
    if (lex->current == 32 || lex->current == 10) {
      lexAdv(lex);

    } else if (isdigit(lex->current)) { /* collects numbers */
      char *tempNumber = collectNumber(lex, col);
      Token *digitToken = generateToken(strdup(tempNumber), T_NUMBER, (int)strlen(tempNumber) + 1);
      addNode(newQ, tokenCounter, digitToken);
      
      /*printf("digit!\n");*/
      freeCollector(col);
      tokenCounter++;

    } else if (isalpha(lex->current)) { /* collects keywords */
      char *tempAlpha = collectKeyword(lex, col);
      Token *alphaToken = generateToken(strdup(tempAlpha), T_IDENTIFIER, (int)strlen(tempAlpha) + 1);
      addNode(newQ, tokenCounter, alphaToken);

      /*printf("alpha!\n");*/
      freeCollector(col);
      tokenCounter++;

    } else if (lex->current == '"' || lex->current == '\'') {
      char *tempBlock = collectBlock(lex, col, lex->current);
      Token *blockToken = generateToken(strdup(tempBlock), T_STRING, (int)strlen(tempBlock) + 1);
      addNode(newQ, tokenCounter, blockToken);
      
      freeCollector(col);
      tokenCounter++;

    } else if (cmpDoublechar != T_ARBITRARY) { /* check if current is start of block char */
      char *tempDoublechar = collectDoublechar(lex);
      Token *doublecharToken = generateToken(strdup(tempDoublechar), cmpDoublechar, (int)strlen(tempDoublechar) + 1);
      addNode(newQ, tokenCounter, doublecharToken);

      if (tempDoublechar == NULL) {continue;}

      /*printf("%s doublechar!\n", tempDoublechar);*/
    } else if (cmpSinglechar != T_ARBITRARY){
      /* FIX NOTE: STOP WITH THESE NASTY CASTS BRO. not. cool. dude. */
      char *tempSymbol = collectSinglechar(lex);
      Token *symbolToken = generateToken(strdup(tempSymbol), cmpSinglechar, (int)strlen(tempSymbol) + 1);
      addNode(newQ, tokenCounter, symbolToken);

      lexAdv(lex);
      tokenCounter++;
    } else if (lex->current == '\0' && lex->buffer[lex->i + 1] == '\0') { /* ends program if EOF detected */
      /*Token *eof = generateToken("\0", T_EOF, sizeof(char));*/
      /*addNode(newQ, tokenCounter, eof);*/

      printQueue(newQ, &status);
      destroyQueue(newQ);

      free(col->collectorBuffer); free(col);
      break;

    } else {
      printf("'%c': unknown!\n", lex->current);
      lexAdv(lex);
      freeCollector(col);
    }
  }
  
  /*free(col->collectorBuffer);*/
  /*free(col);*/
}
