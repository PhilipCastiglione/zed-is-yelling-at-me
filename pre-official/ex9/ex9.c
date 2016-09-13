#include <stdio.h>

int main(int argc, char *argv[])
{
  int numbers[4] = {0};
  //int numbers[4] = {1};
  //int numbers[4] = {'a'};
  char name[4] = {'a'};
  //char *name = "a\0\0\0"; // sweet error
  //char *name = "a\0"; // sweet error

  // first, print them out raw
  printf("numbers: %d %d %d %d\n",
          numbers[0], numbers[1],
          numbers[2], numbers[3]);
  
  printf("name each: %c %c %c %c\n",
          name[0], name[1],
          name[2], name[3]);

  printf("name: %s\n", name);

  // setup the numbers;
  numbers[0] = 1;
  numbers[1] = 2;
  numbers[2] = 3;
  numbers[3] = 4;
  //numbers[0] = 'P';
  //numbers[1] = 'h';
  //numbers[2] = 'i';
  //numbers[3] = '\0';

  // setup the name;
  name[0] = 'P';
  name[1] = 'h';
  name[2] = 'i';
  name[3] = '\0';

  // then print them out initialized
  printf("numbers: %d %d %d %d\n",
          numbers[0], numbers[1],
          numbers[2], numbers[3]);
  
  printf("name each: %c %c %c %c\n",
  //printf("name each: %d %d %d %d\n",
          name[0], name[1],
          name[2], name[3]);

  // print the name ~like~ (as?) a string
  printf("name: %s\n", name);

  // another way to use name
  char *another = "Phi";

  printf("another: %s\n", another);

  printf("another each: %c %c %c %c\n",
          another[0], another[1],
          another[2], another[3]);

  // nope
  //int *wat = {1,2,3}
  //printf("wat: %d %d %d\n",
          //wat[0], wat[1], wat[2]);
  char *derp = "derp";
  printf("derp? %s\n", derp);
  //printf(derp); //sort of but not really

  return 0;
}
