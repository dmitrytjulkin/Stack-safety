#include <stdio.h>
#include <string.h>
#include <math.h>

#include "stack.h"

stack_errcodes_type StackPush (stack_type* stack, double value)
{
    stack_errcodes_type errcode = NO_ERR;

    if ((errcode = StackVerify (stack, "stack_operations.cpp", "StackPush")) != 0)
        return errcode;

    if (stack->size == stack->capacity - 1) {
        stack->capacity += 10;

        stack->data = (double*) realloc (stack->data, (stack->capacity + 2) * sizeof(double));

        for (size_t i = stack->size + 1; i <= stack->capacity; ++i)
            stack->data[i] = POISON;

        stack->data[stack->capacity + 1] = CANARY2;
    }

    ++stack->size;
    stack->data[stack->size] = value;

    if ((errcode = StackVerify (stack, "stack_operations.cpp", "StackPush")) != 0)
        return errcode;

    return NO_ERR;
}

double StackPop (stack_type* stack, stack_errcodes_type* errcode)
{
    if ((*errcode = StackVerify (stack, "stack_operations.cpp", "StackPop")) != 0)
        return 0;

    double last_elem = stack->data[stack->size];

    stack->data[stack->size] = POISON;
    --stack->size;

    if ((*errcode = StackVerify (stack, "stack_operations.cpp", "StackPop")) != 0)
        return 0;

    return last_elem;
}

stack_errcodes_type StackAdd (stack_type* stack)
{
    stack_errcodes_type errcode = NO_ERR;

    if ((errcode = StackVerify (stack, "stack_operations.cpp", "StackAdd")) != 0)
        return errcode;

    StackPush(stack, StackPop(stack, &errcode) + StackPop(stack, &errcode));

    if ((errcode = StackVerify (stack, "stack_operations.cpp", "StackAdd")) != 0)
        return errcode;

    return NO_ERR;
}

stack_errcodes_type StackSub (stack_type* stack)
{
    stack_errcodes_type errcode = NO_ERR;

    if ((errcode = StackVerify (stack, "stack_operations.cpp", "StackSub")) != 0)
        return errcode;

    StackPush(stack, - StackPop(stack, &errcode) + StackPop(stack, &errcode));

    if ((errcode = StackVerify (stack, "stack_operations.cpp", "StackSub")) != 0)
        return errcode;

    return NO_ERR;
}

stack_errcodes_type StackMul (stack_type* stack)
{
    stack_errcodes_type errcode = NO_ERR;

    if ((errcode = StackVerify (stack, "stack_operations.cpp", "StackMul")) != 0)
        return errcode;

    StackPush(stack, StackPop(stack, &errcode) * StackPop(stack, &errcode));

    if ((errcode = StackVerify (stack, "stack_operations.cpp", "StackMul")) != 0)
        return errcode;

    return NO_ERR;
}

stack_errcodes_type StackDiv (stack_type* stack)
{
    stack_errcodes_type errcode = NO_ERR;

    if ((errcode = StackVerify (stack, "stack_operations.cpp", "StackDiv")) != 0)
        return errcode;

    StackPush(stack, 1 / StackPop(stack, &errcode) * StackPop(stack, &errcode));

    if ((errcode = StackVerify (stack, "stack_operations.cpp", "StackDiv")) != 0)
        return errcode;

    return NO_ERR;
}

