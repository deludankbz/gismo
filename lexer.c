#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "include/lexer.h"

// TODO: Better error messages
//
// DONE: put headers into include
// DONE: Return should be ["x", " ", "=", " ", "1", "\0"] 

char *openFile(const char *filename) {
  FILE *file = fopen(filename, "rb");
  if (!file) {
    exit(EXIT_FAILURE);
  }

  fseek(file, 0, SEEK_END);
  // fSize + null terminator
  long fSize = ftell(file) + 1;
  fseek(file, 0, SEEK_SET);

  // malloc() for file buffer size
  char *buffer = malloc(fSize + 1);
  if (!buffer) {
    printf("buffer malloc went wrong!");
    exit(EXIT_FAILURE);
    return NULL;
  }

  size_t fileBytes = fread(buffer, 1, fSize, file);
  buffer[fileBytes] = '\0';

  const char *buffLooper = buffer;
  while (*buffLooper) {
    printf("%c", *buffLooper);
    if (*buffLooper == '\0') {printf("fuck fuck"); exit(EXIT_FAILURE);} // fix fuck fuck
    buffLooper++;
  }

  fclose(file);
  return buffer;
}

Token *tokenize(char *source, size_t *arrTokenSize) {
  size_t t_Capacity = 8;  // array size 
  size_t t_Count = 0;     // token t_Count

  Token *tokens = malloc(t_Capacity * sizeof(Token)); // how he know??? how he know the size of struct???
  //printf("t_Capacity: %zu; sizeof(Token): %lu", t_Capacity, sizeof(Token));
  
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
  /*tokenize("Hello", &numT);*/
  char *fCont = openFile("/home/deludank/Documents/Code/C/learningC/gismo/main.gs");
  tokenize(fCont, 0);
  /*printf("%c", *fCont);*/
}
