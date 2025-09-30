#include <stdio.h>
#include <stdlib.h>

struct stack_type {
        int* data;
        size_t size;
        size_t capacity;
} stack;

void StackInit (stack_type* stack);
void StackPush (stack_type* stack, int value);
int StackPop (stack_type* stack);
void StackDestroy (stack_type* stack);

int main ()
{
    StackInit (&stack);

    // printf ("size of stack = %zu,\nbut actual size = %zu\n", stack.capacity, stack.size);

    // stack.data[1] = 'Z';
    // printf ("data[1] = %c\n", *(stack.data + 1));

    StackPush (&stack, 10);

    // printf ("stack[%zu] = %d, size = %zu\n", stack.size - 1, stack.data[stack.size - 1], stack.size);

    int a = StackPop (&stack);

    // printf ("stack[%zu] = %d, size = %zu\n", stack.size, a, stack.size);

    StackDestroy (&stack);
//
    return 0;
}

void StackInit (stack_type* stack)
{
    stack->capacity = 5;
    stack->data = (int*) calloc (stack->capacity, sizeof (char));
    stack->size = 0;
}

void StackPush (stack_type* stack, int value)
{
    stack->data[stack->size++] = value;
}

int StackPop (stack_type* stack)
{
    --stack->size;

    int a = stack->data[stack->size];

    return a;
}

void StackDestroy (stack_type* stack)
{
    free (stack->data);
    printf ("OK\n");
}
