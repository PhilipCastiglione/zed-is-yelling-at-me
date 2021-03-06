#include <stdio.h>

int main(int argc, char *argv[])
{
  int areas[] = {10, 12, 13, 14, 20};
  char name[] = "Philip";
  char full_name[] = {
    'P', 'h', 'i', 'l', 'i', 'p',
    ' ', 'L', '.', ' ',
    'C', 'a', 's', 't', 'i', 'g', 'l', 'i', 'o', 'n', 'e', '\0'
    //'C', 'a', 's', 't', 'i', 'g', 'l', 'i', 'o', 'n', 'e' // sweet error here
  };
  //int areas[] = {10, 12, 13, 14, 20};
  //char name[] = "Philip";

  // WARNING: On some systems, you may have to change the
  // %ld in this code to a %u since it will use unsigned ints
  printf("The size of an int: %ld\n", sizeof(int));
  printf("The size of areas (int[]); %ld\n",
          sizeof(areas));
  printf("The number of ints in areas: %ld\n",
          sizeof(areas) / sizeof(int));
  printf("The first area is %d, the 2nd %d.\n",
          areas[0], areas[1]);
          //areas[10], areas[1]);
          //name[20], areas[1]);

  printf("The size of a char: %ld\n", sizeof(char));
  printf("The size of name (char[]): %ld\n",
          sizeof(name));
  printf("The number of chars: %ld\n",
          sizeof(name) / sizeof(char));

  printf("The size of full_name (char[]): %ld\n",
          sizeof(full_name));
  printf("The number of chars: %ld\n",
          sizeof(full_name) / sizeof(char));

  printf("name=\"%s\" and full_name=\"%s\"\n",
          name, full_name);

  printf("reassign areas[0]\n");
  printf("before: %d\n", areas[0]);

  areas[0] = 100;

  printf("after: %d\n", areas[0]);

  //printf("out of range assignment: \n");
  //printf("before: %d\n", areas[12]);

  //areas[12] = 200;

  //printf("after: %d\n", areas[12]);
  // terrifyingly, the above WORKS
  // but am I changing some random bits of memory??

  printf("name[1]: %d\n", name[1]);
  printf("areas[1]: %d\n", areas[1]);
  areas[1] = name[1];
  printf("name[1]: %d\n", name[1]);
  printf("areas[1]: %d\n", areas[1]);

  return 0;
}
