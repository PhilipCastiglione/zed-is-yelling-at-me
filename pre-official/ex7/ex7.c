#include <stdio.h>

int main(int argc, char *argv[])
{
  int bugs = 100;
  double bug_rate = 1.2;

  printf("You have %d bugs at the imaginary rate of %f.\n",
          bugs, bug_rate);
  
  long universe_of_defects = 1L * 1024L * 1024L * 1024L;
  printf("The entire universe has %ld bugs.\n",
          universe_of_defects);

  double expected_bugs = bugs * bug_rate;
  printf("You are expected to have %f bugs.\n",
          expected_bugs);

  double part_of_universe = expected_bugs / universe_of_defects;
  printf("That is only a %e portion of the univers.\n",
          part_of_universe);

  // this makes no sense, just a demo of something weird
  char nul_byte = '\0';
  int care_percentage = bugs * nul_byte;
  printf("Which means you should care %d%%.\n",
         care_percentage);

  // experiments of a mad scientist
  printf("what the hell is that nul byte?\n");
  printf("with %%s it is: %s\n", nul_byte);
  printf("with %%c it is: %c\n", nul_byte);

  long really_long = 1234567890L;
  unsigned long wat_really_long = 1234567890L;
  printf("yo %ld\n", really_long);
  printf("yo %ld\n", wat_really_long);

  really_long *= 1000;
  wat_really_long *= 1000;
  printf("yo %ld\n", really_long);
  printf("ya %ld\n", wat_really_long);

  really_long *= 1000;
  wat_really_long *= 1000;
  printf("yo %ld\n", really_long);
  printf("ya %ld\n", wat_really_long);

  really_long *= 1000;
  wat_really_long *= 1000;
  printf("yo %ld\n", really_long);
  printf("ya %ld\n", wat_really_long);

  really_long *= 1000;
  wat_really_long *= 1000;
  printf("yo %ld\n", really_long);
  printf("ya %ld\n", wat_really_long);

  really_long *= 1000;
  wat_really_long *= 1000;
  printf("yo %ld\n", really_long);
  printf("ya %ld\n", wat_really_long);

  really_long *= 1000;
  wat_really_long *= 1000;
  printf("yo %ld\n", really_long);
  printf("ya %ld\n", wat_really_long);

  printf("ok so I'll make a char and an int\n");
  
  char derp = 'A';
  int herp = 2;

  printf("the char: %c\n", derp);
  printf("the int: %i\n", herp);
  printf("the char as an int: %i\n", derp);
  printf("the int as a char: %c\n", herp);

  printf("now i do something INSANE\n");

  char wat = derp * herp;
  int wot = derp * herp;
  
  printf("wat: %c\n", wat);
  printf("wat: %i\n", wat);
  printf("wot: %c\n", wot);
  printf("wot: %i\n", wot);

  return 0;
}
