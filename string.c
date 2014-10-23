#include <stdio.h>
#include <stdlib.h>

#define BUFFER_FACTOR 2

struct string {
  char *memory;
  unsigned int length; // number of characters, as would be printed
  unsigned int size; // actual number of bytes currently stored
  unsigned int capacity; // amount of bytes we could store
};

struct string* new_string(char *content);
int getlength(char *s);
void append(struct string *s, char *more_content);
void copy_characters(char *location, char *content, int length);
void print_string(struct string *s);
void free_string(struct string *s);

struct string* new_string(char *content) {
  unsigned int length, size;
  char *allocated_charray;
  length = getlength(content);
  size = (length+1) * sizeof(char);
  allocated_charray = malloc(size);
  copy_characters(allocated_charray, content, length);

  struct string *temp = malloc(sizeof(struct string));
  temp->memory = allocated_charray;
  temp->length = length;
  temp->size = size;
  temp->capacity = size;
  return temp;
}

int getlength(char *s) {
  int i = 0;
  while(*(s + i) != '\0')
    i++;
  return i;
}

void copy_characters(char *location, char *content, int length) {
  int i = 0;
  for (; i < length; i++)
    *(location + i) = *(content + i);
  *(location + i) = '\0';
}

void print_string(struct string *s) {
  for (int i = 0; i < s->length; i++)
    printf("%c", *(s->memory + i));
  printf("\n");
}

void append(struct string *s, char *more_content) {
  int additional_length = getlength(more_content);
  int needed_capacity = s->size + (additional_length * sizeof(char));

  if (needed_capacity > s->capacity)
  {
    s->memory = realloc(s->memory, needed_capacity * BUFFER_FACTOR);
    copy_characters(s->memory + s->length, more_content, additional_length);
    s->size = needed_capacity;
    s->capacity = needed_capacity * BUFFER_FACTOR;
  } else {
    copy_characters(s->memory + s->length, more_content, additional_length);
    s->size = needed_capacity;
  }
  s->length = s->length + additional_length;
}

void free_string(struct string *s){
 free(s->memory);
 s->memory = NULL;
 s->size = s->length = s->capacity = 0;
}

struct string* concat(struct string *a, struct string *b) {
  struct string *c = new_string(a->memory);
  append(c, b->memory);
  return c;
}

int main() {
  struct string *test_str = new_string("hello");
  print_string(test_str);
  printf("length: %d\n", test_str->length);
  printf("capacity: %d\n\n", test_str->capacity);

  append(test_str, " test");
  print_string(test_str);
  printf("length: %d\n", test_str->length);
  printf("capacity: %d\n\n", test_str->capacity);


  append(test_str, " test");
  print_string(test_str);
  printf("length: %d\n", test_str->length);
  printf("capacity: %d\n\n", test_str->capacity);

  struct string *bla = concat(test_str, new_string(" bla"));
  print_string(bla);
  printf("length: %d\n", bla->length);
  printf("capacity: %d\n\n", bla->capacity);

  return 0;
}
