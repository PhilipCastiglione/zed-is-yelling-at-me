#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

int main(int argc, char *argv[])
{
  for(int i = 0; i < 107 ; i++) {
    errno = i;
    printf("Error message for errno %d\n", i);
    perror("Custom message");
  }

  char* totes_string = "123";
  int omg = atoi(totes_string);
  int woa = (int) totes_string;

  printf("%s\n", totes_string);
  printf("%d\n", omg);

  // this prints out a hilarious int that is not at all
  // what you expect
  printf("%d\n", woa);

  return 0;
}
