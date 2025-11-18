#include <stdio.h>
#include <stdlib.h>

#include "stack.h"

stack_errcodes_type StackInit (stack_type* stack)
{
    if (stack == NULL) {
        printf ("Program ended with error code %d\n", STACK_NULL_ERR);
        printf ("Stack pointer = 0\n");
    }

    stack->capacity = 5;
    stack->data = (double*) calloc (stack->capacity + 2, sizeof (double));
    stack->size = 0;

    stack->data[0] = CANARY1;

    for (size_t i = 1; i <= stack->capacity; ++i)
        stack->data[i] = POISON;

    stack->data[stack->capacity + 1] = CANARY2;

    stack_errcodes_type errcode = NO_ERR;

    errcode = StackVerify (stack, __FILE__, __func__, __LINE__);

    return errcode;
}
