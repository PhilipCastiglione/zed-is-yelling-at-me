#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

// some sweet new struct thing, looks like a declaration with some attrs
struct Person {
  char *name;
  int age;
  int height;
  int weight;
};

// a function, with a return of type struct Person pointer, called Person_create
struct Person *Person_create(char *name, int age, int height, int weight)
{
  // a struct Person pointer called who, with a memory allocation of a given size
  struct Person *who = malloc(sizeof(struct Person));
  // which apparently is enough to not be NULL
  assert(who != NULL);

  // i guess giving values to the previously declared attributes
  who->name = strdup(name); // what's with strdup; must relate to being array of chars
  who->age = age;
  who->height = height;
  who->weight = weight;

  // remember this is just a pointer to the person we are returning
  // really not sure about the choice of var name but anyway i get it
  return who;
}

// function with no return value called Person_destroy, takes a pointer to a person
void Person_destroy(struct Person *who)
{
  // assert must be some kind of test, to make sure we didn't pass NULL?
  // I guess that might be bad, no idea what free does, but free(NULL) might be bad
  // should see what assert(0) does to find out what failure means
  assert(who != NULL);
  //POSTSCRIPT guess passing asserts don't do anything

  // wtf why do we only need to free the name
  // is this something to do with name being an array of chars
  // or is it Zed not demonstrating everything
  // probably the former
  free(who->name);
  //POSTSCRIPT it's because strdup is duplication! a whole new mem alloc
  //free(who->name);
  free(who);
}

// function with no return value called Person_print that takes a pointer to a person
void Person_print(struct Person *who)
{
  // nothing fancy
  printf("Name: %s\n", who->name);
  printf("\tAge: %d\n", who->age);
  printf("\tHeight: %d\n", who->height);
  printf("\tWeight: %d\n", who->weight);
}

int main(int argc, char *argv[])
{
  //ZED make two people structures
  struct Person *joe = Person_create(
          "Joe Shmalex", 32, 64, 140);

  struct Person *frank = Person_create(
          "Frank Shmlank", 20, 72, 180);

  //ZED print them out and where they are in memory
  printf("Joe is at memory location %p:\n", joe);
  Person_print(joe);

  printf("Frank is at memory location %p:\n", frank);
  Person_print(frank);

  //ZED make everyone age 20 years and print them again
  // since zed says make everyone 20, += must do something weird here
  // must allocate from 0?
  joe->age += 20;
  //POSTSCRIPT no this does exactly what you'd expect and zed's comment is just weird
  //POSTSCRIPT OH as in age the verb silly
  // wait except does this mean height will be -2?
  joe->height -= 2;
  //POSTSCRIPT no this does exactly what you'd expect
  joe->weight += 40;
  Person_print(joe);

  frank->age += 20;
  frank->weight +=20;
  Person_print(frank);

  //ZED destroy them both so we clean up
  Person_destroy(joe);
  Person_destroy(frank);
  //Person_destroy(frank);

  //Person_destroy(NULL);
  //Person_print(NULL);
  return 0;
}
