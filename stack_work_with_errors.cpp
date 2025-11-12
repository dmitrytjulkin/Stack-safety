#include <stdio.h>

#include "stack.h"

stack_errcodes_type StackVerify (stack_type* stack)
{
    if (stack == NULL) return NULL_ERR;

    if (stack->size == 0) return NO_SPACE_ERR;

    return NO_ERR;
}

void StackDump (stack_type* stack, stack_errcodes_type errcode, const char* name_of_function)
{
    if (errcode == NO_ERR)
        return;

    printf ("StackDump called from %s\n"
            "ended with error code %d\n",
            name_of_function, errcode);

    PrintStack (stack);
}
