#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "stack.h"

// TODO SQRT,

int main ()
{
    stack_type stack;

    StackInit (&stack);

    printf (GREEN "passed initializing\n" COLOR_RESET);

    UserComands (&stack);

    // BreakStack (&stack);

    printf (GREEN "passed reading users commands\n" COLOR_RESET);

    StackDestroy (&stack);

    printf (GREEN "passed destroying stack\n" COLOR_RESET);

    return 0;
}

void PrintStack (stack_type* stack)
{
    assert (stack != NULL);

    for (size_t i = 0; i < stack->capacity; ++i)
        printf ("[%lg] ", stack->data[i]);

    printf ("\n");
}

