#ifndef AST_H
#define AST_H

/* AST */

typedef enum AST_Types {
  PROGRAM,
  NUMLITERAL,
  IDENTIFIER,
  BINARYEXPR,
} AST_Types;

typedef struct Statement { 
  AST_Types kind;
} Statement;

typedef struct Program {
  AST_Types kind;
  Statement **body;
} Program;

#endif // !AST_H
