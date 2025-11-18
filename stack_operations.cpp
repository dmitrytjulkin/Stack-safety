#include <stdio.h>
#include <string.h>
#include <math.h>

#include "stack.h"

stack_errcodes_type StackResize (stack_type* stack) {
    PRE_VERIFY;

    stack->capacity += 10;

    stack->data = (double*) realloc (stack->data, (stack->capacity + 2) * sizeof(double));

    for (size_t i = stack->size + 1; i <= stack->capacity; ++i)
        stack->data[i] = POISON;

    stack->data[stack->capacity + 1] = CANARY2;

    POST_VERIFY;

    return NO_ERR;
}

stack_errcodes_type StackPush (stack_type* stack, double value)
{
    PRE_VERIFY;

    if (stack->size == stack->capacity - 1)
        errcode = StackResize (stack);

    ++stack->size;
    stack->data[stack->size] = value;

    POST_VERIFY;

    return NO_ERR;
}

double StackPop (stack_type* stack, stack_errcodes_type* errcode)
{
    if ((*errcode = StackVerify (stack, __FILE__, __func__, __LINE__)) != NO_ERR)
        return 0;

    if (stack->size == 0) {
        DUMP (CANARY_IN_DANGER);
        printf ("Program ended with error code %d\n", CANARY_IN_DANGER);
        printf ("Canary is about to be changed\n");
        *errcode = CANARY_IN_DANGER;

        return 0;
    }

    double last_elem = stack->data[stack->size];

    stack->data[stack->size] = POISON;
    --stack->size;

    POST_VERIFY;

    return last_elem;
}

stack_errcodes_type StackAdd (stack_type* stack)
{
    PRE_VERIFY;

    double a = StackPop (stack, &errcode);
    double b = StackPop (stack, &errcode);

    RETURN_IF_ERR;

    errcode = StackPush (stack, b + a);

    POST_VERIFY;

    return NO_ERR;
}

stack_errcodes_type StackSub (stack_type* stack)
{
    PRE_VERIFY;

    double a = StackPop (stack, &errcode);
    double b = StackPop (stack, &errcode);

    RETURN_IF_ERR;

    errcode = StackPush (stack, b - a);

    POST_VERIFY;

    return NO_ERR;
}

stack_errcodes_type StackMul (stack_type* stack)
{
    PRE_VERIFY;

    double a = StackPop (stack, &errcode);
    double b = StackPop (stack, &errcode);

    RETURN_IF_ERR;

    errcode = StackPush (stack, a * b);

    POST_VERIFY;

    return NO_ERR;
}

stack_errcodes_type StackDiv (stack_type* stack)
{
    PRE_VERIFY;

    double a = StackPop(stack, &errcode);
    double b = StackPop(stack, &errcode);

    RETURN_IF_ERR;

    if (IsZero(a)) {
        DUMP (DIVISION_BY_ZERO);
        printf ("Program ended with error code %d\n", DIVISION_BY_ZERO);
        printf ("Division by zero\n");
        return DIVISION_BY_ZERO;
    }

    errcode = StackPush(stack, b / a);

    POST_VERIFY;

    return NO_ERR;
}

