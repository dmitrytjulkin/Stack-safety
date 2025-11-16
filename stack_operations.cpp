#include <stdio.h>
#include <string.h>
#include <math.h>

#include "stack.h"

stack_errcodes_type StackPush (stack_type* stack, int value)
{
    stack_errcodes_type errcode = NO_ERR;

    if ((errcode = StackVerify (stack, "stack_operations.cpp", "StackPush")) != 0)
        return errcode;

    if (stack->size == stack->capacity - 1) {
        stack->capacity += 10;

        stack->data = (double*) realloc (stack->data, stack->capacity * sizeof(double));

        stack->data[stack->capacity - 1] = CANARY2;
    }

    stack->data[stack->size++] = value;

    if ((errcode = StackVerify (stack, "stack_operations.cpp", "StackPush")) != 0)
        return errcode;

    return NO_ERR;
}

stack_errcodes_type StackPop (stack_type* stack)
{
    stack_errcodes_type errcode = NO_ERR;

    if ((errcode = StackVerify (stack, "stack_operations.cpp", "StackPop")) != 0)
        return errcode;

    double* last_elem = &stack->data[stack->size - 1];
    printf ("pop out: [%lg]\n", *last_elem);

    --stack->size;
    stack->data[stack->size] = 0;

    if ((errcode = StackVerify (stack, "stack_operations.cpp", "StackPop")) != 0)
        return errcode;

    return NO_ERR;
}

stack_errcodes_type StackAdd (stack_type* stack)
{
    stack_errcodes_type errcode = NO_ERR;

    if ((errcode = StackVerify (stack, "stack_operations.cpp", "StackAdd")) != 0)
        return errcode;

    stack->data[stack->size - 2] += stack->data[stack->size - 1];
    stack->data[stack->size - 1] = 0;
    --stack->size;

    if ((errcode = StackVerify (stack, "stack_operations.cpp", "StackAdd")) != 0)
        return errcode;

    return NO_ERR;
}

stack_errcodes_type StackSub (stack_type* stack)
{
    stack_errcodes_type errcode = NO_ERR;

    if ((errcode = StackVerify (stack, "stack_operations.cpp", "StackSub")) != 0)
        return errcode;

    stack->data[stack->size - 2] -= stack->data[stack->size - 1];
    stack->data[stack->size - 1] = 0;
    --stack->size;

    if ((errcode = StackVerify (stack, "stack_operations.cpp", "StackSub")) != 0)
        return errcode;

    return NO_ERR;
}

stack_errcodes_type StackMul (stack_type* stack)
{
    stack_errcodes_type errcode = NO_ERR;

    if ((errcode = StackVerify (stack, "stack_operations.cpp", "StackMul")) != 0)
        return errcode;

    stack->data[stack->size - 2] *= stack->data[stack->size - 1];
    stack->data[stack->size - 1] = 0;
    --stack->size;

    if ((errcode = StackVerify (stack, "stack_operations.cpp", "StackMul")) != 0)
        return errcode;

    return NO_ERR;
}

stack_errcodes_type StackDiv (stack_type* stack)
{
    stack_errcodes_type errcode = NO_ERR;

    if ((errcode = StackVerify (stack, "stack_operations.cpp", "StackDiv")) != 0)
        return errcode;

    stack->data[stack->size - 2] /= stack->data[stack->size - 1];
    stack->data[stack->size - 1] = 0;
    --stack->size;

    if ((errcode = StackVerify (stack, "stack_operations.cpp", "StackDiv")) != 0)
        return errcode;

    return NO_ERR;
}

stack_errcodes_type StackSqrt (stack_type* stack)
{
    stack_errcodes_type errcode = NO_ERR;

    if ((errcode = StackVerify (stack, "stack_operations.cpp", "StackSqrt")) != 0)
        return errcode;

    stack->data[stack->size - 1] = sqrt (stack->data[stack->size - 1]);

    if ((errcode = StackVerify (stack, "stack_operations.cpp", "StackSqrt")) != 0)
        return errcode;

    return NO_ERR;
}
