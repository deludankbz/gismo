#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include "include/errors.h"

/* prints an error. how magical. */
static void printError(const Error *err) { printf("[%u] - %s\n", err->type, err->value); }

/* exits the program */
static void errTerm() { exit(EXIT_FAILURE); }

/* raises an error message and quits the program */
void raiseError(void *address, ErrorType type, char *format, ...) {
  va_list args; va_start(args, format);

  char *buffer = calloc(256, sizeof(char));
  vsnprintf(buffer, sizeof(buffer), format, args);

  Error *err = malloc(sizeof(Error));
  if (!err) {
    perror("[e_inception] malloc() for Error struct went wrong!");
    errTerm();
  } 

  err->type = type; err->value = buffer; // you dirty little bastard. BASTARd!
  printError(err);

  /* in theory, freeing a void * is perfectly safe but not good practice. */
  free(address);
  free(err); va_end(args); errTerm();
}

/* raises a warning message but doesn't quit the program */
void raiseWarn(ErrorType type, char *format, ...) {
  va_list args; va_start(args, format);

  char *buffer = calloc(256, sizeof(char));
  vsnprintf(buffer, sizeof(buffer), format, args);

  Error *err = malloc(sizeof(Error));
  if (!err) {
    perror("[e_inception] malloc() for Error struct went wrong!");
  } 

  /* how can you handle something that you don't know yet? */
  err->type = type; err->value = buffer; // you dirty little bastard. BASTARd!
  free(buffer);
  printError(err);
  
  free(err); va_end(args);
}
