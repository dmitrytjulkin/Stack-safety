#include <stdio.h>
#include <stdlib.h>

#include "stack.h"

stack_errcodes_type StackInit (stack_type* stack)
{
    stack->capacity = 5;
    stack->data = (double*) calloc (stack->capacity + 2, sizeof (double));
    stack->size = 0;

    stack->data[0] = CANARY1;

    for (size_t i = 1; i <= stack->capacity; ++i) {
        stack->data[i] = POISON;
    }

    stack->data[stack->capacity + 1] = CANARY2;

    stack_errcodes_type errcode = NO_ERR;

    if ((errcode = StackVerify (stack, "stack_init.cpp", "StackInit")) != 0)
        return errcode;

    return errcode;
}
