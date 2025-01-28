#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "include/errors.h"

/* Prints an error. How magical. */
extern void *printError(const Error *err) { printf("[%u] - %s\n", err->type, err->value); return NULL; }

/* Exits the program */
extern void *errTerm() { exit(EXIT_FAILURE); return NULL; }

extern void *raiseError(ErrorType type, const char *format, ...) {
  va_list args;
  va_start(args, format);

  char buffer[1024];
  vsnprintf(buffer, sizeof(buffer), format, args);

  Error *err = malloc(sizeof(Error));
  if (!err) {
    perror("[e_inception] malloc() for Error struct went wrong!");
    errTerm();
  } 

  /* how can you handle something that you don't know yet? */
  err->type = type; err->value = buffer; // you dirty little bastard. BASTARd!
  printError(err);

  free(err);
  va_end(args);
  errTerm();
  return NULL;
}

/*int main() {*/
/*  char *chav = "fnosnfsop.gs";*/
/*  raiseError(E_INCEPTION, "'%s' couldn't be opened!", chav);*/
/*}*/
