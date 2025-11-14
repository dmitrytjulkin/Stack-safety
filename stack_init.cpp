#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "stack.h"

stack_errcodes_type StackInit (stack_type* stack)
{
    assert (stack != NULL);

    stack->capacity = 5;
    stack->data = (double*) calloc (stack->capacity, sizeof (double));
    stack->size = 1;

    stack->data[0] = CANARY;
    stack->data[stack->capacity - 1] = CANARY;

    StackOk (stack, "StackInit");

    return NO_ERR;
}
