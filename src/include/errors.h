#ifndef ERRORS_H
#define ERRORS_H


/* ERRORS
 */


#include <stdio.h>
typedef enum {
  /* malloc & free related errors */
  E_MALLOC, E_FREE,
  E_BUFFER_OVERFLOW,

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
