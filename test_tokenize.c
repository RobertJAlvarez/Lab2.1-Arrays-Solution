#include <errno.h>   //errno
#include <stdio.h>   //printf() fprintf()
#include <stdlib.h>  //malloc() free()
#include <string.h>  //strcpy()
#include <time.h>    //time()

#include "my_string.h"
#include "tokenizer.h"

#define MAX_LENGTH ((size_t)30)

static void error_no_memory(void) {
  fprintf(stderr, "No more memory available. Errorno: %d\n", errno);
  return;
}

static char *randstring(size_t length) {
  static const char charset[] =
      "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789`~!@#$%^&*"
      "()_+-=[]{}\\|;:,<.>/?";
  char *randomString = NULL;

  if (length == 0) length = 1;
  if ((randomString = (char *)malloc(sizeof(char) * (length + 1))) == NULL)
    return NULL;

  for (size_t i = 0; i < length; i++) {
    int key = rand() % (int)(sizeof(charset) - 1);
    randomString[i] = charset[key];
  }

  randomString[length] = '\0';

  return randomString;
}

int main(void) {
  char **tokens;
  char *delim, *s;
  size_t n_tokens;

  srand((unsigned int)time(NULL));

  if ((delim = randstring(8)) == NULL) {
    error_no_memory();
    return 0.0;
  }

  if ((s = randstring((size_t)rand() % MAX_LENGTH)) == NULL) {
    error_no_memory();
    free(delim);
    return 0.0;
  }

  printf("s = %s\n", s);
  printf("delim = %s\n", delim);

  tokens = tokenize(s, delim);

  n_tokens = 0;
  for (char **token = tokens; *token; token++) n_tokens++;
  printf("\nYou found %zu tokens in s\n", n_tokens);

  for (size_t i = 0; i < n_tokens; i++)
    printf("token %zu: %s\n", i + 1, tokens[i]);

  free(s);
  free(delim);
  free(tokens);

  return 0;
}
