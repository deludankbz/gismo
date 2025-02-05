#include <stdio.h>
#include <stdlib.h>
#include "include/errors.h"

/* opens a file. wow!
 * NOTE *openFile retuns a buffer with a double NULL terminator; it's not a bug, it's a feature 
*/
char *openFile(const char *filename) {
  FILE *file = fopen(filename, "rb");
  if (!file) { raiseWarn(E_UNKOWN, "buffLooper went wrong!\n");exit(EXIT_FAILURE); }

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
    /*printf("%c", *buffLooper);*/
    if (*buffLooper == '\0') { raiseWarn(E_UNKOWN, "buffLooper went wrong!\n");exit(EXIT_FAILURE); }
    buffLooper++;
  }

  fclose(file);
  return buffer;
}
