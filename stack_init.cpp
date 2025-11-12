#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "stack.h"

stack_errcodes_type StackInit (stack_type* stack)
{
    assert (stack != NULL);

    stack->capacity = 5;
    stack->data = (int*) calloc (stack->capacity, sizeof (int));
    stack->size = 0;

    stack_errcodes_type errcode = StackVerify (stack);
    // StackDump (stack, errcode, "StackInit");

    return errcode;
}
