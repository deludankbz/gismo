#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "include/errors.h"

/* ERRORS
 */

/* prints an error. how magical. */
static void printWarn(const Error *err) { printf("\x1b[1;33m[%u] - %s\x1b[0m\n", err->type, err->value); }
static void printError(const Error *err) { printf("\x1b[1;31m[%u] - %s\x1b[0m\n", err->type, err->value); }

/* exits the program */
static void errTerm() { exit(EXIT_FAILURE); }

/* raises an error message and quits the program */
void raiseError(ErrorType type, char *source, ...) {
  va_list args; va_start(args, source);

  int lenght = vsnprintf(NULL, 0, source, args) + 1;
  va_end(args);

  char *buffer = calloc(lenght , sizeof(char));

  va_start(args, source);
  vsnprintf(buffer, lenght, source, args);
  va_end(args);

  Error *err = malloc(sizeof(Error));
  if (!err) {
    perror("[e_inception] malloc() for Error struct went wrong!");
    free(buffer); errTerm();
  } 

  err->type = type; err->value = buffer; // i'll find you! you BASTARd!
  printError(err);

  free(buffer); free(err);
  /*errTerm();*/
}

/* raises a warning message but doesn't quit the program */
void raiseWarn(ErrorType type, char *source, ...) {
  va_list args; va_start(args, source);

  int lenght = vsnprintf(NULL, 0, source, args);
  va_end(args);

  char *buffer = calloc((lenght + 1), sizeof(char));

  va_start(args, source);
  vsnprintf(buffer, lenght + 1, source, args);
  va_end(args);

  Error *err = malloc(sizeof(Error));
  if (!err) { perror("[e_inception] malloc() for Error struct went wrong!"); } 
  err->type = type; err->value = buffer; // i'll find you! you BASTARd!
  printWarn(err);

  free(buffer); free(err);
}
