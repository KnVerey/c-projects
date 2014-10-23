#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct string_buffer {
  char **strings;
  unsigned int count;
};

struct string_buffer* new_buffer() {
  struct string_buffer *buf = malloc(sizeof(struct string_buffer));
  buf->strings = NULL;
  buf->count = 0;
  return buf;
}

void append(struct string_buffer *buf, char *string) {
  buf->strings = realloc(buf->strings, sizeof(char*) * (buf->count + 1));
  *(buf->strings + (buf->count)) = string;
  buf->count++;
}

char* join(struct string_buffer *buf, char c) {
  unsigned int total_length = 0;
  for (int i = 0; i < buf->count; ++i)
    total_length += strlen(*(buf->strings + i));

  total_length += (buf->count - 1) + 1;

  char* full_string = malloc(total_length);

  char *dst = full_string;

  for (int i = 0; i < buf->count; ++i){
    int len = strlen(buf->strings[i]);
    memcpy(dst, buf->strings[i], len);
    dst += len;

    if(i < buf->count - 1) {
      *dst = c;
      dst++;
    }
  }

  full_string[total_length - 1] = '\0';

  return full_string;
}

// free_string_buffer()

// ['hello', 'testx', 'blaxx'].reverse.join

// [...].shuffle.join

// [...].uniq.join

// **BONUS**
// [...].select{ ... }
// returns new buffer with elements for which filter_function() is != 0
// select(struct string_buffer *buf, *((int)filter_function(char*))


int main(void) {
  struct string_buffer *buf = new_buffer();

  append(buf, "hello");
  append(buf, "testx");
  append(buf, "blaxx");

  printf("%d\n", buf->count);
  printf("%s\n", join(buf, ' ')); // "hello test bla"
}
