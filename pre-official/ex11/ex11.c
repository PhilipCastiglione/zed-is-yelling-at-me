#include <stdio.h>

int main(int argc, char *argv[])
{
  // go through each string in argv

  int i = 0;
  while(i < argc) {
    printf("arg %d: %s\n", i, argv[i]);
    i++;
  }

  int j = argc;
  while(j > 0) {
    j--;
    printf("arg %d: %s\n", j, argv[j]);
  }

  // let's make our own array of strings
  char *states[] = {
    "California", "Oregon",
    "Washington", "Texas"
  };

  int num_states = 4;
  i = 0; // watch for this
  while(i < num_states) {
    printf("state %d: %s\n", i, states[i]);
    i++;
  }

  i = 0;
  while(i < num_states) {
    states[i] = argv[i];
    printf("state %d: %s\n", i, states[i]);
    i++;
  }

  return 0;
}
