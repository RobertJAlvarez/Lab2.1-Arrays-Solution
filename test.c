#include <errno.h>     //errno
#include <stdio.h>     //printf() fprintf()
#include <stdlib.h>    //rand()
#include <string.h>    //strcpy()
#include <sys/mman.h>  //mmap() munmap()
#include <sys/wait.h>  //wait()
#include <time.h>      //time()
#include <unistd.h>    //fork()

#include "./h/ArrayList.h"
#include "./h/my_string.h"
#include "./h/tokenizer.h"

// This is to include my tokenize implementation
char **my_tokenize(char *str, const char *delims);

#define N_TESTS ((size_t)1000)
#define MAX_LENGTH ((size_t)32)

static void error_no_memory(void) {
  fprintf(stderr, "No more memory available.\n");
  return;
}

static char *randstring(size_t length) {
  static const char charset[] =
      "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789`~!@#$%^&*"
      "()_+-=[]{}\\|;:,<.>/?";
  char *randomString = NULL;

  if (!length) length = 1;
  if ((randomString = (char *)malloc(sizeof(char) * (length + 1))) == NULL)
    return NULL;

  for (size_t i = 0; i < length; i++) {
    int key = rand() % (int)(sizeof(charset) - 1);
    randomString[i] = charset[key];
  }

  randomString[length] = '\0';

  return randomString;
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
  size_t passed = 0;
  const double points = 4.;
  char *s;

  printf("Function %s() ", __func__);

  for (size_t i = 0; i < N_TESTS; i++) {
    s = randstring(((size_t)rand()) % MAX_LENGTH);
    passed += (strlen(s) == str_len(s));
    free(s);
  }

  return points * ((double)passed) / ((double)N_TESTS);
}

static void *_make_i_str(char *s1, size_t length, size_t i) {
  char *s2;

  if (i % 5 == 0) {
    // Make a copy of s1 in s2
    s2 = strdup(s1);
  } else if (i % 7 == 0) {
    // Make a new string of the same length
    s2 = randstring(length);
  } else {
    // Make a new string with potentially different length
    s2 = randstring(((size_t)rand()) % MAX_LENGTH);
  }

  return s2;
}

double test_str_cmp(void) {
  size_t passed = 0;
  const double points = 4.;
  char *s1, *s2;
  size_t length, n;
  int cmp1, cmp2;

  printf("Function %s() ", __func__);

  for (size_t i = 0; i < N_TESTS; i++) {
    length = ((size_t)rand()) % MAX_LENGTH;

    if ((s1 = randstring(length)) == NULL) {
      error_no_memory();
      return 0.0;
    }

    // Make a new string s2
    if ((s2 = _make_i_str(s1, length, i)) == NULL) {
      error_no_memory();
      free(s1);
      return 0.0;
    }

    if (i % 2) {
      // Compare using strncmp
      n = ((size_t)rand()) % MAX_LENGTH;
      cmp1 = strncmp(s1, s2, n);
      cmp2 = str_n_cmp(s1, s2, n);
    } else {
      // Compare using strcmp
      cmp1 = strcmp(s1, s2);
      cmp2 = str_cmp(s1, s2);
    }

    passed += (((cmp1 < 0) && (cmp2 < 0)) || ((cmp1 > 0) && (cmp2 > 0)) ||
               ((cmp1 == 0) && (cmp2 == 0)));

    free(s1);
    free(s2);
  }

  return points * ((double)passed) / ((double)N_TESTS);
}

double test_mem_cpy(void) {
  size_t passed = 0;
  const double points = 4.;

  size_t length;
  char *s1, *s2, *s3;

  printf("Function %s() ", __func__);

  for (size_t i = 0; i < N_TESTS; i++) {
    length = ((size_t)rand()) % MAX_LENGTH;

    if ((s1 = randstring(length)) == NULL) {
      error_no_memory();
      return 0.0;
    }

    // Add 1 to length to account for the null character
    length += 1;

    if ((s2 = (char *)malloc(sizeof(char) * length)) == NULL) {
      error_no_memory();
      free(s1);
      return 0.0;
    }

    if ((s3 = (char *)malloc(sizeof(char) * length)) == NULL) {
      error_no_memory();
      free(s1);
      free(s2);
      return 0.0;
    }

    memcpy(s2, s1, length);
    mem_cpy(s3, s1, length);

    passed += (strcmp(s2, s3) == 0);

    free(s1);
    free(s2);
    free(s3);
  }

  return points * ((double)passed) / ((double)N_TESTS);
}

static double _test_str_charset(int is_str_chr) {
  size_t passed = 0;
  const double points = 4.;

  char *s1, *s2, *s3;
  char *charset;
  size_t n;

  for (size_t i = 0; i < N_TESTS; i++) {
    if ((s1 = randstring((size_t)rand() % MAX_LENGTH)) == NULL) {
      error_no_memory();
      return 0.0;
    }

    if (is_str_chr) {
      n = 1;
    } else {
      n = (size_t)(rand() % 4);
    }

    if ((charset = randstring(n)) == NULL) {
      error_no_memory();
      free(s1);
      return 0.0;
    }

    if (is_str_chr) {
      s2 = strchr(s1, (int)charset[0]);
      s3 = str_chr(s1, (int)charset[0]);
    } else {
      s2 = strpbrk(s1, charset);
      s3 = str_p_brk(s1, charset);
    }

    passed += (s2 == s3);

    free(s1);
    free(charset);
  }

  return points * ((double)passed) / ((double)N_TESTS);
}

double test_str_chr(void) {
  printf("Function %s() ", __func__);

  return _test_str_charset(/* is_str_chr = */ 1);
}

double test_str_p_brk(void) {
  printf("Function %s() ", __func__);

  return _test_str_charset(/* is_str_chr = */ 0);
}

double test_str_sep(void) {
  size_t passed = 0;
  const double points = 4.;

  char *org1, *org2;
  char *s1, *s2, *s3, *s4;
  char *delim;

  printf("Function %s() ", __func__);

  for (size_t i = 0; i < N_TESTS; i++) {
    // Get 4 random delimiter characters
    if ((delim = randstring(4)) == NULL) {
      error_no_memory();
      return 0.0;
    }

    // Make s1
    if ((s1 = randstring((size_t)rand() % MAX_LENGTH)) == NULL) {
      error_no_memory();
      free(delim);
      return 0.0;
    }

    // Make a copy of s1
    if ((s2 = strdup(s1)) == NULL) {
      error_no_memory();
      free(delim);
      free(s1);
      return 0.0;
    }

    // Keep original address of s1 and s2
    org1 = s1;
    org2 = s2;

    // Iterate over s1 and s2 until they are over or diverge
    do {
      s3 = strsep(&s1, delim);
      s4 = str_sep(&s2, delim);
    } while ((s1 != NULL) && (s2 != NULL) && (*s3 != '\0') && (*s4 != '\0'));

    passed += (*s3 == *s4);

    free(delim);
    free(org1);
    free(org2);
  }

  return points * ((double)passed) / ((double)N_TESTS);
}

double test_str_cat(void) {
  size_t passed = 0;
  const double points = 4.;

  char *s1, *s2, *s3;
  size_t l1, l2;

  printf("Function %s() ", __func__);

  for (size_t i = 0; i < N_TESTS; i++) {
    // NOTE: 2 is added to the length to avoid errors using strcat()
    l1 = 2 + ((size_t)rand()) % MAX_LENGTH;
    if ((s1 = randstring(l1)) == NULL) {
      error_no_memory();
      return 0.0;
    }

    l2 = 2 + ((size_t)rand()) % MAX_LENGTH;
    if ((s2 = randstring(l2)) == NULL) {
      error_no_memory();
      free(s1);
      return 0.0;
    }

    if ((s3 = strdup(s2)) == NULL) {
      error_no_memory();
      free(s1);
      free(s2);
      return 0.0;
    }

    // Increase the size of s2 and s3 to hold s1
    if ((s2 = reallocf(s2, l1 + l2 + 1)) == NULL) {
      error_no_memory();
      free(s1);
      free(s3);
      return 0.0;
    }
    if ((s3 = reallocf(s3, l1 + l2 + 1)) == NULL) {
      error_no_memory();
      free(s1);
      free(s2);
      return 0.0;
    }

    // Copy s1 into s2 and s3
    str_cat(s3, s1);
    strcat(s2, s1);

    passed += (strcmp(s2, s3) == 0);

    free(s1);
    free(s2);
    free(s3);
  }

  return points * ((double)passed) / ((double)N_TESTS);
}

double test_tokenize(void) {
  size_t passed = 0;
  const double points = 4.;

  char **t1, **t2;
  char *s1, *s2;
  char *delim;

  printf("Function %s() ", __func__);

  for (size_t i = 0; i < N_TESTS; i++) {
    // Get 4 random delimiter characters
    if ((delim = randstring(8)) == NULL) {
      error_no_memory();
      return 0.0;
    }

    // Make s1
    if ((s1 = randstring((size_t)rand() % MAX_LENGTH)) == NULL) {
      error_no_memory();
      free(delim);
      return 0.0;
    }

    // Make a copy of s1
    if ((s2 = strdup(s1)) == NULL) {
      error_no_memory();
      free(delim);
      free(s1);
      return 0.0;
    }

    t1 = tokenize(s1, delim);
    t2 = my_tokenize(s2, delim);

    // Assume passed and subtract if fail
    passed++;

    // Iterate over both arrays to validate identical strings
    for (; (*t1 != NULL) && (*t2 != NULL); t1++, t2++) {
      if (strcmp(*t1, *t2) != 0) {
        passed--;
        break;
      }
    }

    free(s1);
    free(s2);
    free(delim);
  }

  return points * ((double)passed) / ((double)N_TESTS);
}

static double *func_points;

int main(void) {
  double total_points;
  int n_funcs;
  double (*functions[])(void) = {
      &test_AL_get_at,       &test_AL_set_at,      &test_AL_insert_first,
      &test_AL_delete_first, &test_AL_insert_last, &test_AL_delete_last,
      &test_AL_insert_at,    &test_str_len,        &test_str_cmp,
      &test_mem_cpy,         &test_str_chr,        &test_str_p_brk,
      &test_str_sep,         &test_str_cat,        &test_tokenize};

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
