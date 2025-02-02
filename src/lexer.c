#include <ctype.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "include/lexer.h"
#include "include/token.h"
#include "include/errors.h"

/* TODO: Tokenize clip->buffer (more or less)
 */

void *lexAdv(Lexer *lex) {
  lex->i++;
  lex->current = lex->buffer[lex->i];
}

Lexer *lexInit(char *source) {
  /* lex needs to free */
  Lexer *lex = malloc(sizeof(Lexer));
  if (!lex) {raiseError(lex, E_MALLOC, "failed to allocate memory for lexer.");}
  lex->buffer = source;
  lex->bufferSize = strlen(lex->buffer) + 1; // sizeof buffer plus '\0'
  lex->i = 0;
  lex->current = source[lex->i];
  return lex;
}

/* clipInit takes a Clipboard and an InitSize */
Clipboard *clipInit(int iSize) {
  Clipboard *clip = malloc(sizeof(Clipboard));
  if (!clip) {raiseError(clip, E_MALLOC, "failed to allocate memory for clipboard.");}
  clip->buffer = malloc(iSize);
  if (!clip->buffer) {raiseError(clip->buffer, E_MALLOC, "failed to allocate memory for clip buffer.");}

  clip->lenght = 0;
  clip->buffsize = iSize;
  clip->buffer[0] = '\0';

  return clip;
}

void freeClip(Clipboard *clip) { 
  if (clip) {
    free(clip->buffer);
    free(clip);
  }
}

void clearBuffer(Clipboard *clip) {
  free(clip->buffer);
  clip->buffer = malloc(clip->buffsize);
  if (!clip->buffer) {raiseError(clip, E_MALLOC, "failed to alloc new clipboard buffer.");}

  clip->lenght = 0;  
  clip->buffer[0] = '\0';
}

/* save char to buffer to collect and retrun string */
void saveToClip(Clipboard *clip, char c) {
    if (clip->lenght + 1 >= clip->buffsize) {
        clip->buffsize *= 2;
        char *newBuffer = realloc(clip->buffer, clip->buffsize);
        if (!newBuffer) {
            raiseError(NULL, E_MALLOC, "failed to reallocate clipboard buffer.");
            return;
        }
        clip->buffer = newBuffer;
    }
    clip->buffer[clip->lenght++] = c;
    clip->buffer[clip->lenght] = '\0';
}

/* NOTE: TODO: Lexer might make mistakes; a redo method would be great. */ 
/* count chars without increasing lex->i */
void *lexer(Lexer *lex) {
  Clipboard *clip = clipInit(16);
  if (!clip) {return NULL;}

  while (!(lex->i >= lex->bufferSize + 1)) {
    if (isalnum(lex->current)) {
      saveToClip(clip, lex->current);
      lexAdv(lex);
    } else if (lex->current == ' ' || lex->current == '\n') {
      printf("%s", makeToken(clip->buffer));
      /*printf("\n%s", clip->buffer);*/
      clearBuffer(clip);
      lexAdv(lex);
    } else {
      lexAdv(lex);
    } 
  }
  freeClip(clip);
}
