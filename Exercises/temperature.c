#include <stdio.h>

int main()
{
  float fc_fahr, cf_fahr, fc_celcius, cf_celcius;

  int fc_lower = -40;
  int fc_upper = 120;
  int fc_step = 10;

  int cf_lower = -40;
  int cf_upper = 40;
  int cf_step = 5;

  printf("%s|%8s     ", "\u2109       ", "\u2103" );
  printf("%s|%8s\n", "\u2103     ", "\u2109" );
  printf("-------------       -------------\n");

  fc_fahr = fc_lower;
  cf_celcius = cf_lower;
  while (fc_fahr <= fc_upper || cf_celcius <= cf_upper) {
    fc_celcius = (5.0/9.0) * (fc_fahr-32.0);
    cf_fahr = cf_celcius * (9.0/5.0) + 32;
    printf("%3.0f   |%6.1f       ", fc_fahr, fc_celcius); // 3.0f = at least 3 char whide, no decimal digits
    printf("%3.0f   |%6.1f\n", cf_celcius, cf_fahr);
    fc_fahr = fc_fahr + fc_step;
    cf_celcius = cf_celcius + cf_step;
  }
}
