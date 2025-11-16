#include <stdio.h>
#include <stdlib.h>

#include "stack.h"

stack_errcodes_type StackDestroy (stack_type* stack)
{
    stack_errcodes_type errcode = StackVerify (stack, "stack_destroy.cpp", "StackDestroy");

    free (stack->data);

    return errcode;
}
