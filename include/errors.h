#ifndef ERRORS_H
#define ERRORS_H

// TODO: Make a well defined struct with more error 
// messages, achieving a more complete "debugging" state.
typedef enum {
  E_MALLOC,   // malloc shittery
  E_FILE,     // file io shittery
  E_UNKOWN,   // wtf?

  E_INCEPTION,// so deep omg
} ErrorType;

typedef struct {
  ErrorType type;
  char *value;
} Error;


static void *printError(const Error *err);

static void *errTerm();

extern void *raiseErr(ErrorType type, char *value);

#endif // ERRORS_H
