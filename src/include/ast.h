#ifndef AST_H
#define AST_H

/* AST */

typedef enum NodeType {
  PROGRAM,
  NUMLITERAL,
  IDENTIFIER,
  BINARYEXPR,

} NodeType;

typedef struct Statement { NodeType kind; } Statement;

typedef struct Program {
  NodeType kind;
  Statement **body;
} Program;

typedef struct Expr { NodeType kind; } Expr;

typedef struct BinaryExpr {
  Expr left;
  char *opr;
  Expr right;
} BinaryExpr;

typedef struct Identifier {
  NodeType kind;
  char *content;
} Identifier;

typedef struct NumericLiteral {
  NodeType kind;
  char *value;
} NumericLiteral;


static void initAST();


#endif // !AST_H
