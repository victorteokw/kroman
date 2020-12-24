#include "kroman_process.h"
#include "kroman_convert.h"
#include "kroman_adjust.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>
#include <locale.h>
#include <stdbool.h>

#define KROMAN_MAXLINE 4096
#define KROMAN_SIZE 20

void kroman_process_line(char *user_line, FILE *outstream);

void kroman_process(FILE *instream, FILE *outstream) {
  // Set current user locale, may or may not be en_US.UTF-8
  setlocale(LC_ALL, "");
  char *user_line = malloc(KROMAN_MAXLINE * sizeof(char));
  while (fgets(user_line, KROMAN_MAXLINE, instream)) {
    kroman_process_line(user_line, outstream);
  }
  free(user_line);
  if (ferror(instream)) {
    printf("Instream error occured!\n");
    exit(1);
  }
}

void kroman_process_line(char *user_line, FILE *outstream) {
  wchar_t *wide_line = malloc(KROMAN_MAXLINE * sizeof(wchar_t));
  mbstowcs(wide_line, user_line, KROMAN_MAXLINE);
  size_t len = wcslen(wide_line);
  bool last_is_hangul = false;
  for (size_t i = 0; i < len; ++i) {
    if(i < len - 1)
      kroman_adjust(&(wide_line[i]), &(wide_line[i + 1]));
    wchar_t wide_char = wide_line[i];
    char *retstring = malloc(sizeof(char) * KROMAN_SIZE);
    memset(retstring, 0, sizeof(char) * KROMAN_SIZE);
    bool is_hangul;
    kroman_convert(wide_char, retstring, &is_hangul);
    if (last_is_hangul && is_hangul) {
      fprintf(outstream, "-%s", retstring);
    } else {
      fprintf(outstream, "%s", retstring);
    }
    
    last_is_hangul = is_hangul;
    free(retstring);
  }
  free(wide_line);
}
