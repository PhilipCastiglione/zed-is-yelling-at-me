#include <stdio.h>

int main(int argc, char *argv[])
{
  int i = 0;

  if(argc == 1) {
  //if(argc == 2) {
    printf("You have only one argument. Zed thinks you suck, but I'm a little more tolerant.\n");
  } else if(argc > 1 && argc < 4) {
  //} else if(argc > 2 && argc < 5) {
    printf("Here are your arguments:\n");

    for(i = 0; i < argc; i++) {
      printf("%s ", argv[i]);
    }
    printf("\n");
  //} else if(argc > 10 || argc == 0) {
    //printf("You are either persistent or magical!\n");
  } else {
    printf("You have too many arguments. Again, Zed thinks you suck. I'd rather say you're over-eager...\n");
  }

  return 0;
}
