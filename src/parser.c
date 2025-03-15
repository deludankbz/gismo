#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include "include/parser.h"
#include "include/ast.h"


/* PARSER
    NOTE:
    Floats should be handled by the parser;
    e.g:
        0.5 -> | 0 | . | 5 | -> parse() -> Node (float: 0.5)
        .8 ->  | 0 | . | 8 | -> parse() -> Node (float: 0.8)
                 ^ parser should add 0 in-front of '.'
*/


/*=========*/
/* METHODS */
/*=========*/


AST_Program impl_Program(parser_t* self) {}

AST_NumericLiteral impl_NumericLiteral(parser_t* self) {}

void destroyParser(parser_t* self) { free(self); }

void advToken (parser_t* self) { self->current_t = self->current_t->next; }

void parse(parser_t* self) { }


/*==============*/
/* PARSER CLASS */
/*==============*/


parser_t *newParser(Lexer *lex) {
  parser_t *newParser = malloc(sizeof(parser_t));
  if (!newParser) { return NULL; }

  AST_Program *parserObj = malloc(sizeof(AST_Program));
  if (!parserObj) { return NULL; }

  newParser->tokens = lex->q;
  newParser->current_t = lex->q->head;

  newParser->parserObj = parserObj;

  /* method reg */
  newParser->Program = impl_Program;
  newParser->NumericLiteral = impl_NumericLiteral;
  newParser->destroy = destroyParser;
  newParser->parse = parse;
  return newParser;
}
