#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include "include/token.h"
#include "include/errors.h"


/* TOKEN */


char *concat(char *source, ...) {
  va_list args; va_start(args, source);

  int lenght = vsnprintf(NULL, 0, source, args);
  va_end(args);

  char *buffer = malloc(lenght + 1);
  if (!buffer) { return NULL; }

  va_start(args, source);
  vsnprintf(buffer, lenght + 1, source, args);
  va_end(args);

  return buffer;
}

/* check if current char is " ' ( [ { */
TokenType checkBlock(char c) {
  switch (c) {
    /* inline blocks */
    case '\'': return T_QUOTE;
    case '"': return T_DB_QUOTES;

    /* stfu clangd */
    default: return T_ARBITRARY;
  }
}

/* check for symbols */
/* WHAT THE HEEEEEEEEEEEEEE- */
TokenType checkDoublechar(char c, char nextC) {
  switch (c) {

    /* Logical operators */
    case '&': if (nextC == '&') return T_AND; 
    case '|': if (nextC == '|') return T_OR; 

    /* Condtional operators */
    case '!': if (nextC == '=') return T_ISEQUAL; 
    case '=': if (nextC == '=') return T_ISEQUAL; 
    case '<': if (nextC == '=') return T_LESS_EQUAL; 
    case '>': if (nextC == '=') return T_GREATER_EQUAL; 

    /* Math macros */
    case '+': if (nextC == '=') return T_PLUS_EQUAL; 
    case '-': if (nextC == '=') return T_MINUS_EQUAL; 
    case '*': if (nextC == '=') return T_STAR_EQUAL; 
    case '/': if (nextC == '=') return T_SLASH_EQUAL; 
    case '%': if (nextC == '=') return T_PERCENT_EQUAL; 
    
    /* for unexpected characters */
    default: return T_ARBITRARY;
  }
}

TokenType checkSymbol(char c) {
  switch (c) {

    /* Single-character symbols */
    case '(': return T_LPAREN;
    case ')': return T_RPAREN;
    case '{': return T_LBRACE;
    case '}': return T_RBRACE;
    case '[': return T_LBRACKET;
    case ']': return T_RBRACKET;
    case ';': return T_SEMICOLON;
    case ',': return T_COMMA;
    case '.': return T_DOT;

    /* Quotes */
    case '"': return T_DB_QUOTES;
    case '\'': return T_QUOTE;

    /* Operators */
    case '+': return T_PLUS;
    case '-': return T_MINUS;
    case '*': return T_STAR;
    case '/': return T_SLASH;
    case '%': return T_PERCENT;
    case '&': return T_AMP;
    case '|': return T_PIPE;
    case '^': return T_CARET;
    case '!': return T_DIFF;
    case '=': return T_EQUAL;
    case '<': return T_LESS;
    case '>': return T_GREATER;

    /* for unexpected characters */
    default: return T_ARBITRARY;
  }
}

Token *generateToken(char *source, TokenType tType, size_t maxSize) {
  Token *tempToken = malloc(sizeof(Token));
  /* TODO FIX for some unknown reason this causes memory leaks */
  tempToken->value = calloc(maxSize, sizeof(char));
  tempToken->type = tType;

  if (!tempToken->value) { free(tempToken->value); raiseError(E_MALLOC, "tempToken->value malloc went wrong!"); }
  if (!tempToken) { free(tempToken); raiseError(E_MALLOC, "tempToken malloc went wrong!"); }
  tempToken->value = source;

  return tempToken;
}

const char *makeToken(char *source, TokenType tType) {
  return concat("token[id: %i; value: \"%s\"]\n", tType, source);
}
