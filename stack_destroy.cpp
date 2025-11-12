#include <stdio.h>
#include <assert.h>

#include "stack.h"

void StackDestroy (stack_type* stack)
{
    free (stack->data);
    // printf ("OK\n");
}
