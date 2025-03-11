#ifndef AST_H
#define AST_H

#include "token.h"
#include <stdint.h>

/* AST */

typedef enum NodeType {
  PROGRAM,
  LITERAL,
  IDENTIFIER,
  BIN_EXPR,

} NodeType;


#endif // !AST_H
