#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "include/errors.h"

/* Prints an error. How magical. */
static void *printError(const Error *err) { printf("[%u] - %s\n", err->type, err->value); return NULL; }

/* Exits the program */
static void *errTerm() { exit(EXIT_FAILURE); return NULL; }

void *raiseErr(ErrorType type, char *value) {
  Error *err = malloc(sizeof(Error));
  if (!err) {
    perror("[e_inception] malloc() for Error struct went wrong!");
    errTerm();
  } 

  /* how can you handle something that you don't know yet? */
  err->type = type; err->value = value; // you dirty little bastard. BASTARd!
  printError(err);

  free(err);
  errTerm();
  return NULL;
}

int main() {
  raiseErr(E_INCEPTION, "STOP RIGHT THERE CRIMINAL SCUM!");
}
