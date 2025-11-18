#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "stack.h"

stack_errcodes_type StackDestroy (stack_type* stack)
{
    assert (stack != NULL);

    free (stack->data);

    return NO_ERR;
}
