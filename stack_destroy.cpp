#include <stdio.h>
#include <assert.h>

#include "stack.h"

void StackDestroy (stack_type* stack)
{
    StackOk (stack, "StackDestroy");

    free (stack->data);
}
