#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

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

struct string_buffer* copy_buffer(struct string_buffer *buf) {
  struct string_buffer *newbuf = new_buffer();
  newbuf->count = buf->count;
  newbuf->strings = NULL;
  if(newbuf->count > 0) {
    newbuf->strings = malloc(sizeof(char*) * (buf->count));
    for (int i = 0; i < buf->count; ++i)
    {
      newbuf->strings[i] = buf->strings[i];
    }
  }
  return newbuf;
}

void append(struct string_buffer *buf, char *string) {
  buf->strings = realloc(buf->strings, sizeof(char*) * (buf->count + 1));
  *(buf->strings + (buf->count)) = string;
  buf->count++;
}

char* join(struct string_buffer *buf, char c) {
  char* full_string = NULL;
  if(buf->count == 0) {
    return full_string;
  }

  unsigned int total_length = 0;
  for (int i = 0; i < buf->count; ++i)
    total_length += strlen(*(buf->strings + i));

  total_length += (buf->count - 1) + 1;
  full_string = malloc(total_length);

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

void free_string_buffer(struct string_buffer *buf) {
  free(buf->strings);
  free(buf);
  // the strings themselves were created in main...
  // and any full_strings that have been generated may still be referenced too
}

void swapstrs(struct string_buffer *buf, int position1, int position2) {
  char *placeholder = buf->strings[position1];
  buf->strings[position1] = buf->strings[position2];
  buf->strings[position2] = placeholder;
}

void reverse(struct string_buffer *buf) {
  for (int i = 0, z = buf->count - 1; i < z; ++i, z--)
    swapstrs(buf, i, z);
}

// [...].shuffle.join
// Fisher-Yates shuffle: http://en.wikipedia.org/wiki/Fisher%E2%80%93Yates_shuffle
void shuffle(struct string_buffer *buf) {
  if(buf->count == 0)
    return;

  int swap_position;
  for (int i = buf->count - 1; i > 0; --i)
  {
    swap_position = (rand() % i);
    swapstrs(buf, i, swap_position);
  }
}

void removestr(struct string_buffer *buf, int index) {
  for (int i = index; i < buf->count; ++i)
  {
    buf->strings[i] = buf->strings[i+1];
  }
  buf->count--;
  realloc(buf->strings, sizeof(char*) * buf->count);
}

void uniq(struct string_buffer *buf) {
  for (int i = 0; i < buf->count; ++i)
  {
    for (int j = i + 1; j < buf->count; ++j)
    {
      if(strcmp(buf->strings[i], buf->strings[j]) == 0) {
        removestr(buf, j);
        j--;
      }
    }
  }
}

struct string_buffer* select(struct string_buffer *buf, int(*filter_function)(char*)) {
  struct string_buffer *newbuf = copy_buffer(buf);
  for (int i = 0; i < newbuf->count; ++i)
  {
    if(filter_function(newbuf->strings[i]) == 0) {
      removestr(newbuf, i);
      i--;
    }
  }

  return newbuf;
}

int containsx(char *str) {
  if (strchr(str, 'x') || strchr(str, 'X')) {
    return 1;
  } else {
    return 0;
  }
}


int main(void) {
  srand(time(0));
  struct string_buffer *buf = new_buffer();

  append(buf, "boggle");
  append(buf, "boggle");
  append(buf, "hello");
  append(buf, "testX");
  append(buf, "boggle");
  append(buf, "blaxx");
  append(buf, "boggle");

  printf("Original: %s\n", join(buf, ' '));
  reverse(buf);
  printf("Reversed: %s\n", join(buf, ' '));
  shuffle(buf);
  printf("Shuffled: %s\n", join(buf, ' '));
  uniq(buf);
  printf("Unique: %s\n", join(buf, ' '));

  struct string_buffer *filteredbuf = select(buf, &containsx);
  printf("Filtered: %s\n", join(filteredbuf, ' '));

  free_string_buffer(buf);
}
