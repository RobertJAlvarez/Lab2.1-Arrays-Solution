#include <errno.h>     //errno
#include <stdio.h>     //printf() fprintf()
#include <stdlib.h>    //rand()
#include <string.h>    //strcpy()
#include <sys/mman.h>  //mmap() munmap()
#include <sys/wait.h>  //wait()
#include <time.h>      //time()
#include <unistd.h>    //fork()

#include "DoubleLL.h"
#include "bitwise_f.h"
#include "my_DoubleLL.h"
#include "my_bitwise_f.h"

static void error_no_memory(void) {
  fprintf(stderr, "No more memory available.\n");
  return;
}

static char *randstring(size_t length) {
  static char charset[] =
      "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789`~!@#$%^&*"
      "()_+-=[]{}\\|;:,<.>/?";
  char *randomString = NULL;

  if (!length) return NULL;
  if ((randomString = malloc(sizeof(char) * (length + 1))) == NULL) return NULL;

  for (size_t i = 0; i < length; i++) {
    int key = rand() % (int)(sizeof(charset) - 1);
    randomString[i] = charset[key];
  }

  randomString[length] = '\0';

  return randomString;
}

double test_AL_init(void) {
  printf("Function %s() ", __func__);

  return 0.0;
}

double test_AL_free(void) {
  printf("Function %s() ", __func__);

  return 0.0;
}

double test_AL_get_at(void) {
  printf("Function %s() ", __func__);
  return 0.0;
}

double test_AL_set_at(void) {
  printf("Function %s() ", __func__);
  return 0.0;
}

double test_AL_insert_first(void) {
  printf("Function %s() ", __func__);
  return 0.0;
}

double test_AL_delete_first(void) {
  printf("Function %s() ", __func__);
  return 0.0;
}

double test_AL_insert_last(void) {
  printf("Function %s() ", __func__);
  return 0.0;
}

double test_AL_delete_last(void) {
  printf("Function %s() ", __func__);
  return 0.0;
}

double test_AL_insert_at(void) {
  printf("Function %s() ", __func__);
  return 0.0;
}

double test_str_len(void) {
  printf("Function %s() ", __func__);
  return 0.0;
}

double test_str_n_cmp(void) {
  printf("Function %s() ", __func__);
  return 0.0;
}

double test_str_cmp(void) {
  printf("Function %s() ", __func__);
  return 0.0;
}

double test_mem_cpy(void) {
  printf("Function %s() ", __func__);
  return 0.0;
}

double test_str_chr(void) {
  printf("Function %s() ", __func__);
  return 0.0;
}

double test_str_p_brk(void) {
  printf("Function %s() ", __func__);
  return 0.0;
}

double test_str_sep(void) {
  printf("Function %s() ", __func__);
  return 0.0;
}

double test_str_cat(void) {
  printf("Function %s() ", __func__);
  return 0.0;
}

double test_tokenize(void) {
  printf("Function %s() ", __func__);
  return 0.0;
}

static double *func_points;

int main(void) {
  double total_points;
  int n_funcs;
  double (*functions[])(void) = {
      &test_AL_init,        &test_AL_free,         &test_AL_get_at,
      &test_AL_set_at,      &test_AL_insert_first, &test_AL_delete_first,
      &test_AL_insert_last, &test_AL_delete_last,  &test_AL_insert_at,
      &test_str_len,        &test_str_n_cmp,       &test_str_cmp,
      &test_mem_cpy,        &test_str_chr,         &test_str_p_brk,
      &test_str_sep,        &test_str_cat,         &test_tokenize};

  pid_t pid;

  n_funcs = sizeof(functions) / sizeof(functions[0]);
  total_points = 0.0;
  srand((unsigned int)time(NULL));

  func_points = mmap(NULL, sizeof *func_points, PROT_READ | PROT_WRITE,
                     MAP_SHARED | MAP_ANONYMOUS, -1, 0);

  for (int i = 0; i < n_funcs; i++) {
    pid = fork();

    if (pid < ((pid_t)0)) {
      fprintf(stderr, "fork() did not work: %s.\n Try running it again.\n",
              strerror(errno));
      return 1;
    }

    if (pid == ((pid_t)0)) {
      // We are the child.
      *func_points = -1.0;
      *func_points = functions[i]();

      return 0;
    }

    // Wait for children
    wait(NULL);

    if (*func_points < 0.0) {
      printf(
          "FAIL by student function, grade it manually and give no more than "
          "half of the full credit.\n");
    } else {
      printf("got %f points.\n", *func_points);
      total_points += *func_points;
    }
  }

  printf("%f\n", total_points);

  munmap(func_points, sizeof *func_points);

  return 0;
}
