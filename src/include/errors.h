#ifndef ERRORS_H
#define ERRORS_H

#include <stdio.h>


/* ERRORS */


typedef enum {
  /* malloc & free related errors */
  E_MALLOC, E_FREE,
  E_BUFFER_OVERFLOW,

  /* file related problems */
  E_FILE, E_MISSINGFILE,
  E_UNKOWN,

  /* errors inside errors.c */
  E_INCEPTION,

  /* token errors */
  E_NULLTOKEN,

  /* syntax errors */
  E_SYNTAX,
} ErrorType;

typedef struct {
  ErrorType type;
  char *value;
} Error;


static void printWarn(const Error *err);
static void printError(const Error *err);

static void errTerm();

/* raiseError should free the pointer given */
void raiseError(ErrorType type, char *source, ...);

void raiseWarn(ErrorType type, char *source, ...);

const char *genErrorText(ErrorType type, const char *fName, int line);

#endif // ERRORS_H
