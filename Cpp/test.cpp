#include <iostream>
#include <stdio.h>
#include <string.h>
using namespace std;

void converge(char *targ, char *src);

void converge(char *targ, char *src) {
  int i, j;
  for (i = 0, j = strlen(src) - 1; i <= j; i++, j--) {
    targ[i] = src[i];
    targ[j] = src[j];
    for (int k = 0; k < strlen(src); k++) {
      printf("%c", targ[k]);
    }
    cout << "\n";
  }
}

int main(void) {
  char target[80] = "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX";
  char *src = (char *)"This is a converging string.";
  converge(target, src);
  return 0;
}