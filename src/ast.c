#ifndef AST_H
#define AST_H


/* AST
  NOTE:
    There should have been two types of nodes:
    Binary ones with two children nodes or 
    Multinode with n children nodes
*/


/* could this enum be used as a precedence order list? */
typedef enum {
  BINARY,
  NUMBER,
  IDENTIFIER,
  GROUPING,
  PREFIX,
} NodeType;


typedef struct AST_Node {
  NodeType type; 
} AST_Node ;

#endif /* AST_H */
