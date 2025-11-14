#include <stdio.h>
#include <math.h>

const double comparable_const = 1e-4;

#include "stack.h"

bool CheckDoubleEquality (double a, double b);

void BreakStack (stack_type *stack)
{
    //errcode = 1
    // stack = NULL;

    //errcode = 2
    // stack->capacity = 0;

    //errcode = 3

    //errcode = 4
    // stack->capacity = 5;
    // stack->size = 10;

    //errcode = 5
    stack->data[0] = 0;

    StackOk (stack, "BreakStack");
}

stack_errcodes_type StackOk (stack_type* stack, const char* name_of_function)
{
    stack_errcodes_type errcode = NO_ERR;

    errcode = StackVerify (stack);
    StackDump (stack, errcode, name_of_function);

    return errcode;
}

stack_errcodes_type StackVerify (stack_type* stack)
{
    if (stack == NULL) return NULL_ERR;

    if (stack->capacity == 0) return NO_SPACE_ERR;

    if (stack->size > stack->capacity) return OVERFLOWED;

    if (!CheckDoubleEquality(stack->data[0], CANARY) ||
        !CheckDoubleEquality(stack->data[stack->capacity - 1], CANARY))
        return CANARY_DIED;

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

bool CheckDoubleEquality (double a, double b)
{
    double diff = fabs(a - b);

    if(diff <= comparable_const)
        return true;

    else
        return false;
}

