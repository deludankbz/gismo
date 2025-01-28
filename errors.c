#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "include/errors.h"

/* Prints an error. How magical. */
static void *printError(const Error *err) { printf("[%u] - %s\n", err->type, err->value); return NULL; }

/* Exits the program */
static void *errTerm() { exit(EXIT_FAILURE); return NULL; }

/* raises an error message and quits the program */
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

  err->type = type; err->value = buffer; // you dirty little bastard. BASTARd!
  printError(err);

  free(err); va_end(args); errTerm();
  return NULL;
}

/* raises a warning message but doesn't quit the program */
extern void *raiseWarn(ErrorType type, const char *format, ...) {
  va_list args;
  va_start(args, format);

  char buffer[1024];
  vsnprintf(buffer, sizeof(buffer), format, args);

  Error *err = malloc(sizeof(Error));
  if (!err) {
    perror("[e_inception] malloc() for Error struct went wrong!");
  } 

  /* how can you handle something that you don't know yet? */
  err->type = type; err->value = buffer; // you dirty little bastard. BASTARd!
  printError(err);
  
  free(err); va_end(args);
  return NULL;
}

/*int main() {*/
/*  char *chav = "fnosnfsop.gs";*/
/*  raiseError(E_INCEPTION, "'%s' couldn't be opened!", chav);*/
/*}*/
