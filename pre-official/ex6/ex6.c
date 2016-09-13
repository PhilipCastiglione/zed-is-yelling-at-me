#include <stdio.h>

int main(int argc, char *argv[])
{
  int distance = 100;
  float power = 2.345f;
  double super_power = 56789.4532;
  char initial = 'L';
  char first_name[] = "Philip";
  char last_name[] = "Castiglione";

  printf("You are %d miles away.\n", distance);
  printf("You have %f levels of power.\n", power);
  printf("You have %f awesome super powers.\n", super_power);
  printf("I have an initial %c.\n", initial);
  printf("I have a first name %s.\n", first_name);
  printf("I have a last name %s.\n", last_name);
  printf("My whole name is %s %c. %s.\n", first_name, initial, last_name);
  //printf("My whole name is %s %c. %s.\n", initial, first_name, last_name); // sweet error
  printf("Here it is!!!\n");
  printf(">");
  printf("");
  printf("<\n");
  printf("There it was...\n");

  return 0;
}
