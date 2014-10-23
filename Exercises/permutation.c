#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_VALID_CHAR 127

int is_permutation();
void fill_counts();

char x = 'a'
char x = 97
char x = 0x61
char x = '\x61'


int main(){
  char string1[] = "cat rat bat!";
  char string2[] = "cat rat bat sat!";
  char string3[] = "cat rat cat!";
  char string4[] = "tab tar !tac";

  printf("%s is a permutation of %s: %d\n", string1, string1, is_permutation(string1, string1));
  printf("%s is a permutation of %s: %d\n", string1, string2, is_permutation(string1, string2));
  printf("%s is a permutation of %s: %d\n", string1, string3, is_permutation(string1, string3));
  printf("%s is a permutation of %s: %d\n", string1, string4, is_permutation(string1, string4));

  return 0;
}

int is_permutation(char s1[], char s2[]) {
  char s1_count_keeper[MAX_VALID_CHAR] = {};
  char s2_count_keeper[MAX_VALID_CHAR] = {};

  fill_counts(s1, s1_count_keeper);
  fill_counts(s2, s2_count_keeper);

  for (int i = 0; i < MAX_VALID_CHAR; ++i)
  {
    if (s1_count_keeper[i] != s2_count_keeper[i])
    {
      return 0;
    }
  }
  return 1;
}

void fill_counts(char s[], char count_keeper[]){
  int current_index = 0;

  for(int i=0; s[i] != '\0'; i++){
    current_index = (int) s[i];
    if(current_index < 0 || current_index > MAX_VALID_CHAR){
      continue;
    } else {
      count_keeper[current_index]++;
    }
  }
}
