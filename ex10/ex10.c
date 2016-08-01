#include <stdio.h>

int main(int argc, char *argv[])
{
  int i = 0;

  // go through each string in argv
  // why a I skipping argv[0]?
  for(i = 1; i < argc; i++) {
  //for(i = 0; i < argc; i++) {
  //for(int i = 1; i < argc; i++) { // yep
    //int amIAThing = 5;
    printf("arg %d: %s\n", i, argv[i]);
  }

  //printf("well, %d\n", amIAThing); // no, you are not

  // let's make or own array of strings
  char *states[] = {
    "California", "Oregon",
    "Washington", "Texas"
  };
  int num_states = 4;

  for(i = 0; i < num_states; i++) {
  //for(int i = 0; i < num_states; i++) { // yep
    printf("state %d: %s\n", i, states[i]);
  }

  printf("NULL yo: %s\n", NULL);

  argv[1] = states[1];

  printf("states[1]: %s\n", states[1]);
  printf("argv[1]: %s\n", argv[1]);

  states[2] = argv[2];

  printf("argv[2]: %s\n", argv[2]);
  printf("states[2]: %s\n", states[2]);

  return 0;
}
