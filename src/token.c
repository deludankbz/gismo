#include <stdio.h>
#include <stdarg.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include "include/token.h"

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

/* WHAT THE HEEEEEEEEEEEEEE- */
TokenType checkSymbols(char c, char nextC) {
  switch (c) {
    case '(': return T_LPAREN;
    case ')': return T_RPAREN;
    case '{': return T_LBRACE;
    case '}': return T_RBRACE;
    case '[': return T_LBRACKET;
    case ']': return T_RBRACKET;
    case ';': return T_SEMICOLON;
    case ',': return T_COMMA;
    case '.': return T_DOT;
    case '+': return (nextC == '=') ? T_PLUS_EQUAL : T_PLUS;
    case '-': return (nextC == '=') ? T_MINUS_EQUAL : T_MINUS;
    case '*': return (nextC == '=') ? T_STAR_EQUAL : T_STAR;
    case '/': return (nextC == '=') ? T_SLASH_EQUAL : T_SLASH;
    case '%': return (nextC == '=') ? T_PERCENT_EQUAL : T_PERCENT;
    case '&': return (nextC == '&') ? T_AND : T_AMP;
    case '|': return (nextC == '|') ? T_OR : T_PIPE;
    case '^': return T_CARET;
    case '!': return (nextC == '=') ? T_ISDIFF : T_DIFF;
    case '=': return (nextC == '=') ? T_ISEQUAL : T_EQUAL;
    case '<': return (nextC == '=') ? T_LESS_EQUAL : T_LESS;
    case '>': return (nextC == '=') ? T_GREATER_EQUAL : T_GREATER;
    case '?': return T_QUESTION;
    case ':': return T_COLON;
    
    // for unexpected characters
    default: return T_ARBITRARY;
  }
}

Token *generateToken(char *source, TokenType tType) {
  Token *tempToken = malloc(sizeof(Token));

  return tempToken;
}

const char *makeToken(char *source, TokenType tType) {
  return concat("token[id: %i; value: \"%s\"]\n", tType, source);
}
