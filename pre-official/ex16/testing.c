#include <stdio.h>
#include <assert.h>

void wat()
{
  printf("in wat\n");
  printf("asserting 1\n");
  assert(1);
  printf("asserting 0\n");
  assert(0);

  // Assertion failed: (0), function wat, file testing.c, line 10.
  // fish: Job 3, './testing' terminated by signal SIGABRT (Abort)
}

int main(int argc, char *argv[])
{
  printf("in main\n");

  wat();

  printf("leaving main\n");

  return 0;
}
