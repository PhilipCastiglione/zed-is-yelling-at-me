#include <stdio.h>
#include <ctype.h>
//#include <string.h>

// forward declarations
int can_print_it(char ch);
void print_letters(char arg[]);
//void print_letters(char arg[], int str_length);

void print_arguments(int argc, char *argv[])
{
  int i = 0;
  //int i; // yep, this is fine

  for(i = 1; i < argc; i++) {
  //for(i = 1; i < argc + 1; i++) { // rad error, out of range on array
    print_letters(argv[i]);
    //print_letters(argv[i], strlen(argv[i]));
  }
}

void print_letters(char arg[])
//void print_letters(char arg[], int str_length)
{
  int i = 0;

  for(i = 0; arg[i] != '\0'; i++) {
  //for(i = 0; i < str_length; i++) {
    char ch = arg[i];

    if(can_print_it(ch)) {
    //if(isalpha(ch) || isblank(ch)) { // couscous code...
      printf("'%c' == %d ", ch, ch);
    }
  }

  printf("\n");
}

int can_print_it(char ch)
{
  return isalpha(ch) || isblank(ch);
}

int main(int argc, char *argv[])
{
  print_arguments(argc, argv);
  //char derp[] = "for reals";
  //char *herp[] = {"for reals", "for srs"};
  //printf("%s\n", derp);
  //printf("%s\n", herp[1]);
  return 0;
}
