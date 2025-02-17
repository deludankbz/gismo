#ifndef TOKEN_H
#define TOKEN_H

#include <stddef.h>
/* TODO add more enums */

typedef enum {
  /* Single-character symbols */
  T_LPAREN,    // (
  T_RPAREN,    // )
  T_LBRACE,    // {
  T_RBRACE,    // }
  T_LBRACKET,  // [
  T_RBRACKET,  // ]
  T_SEMICOLON, // ;
  T_COMMA,     // ,
  T_DOT,       // .
  
  /* Quotes */
  T_DB_QUOTES, // "
  T_QUOTE,     // ' 


  /* Operators */
  T_PLUS,      // +
  T_MINUS,     // -
  T_STAR,      // *
  T_SLASH,     // /
  T_PERCENT,   // %
  T_AMP,       // &
  T_PIPE,      // |
  T_CARET,     // ^
  T_DIFF,      // !
  T_EQUAL,     // =
  T_LESS,      // <
  T_GREATER,   // >

  /* Two-character operators */
  T_ISEQUAL,    // ==
  T_ISDIFF,     // !=
  T_LESS_EQUAL,     // <=
  T_GREATER_EQUAL,  // >=
  T_PLUS_EQUAL,     // +=
  T_MINUS_EQUAL,    // -=
  T_STAR_EQUAL,     // *=
  T_SLASH_EQUAL,    // /=
  T_PERCENT_EQUAL,  // %=

  /* Logical operators */
  T_AND,    // &&
  T_OR,     // ||

  /* Ternary operator */
  T_QUESTION,    // ?
  T_COLON,       // :

  /* Keywords */
  T_VAR,    // var
  T_LET,    // let
  T_IF,     // if
  T_ELSE,   // else
  T_WHILE,  // while
  T_FOR,    // for
  T_RETURN, // return
  T_FUNC,   // func
  T_TRUE,   // true
  T_FALSE,  // false
  T_NIL,    // nil
  T_PRINT,  // print
  T_CONST,  // const

  /* Identifiers and literals */
  T_IDENTIFIER,
  T_NUMBER,
  T_STRING,

  /* Misc */
  T_EOF, T_ARBITRARY,

  /* testing */
  T_SPACE
} TokenType;

typedef struct Token {
  TokenType type;
  char *value;
} Token;

/*char *checkBlocks(char c);*/

TokenType checkSymbol(char c);
TokenType checkDoublechar(char c, char nextC);
TokenType checkBlock(char c);

Token *generateToken(char *source, TokenType tType);
/*const char *makeToken(char *source, TokenType tType);*/

static char *concat(char *source, ...);

#endif // !TOKEN_H
