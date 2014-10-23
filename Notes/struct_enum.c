#include <stdio.h>


int main() {

  struct foo {
    char x;
  };

  enum day { monday, tuesday };

  struct something {
    char a;
    char b;
    struct foo y;
    enum day today;
  };

  struct something foobar;

  struct foo bla;

  foobar.a = 1;
  foobar.b = 2;
  foobar.today = monday;
  foobar.y = bla;

}
