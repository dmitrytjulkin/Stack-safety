#include <stdio.h>
#include <assert.h>

#include "stack.h"

stack_errcodes_type StackPush (stack_type* stack, int value)
{
    if (stack->size == stack->capacity) {
        stack->capacity += 10;
        stack->data = (int*) realloc (stack->data, stack->capacity * sizeof(int));
    }

    stack->data[stack->size++] = value;

    return NO_ERR;
}

int* StackPop (stack_type* stack)
{
    --stack->size;

    int* a = &stack->data[stack->size];
    printf ("a = %d\n", *a);

    stack->data[stack->size] = 0;

    return a;
}

stack_errcodes_type StackAdd (stack_type* stack)
{
    assert (stack != NULL);

    stack->data[stack->size - 2] += stack->data[stack->size - 1];

    stack->data[stack->size - 1] = 0;

    --stack->size;

    return NO_ERR;
}

stack_errcodes_type StackSub (stack_type* stack)
{
    assert (stack != NULL);

    stack->data[stack->size - 2] -= stack->data[stack->size - 1];

    stack->data[stack->size - 1] = 0;

    --stack->size;

    return NO_ERR;
}

stack_errcodes_type StackMul (stack_type* stack)
{
    assert (stack != NULL);

    stack->data[stack->size - 2] *= stack->data[stack->size - 1];

    stack->data[stack->size - 1] = 0;

    --stack->size;

    return NO_ERR;
}

stack_errcodes_type StackDiv (stack_type* stack)
{
    assert (stack != NULL);

    stack->data[stack->size - 2] /= stack->data[stack->size - 1];

    stack->data[stack->size - 1] = 0;

    --stack->size;

    return NO_ERR;
}
