#ifndef ERRORS_H
#define ERRORS_H

// TODO: Make a well defined struct with more error 
// messages, achieving a more complete "debugging" state.

#include <stdio.h>
typedef enum {
  /* malloc & free related errors */
  E_MALLOC, E_FREE,

  /* file related problems */
  E_FILE, E_MISSINGFILE,
  E_UNKOWN,

  /* errors inside errors.c */
  E_INCEPTION,
} ErrorType;

typedef struct {
  ErrorType type;
  char *value;
} Error;


static void printError(const Error *err);

static void errTerm();

/* raiseError should free the pointer given */
void raiseError(void *address, ErrorType type, char *format, ...);

void raiseWarn(ErrorType type, char *format, ...);

#endif // ERRORS_H
