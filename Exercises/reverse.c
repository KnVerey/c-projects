#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HELLO(i) i+5

void reverse(char s[]) {
  char *right_pointer = &s[strlen(s) - 1];
  char *left_pointer = &s[0];
  char placeholder;

  while(right_pointer > left_pointer)
  {
    placeholder = *left_pointer;
    *left_pointer = *right_pointer;
    *right_pointer = placeholder;

    right_pointer--;
    left_pointer++;
  }
}

int main(){
  char s[] = "cat rat bat !!!";

  reverse(s);
  printf("%s\n", s);

  return 0;
};
