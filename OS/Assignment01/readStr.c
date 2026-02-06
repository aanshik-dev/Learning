#include <stdio.h>

int main(void) {
  int count = 0;
  char c;
  while ((c = getchar()) != EOF) { // Ctrl + Z
    if (!(c >= 'a' && c <= 'z') && !(c >= 'A' && c <= 'Z') && c != '\n') {
      count++;
    }
  }
  fprintf(stdout, "%d \n", count);
  return 0;
}