#include <stdio.h>
#include <stdlib.h>

struct Stack {
  int ptr;
  int *contents;
  int size;
};

struct Stack *Stack_new(int size)
{
  struct Stack *stack = malloc(sizeof(struct Stack));
  stack->ptr = 0;
  stack->contents = malloc(sizeof(int) * size);
  stack->size = size;
  return stack;
}

struct Stack *push(struct Stack *stack, int val)
{
  if(stack->ptr < stack->size) {
    stack->contents[stack->ptr] = val;
    stack->ptr++;
  }

  return stack;
}

int pop(struct Stack *stack)
{
  if(stack->ptr > 0) {
    int val = stack->contents[stack->ptr];
    stack->ptr--;
    return val;
  } else {
    return -1;
  }
}

void Stack_print(struct Stack *stack)
{
  for(int i = 0; i < stack->ptr; i++) {
    printf("%d,", stack->contents[i]);
  }
  printf("\n");
}

int main(int argc, char *argv[])
{
  struct Stack *s = Stack_new(5);
  push(s, 5);
  push(s, 3);
  push(s, 2);
  pop(s);
  Stack_print(s);

  return 0;
}
