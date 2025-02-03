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

const char *makeToken(char *source) {
  // change to strcmp()
  if (strcmp(source, "+") == 0 || strcmp(source, "-") == 0 || strcmp(source, "*") == 0 || strcmp(source, "/") == 0) {
    return concat("token[id: %d; value: %s]\n", T_BINARY, source);
  }
  else if (isdigit((unsigned int)source[0])) {
    return concat("token[id: %d; value: %c]\n", T_NUMBER, (unsigned int)source[0]);
  } 
  else {return concat("token[id: %i; value: %s]\n", T_ARBITRARY, source);}
}
