#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define LOWEST_CHAR 32
#define HIGHEST_CHAR 126
#define NUM_CHARS_HANDLED (HIGHEST_CHAR - LOWEST_CHAR + 1)
#define KEEPER_BYTES (NUM_CHARS_HANDLED / 8) + !!(NUM_CHARS_HANDLED % 8)

int all_unique_chars();

int main(){
  char unique[] = "abcdefgukjpm";
  char duplicates[] = "abcdeffgukjpm";
  char non_alpha[] = "abcdefguk;;jpm";
  char case_sensitive[] = "abcedfgukGjpm";
  char garbage[] = { 9, 'a', 127, '\0'};
  char limits[] = { LOWEST_CHAR, HIGHEST_CHAR, '\0' };

  printf("%s has all unique chars: %d\n", duplicates, all_unique_chars(duplicates));
  printf("%s has all unique chars: %d\n", non_alpha, all_unique_chars(non_alpha));
  printf("%s has all unique chars: %d\n", unique, all_unique_chars(unique));
  printf("%s has all unique chars: %d\n", case_sensitive, all_unique_chars(case_sensitive));
  printf("%s has all unique chars: %d\n", garbage, all_unique_chars(garbage));
  printf("%s has all unique chars: %d\n", limits, all_unique_chars(limits));
  return 0;
}

int all_unique_chars(char s[]) {
  char *count_keeper = calloc(KEEPER_BYTES, 1);
  int position_number, current_byte, current_bit;

  for(int i=0; s[i] != '\0'; i++){
    position_number = tolower(s[i]) - LOWEST_CHAR;
    if (position_number < 0 || position_number > (HIGHEST_CHAR - LOWEST_CHAR)) {
      printf("Out-of-range filtered! ");
      continue;
    }

    current_byte = position_number / 8;
    current_bit = position_number % 8;
    if ((count_keeper[current_byte] & 1<<current_bit) == 0){
      count_keeper[current_byte] |= 1<<current_bit;
    } else {
      free(count_keeper);
      return 0;
    }
  }
  free(count_keeper);
  return 1;
}
