#include <stdio.h>

int main() {
  char c;
  while ((c = getchar()) != EOF) {
    if (c >= 'A' && c <= 'Z') {
      c = (c - 'A') + 'a';
    } else if (c >= 'a' && c <= 'z') {
      c = (c - 'a') + 'A';
    }
    putchar(c);
  }
  return 0;
}