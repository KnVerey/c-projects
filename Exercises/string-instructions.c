#include <stdio.h>

struct string {
  char *memory;
  unsigned int length; // actual number of bytes in memory
  unsigned int size; // amount of bytes we could store
};

struct string* new_string(char *content) {
  // ...
  // "man malloc"
}

struct string* append(struct string *s, char *more_content) {
  // ...
  // "man realloc"
}

void print(struct string *s) {
  // ...
}

int main() {
  struct string* str = new_string("hello");

  str = append(str, " test");

  print(str); // hello test

  str->length; // 10
}
