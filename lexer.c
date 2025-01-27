#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lexer.h"

Token *tokenize(const char *source, size_t *arrTokenSize) {
  size_t t_Capacity = 8;  // array size 
  size_t t_Count = 0;     // token t_Count

  Token *tokens = malloc(t_Capacity * sizeof(Token)); // how he know??? how he know the size of struct???
  
  if (!tokens) {
    fprintf(stderr, "\n");
    free(tokens);
    exit(EXIT_FAILURE);
  } 

  // looper that goes through each char
  const char *loopPtr = source;

  while (*loopPtr) {
    printf("'%c' \n", *loopPtr);
    
    if (t_Count >= t_Capacity) {
      t_Capacity *= 2; // TODO: dont do this
      tokens = realloc(tokens, t_Capacity * sizeof(Token));
    }

    if (*loopPtr == '\0') {free(tokens); exit(EXIT_FAILURE);}
    loopPtr++;
  }
}

int main() {
  size_t numT = 0;
  tokenize("Hello", &numT);
}
