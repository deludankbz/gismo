#include <ctype.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#include "include/lexer.h"
#include "include/token.h"
#include "include/errors.h"

/* TODO Tokenize clip->buffer (more or less) */

void lexAdv(Lexer *lex) {
  lex->i++;
  lex->current = lex->buffer[lex->i];
}

Lexer *lexInit(char *source) {
  /* lex needs to free */
  Lexer *lex = malloc(sizeof(Lexer));
  if (!lex) {raiseError(lex, E_MALLOC, "failed to allocate memory for lexer.");}
  lex->buffer = source;
  lex->bufferSize = strlen(lex->buffer) + 1; // sizeof buffer plus '\0'
  lex->i = 0;
  lex->current = source[lex->i];
  return lex;
}

char *collectString(Lexer *lex, char c) {
  /* FIX WILL CAUSE BUFFFER OVERFLOW!!! */
  char *buffer = calloc(256, sizeof(char));
  buffer[strlen(buffer)] = '\0';

  lexAdv(lex);
  for (int i = 0; lex->current != c; i++) { buffer[i] = lex->current; lexAdv(lex); }
  lexAdv(lex);
  return buffer;
}

char *collectKeyword(Lexer *lex) {
  /* FIX WILL CAUSE BUFFFER OVERFLOW!!! */
  char *buffer = calloc(64, sizeof(char));
  buffer[strlen(buffer)] = '\0';

  for (int i = 0; isalpha(lex->current); i++) { buffer[i] = lex->current; lexAdv(lex); }
  return buffer;
}

char *collectNumber(Lexer *lex) {
  /* FIX WILL CAUSE BUFFFER OVERFLOW!!! */
  char *buffer = calloc(16, sizeof(char));
  buffer[strlen(buffer)] = '\0';

  for (int i = 0; isdigit(lex->current); i++) { buffer[i] = lex->current; lexAdv(lex); }
  return buffer;
}

void lexer(Lexer *lex) {
  printf("\n----\n");
  while (!(lex->i >= lex->bufferSize + 1)) {
    /* check for SPACE or newLine */
    if (lex->current == 32 || lex->current == 10) { lexAdv(lex); }

    /* collects numbers */
    else if (isdigit(lex->current)) {
      char *temp = collectNumber(lex);
      printf("%s is number!\n", temp);
      free(temp);
    } 

    /* collects keywords */
    else if (isalpha(lex->current)) {
      char *tempKeyword = collectKeyword(lex);
      printf("%s is alpha!\n", tempKeyword);
      free(tempKeyword);
    }

    /* NOTE collectString can be useful for collecting stuff inside blocks */
    else if (lex->current == '"') {
      char *tempStr = collectString(lex, '"');
      printf("%s is string!\n", tempStr);
      free(tempStr);
    }

    /* check for blocks of text inside of '"([{*/
    else if (lex->current == '(') {
      printf("%c is paren.!\n", '(');
      char *tempStr = collectString(lex, ')');
      printf("%s is inside parens.!\n", tempStr);
      printf("%c is paren.!\n", ')');
      free(tempStr);
    }

    /* ends program if EOF detected */
    else if (lex->current == '\0' && lex->buffer[lex->i + 1] == '\0') {
      printf("reached EOF!\n"); return;
    } 
    else {
      printf("%c is symbol!\n", lex->current);
      lexAdv(lex);
    }
  }
}
