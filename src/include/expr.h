#ifndef EXPR_H
#define EXPR_H


/*
  EXPRESSIONS:
*/


typedef struct Expr {
  void (*expr)(void* self);
} Expr;


typedef struct NumberExpr {
  Expr expr;
  double value;
} NumberExpr;

NumberExpr *newNumExpr(double value);

typedef struct StringExpr {
  Expr expr;
  char *value;
} StringExpr;

StringExpr *newStringExpr(char *value);

typedef struct SymbolExpr {
  Expr expr;
  /* could be a single char tho */
  char *value; 
} SymbolExpr;

SymbolExpr *newSymbolExpr(char *value);


/*
  BINARY EXPRESSIONS:
*/

typedef struct BinaryExpr {
  Expr left;
  char *ops;
  Expr right;
} BinaryExpr;

BinaryExpr* newBinaryExpr(Expr* left, const char* operation, Expr* right);

typedef struct AssignmentExpr {
  Expr sign;
  Expr value;
} AssignmentExpr;

AssignmentExpr* newAssignmentExpr(Expr* sign, Expr* value);

#endif // !EXPR_H
