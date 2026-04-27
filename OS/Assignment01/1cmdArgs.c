#include <stdio.h>

int main(int argc, char *argv[]) {
  for (int i = 1; i < argc; i++) {
    if (argv[i][0] != '-') {
      printf("%s ", argv[i]);
    }
  }
  if (argc > 1)
    printf("\n");
  return 0;
}