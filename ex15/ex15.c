#include <stdio.h>

int sweet_function(int *full_on_pointer)
{
  return *full_on_pointer;
}

//int main(int argc, char *argv[])
//{
  //int a = 5;
  //int *b = &a;
  //printf("%p\n", b); // prints out an awesome memory address
  //return 0;
//}

//int dank(int argc, char *argv[])
int main(int argc, char *argv[])
{
  int not_yet_a_pointer = 3;
  //int check_it = sweet_function(&not_yet_a_pointer);
  int *totally_a_pointer = &not_yet_a_pointer;
  int check_it = sweet_function(totally_a_pointer);
  printf("CHECK! IT! OUT!: %d\n", check_it);

  // create two arrays we care about
  int ages[] = {23, 43, 12, 89, 2};
  char *names[] = {
    "Alan", "Frank",
    "Mary", "John", "Lisa"
  };

  // safely get the size of ages
  int count = sizeof(ages) / sizeof(int);
  int i = 0;

  // first way using indexing
  for(i = 0; i < count; i++) {
    printf("%s, has %d years alive.\n",
            names[i], ages[i]);
  }

  printf("---\n");

  // first way rewritten to use pointers
  // omg
  for(i = 0; i < count; i++) {
    printf("%d ok\n", ages[i]);
    int *age = &ages[i];
    printf("%p wow\n", age);
    printf("%d woa\n", *age);

    printf("%s aok\n", names[i]);
    char *name = names[i];
    printf("%p awow\n", name);
    printf("%s awoa\n", name);
    printf("%c awoa\n", *name);

    printf("%s, has %d years not dead (yet).\n",
            name, *age);
  }

  // setup the pointers to the start of the arrays
  int *cur_age = ages;
  char **cur_name = names;
  //int *wat = (int*) names[0];
  //printf("OMG WAT: %p\n", wat);
  //int **wot = (int**) names;
  //printf("OMG WAO: %p\n", wot);

  // from this, it looks like a pointer is a reference to the start of
  // a block of memory, somehow in an integer type format?
  // so you can take that reference, add a number of bytes, and then
  // get to the next reference.
  // given that ages is an array of ints, they must be stored in
  // consecutive int sized blocks of memory, so if you reference the
  // start, then add an int sized block to the reference, you get to
  // the start of the reference of the next int, if you pointer THAT
  // with * as below, you just get a reference to taht value. boom.

  // second way using pointers
  for(i = 0; i < count; i++) {
  //for(i = count; i > 0; i--) {
    printf("%s is %d years old.\n",
            //*(cur_name+i), *(cur_age+i));
            *(cur_name + i), *(cur_age + i)); // operators need spaces pls
            //*(cur_name + i - 1), *(cur_age + i - 1));
  }

  printf("---\n");

  // second way rewritten to use arrays
  // easy now
  int age_yo;
  char *name_yo;
  for(i = 0; i < count; i++) {
    age_yo = *(cur_age + i);
    name_yo = *(cur_name + i);
    printf("don't even care %d\n",
            age_yo);
    printf("for reals %s\n",
            name_yo);
  }
  
  // so this is kind of wack. somehow, you can also array reference the pointer,
  // similarly to how you can add an integer to the pointer, though note that
  // when you array reference the pointer you immediately get the value of the
  // memory in the address referred to, without having to use the * operator.
  // so adding an integer to a int * will give you a new int *, but referencing
  // an int * with int*[n] will get you *(int* + n).

  // third way, pointers are just arrays
  for(i = 0; i < count; i++) {
    printf("%s is %d years old again.\n",
            cur_name[i], cur_age[i]);
  }

  printf("---\n");

  // basically, wtf. here we assign an int to int * (and the char thing we
  // brush off as magic because chars are actually just short ints it seems
  // which is still blow our minds, plus it's a 2D array, but ignoring those
  // things it's actually basically the same I think). then we do math on
  // the int * in our sweet loop, and just reference the value with the *
  // operator in the printf. Actually it's not really magic when you step
  // through. This is closer to the first pointer example in that we extract
  // the value from the reference with * rather than [], and we do math on
  // the reference, just that we are doing math on the reference in the loop.
  // otherwise it's actually quite similar to that example. oh also obviously
  // the incrementation is moving the references forward by one int block of
  // memory at a time which seems awfully convenient. I'm not sure how this
  // works for both reference types given that one is an int and the other
  // is a 2D array of chars...

  // fourth way with pointers in a stupid complex way
  for(cur_name = names, cur_age = ages;
        (cur_age - ages) < count;
        cur_name++, cur_age++)
  {
    printf("%s lived %d years so far.\n",
            *cur_name, *cur_age);
  }

  int forgot = 5;
  printf("%d\n", forgot--);
  printf("%d\n", --forgot);
  printf("%d\n", forgot);

  return 0;
}
