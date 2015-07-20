#include "kroman_process.h"
#include <string.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{
  if (argc >= 2) {
    if ((strcmp(argv[1], "--version") & (strcmp(argv[1], "-v"))) == 0) {
      printf("Kroman 1.0\n");
      exit(0);
    } else {
      printf("Usage: kroman < korean > roman\n");
      exit(0);
    }
  }
  kroman_process(stdin, stdout);
  return 0;
}