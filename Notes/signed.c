#include <stdio.h>

int main() {
  signed char a = 128;
  unsigned char b = 255;

  printf("%d\n", a+1);
  printf("%u\n", (unsigned char)(b+1));

}
