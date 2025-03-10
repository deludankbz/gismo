#include "include/expr.h"
#include "include/errors.h"
#include <stdlib.h>

NumberExpr *newNumExpr(double value) {
  NumberExpr *expr = malloc(sizeof(NumberExpr));
  if (!expr) { free(expr); raiseError(E_MALLOC, "failed to malloc -> NumberExpr");}
  /*expr->expr = func here*/
  expr->value = value;

  return expr;
}


StringExpr *newStringExpr(char *value);
SymbolExpr *newSymbolExpr(char *value);
BinaryExpr* newBinaryExpr(Expr* left, const char* operation, Expr* right);
AssignmentExpr* newAssignmentExpr(Expr* sign, Expr* value);
