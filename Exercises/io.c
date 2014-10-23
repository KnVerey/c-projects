#include <stdio.h>

int main() {
  int c;
  while ((c = getchar()) != EOF) {
    putchar(c);
  }
  printf("EOF VALUE: %u\n", c);
}
