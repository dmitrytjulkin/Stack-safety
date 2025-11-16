#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "stack.h"

int main ()
{
    stack_type stack;

    StackInit (&stack);

    printf (GREEN "passed initializing\n" COLOR_RESET);

    UserComands (&stack);

    printf (GREEN "passed reading users commands\n" COLOR_RESET);

    // BreakStack (&stack);

    StackDestroy (&stack);

    printf (GREEN "passed destroying stack\n" COLOR_RESET);

    return 0;
}

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

    //errcode = 5 (CANARY_DIED)
    stack->data[0] = 0;

    StackVerify (stack, "stack_main.cpp", "BreakStack");
}

stack_errcodes_type UserComands (stack_type* stack)
{
    stack_errcodes_type errcode = NO_ERR;

    if ((errcode = StackVerify (stack, "stack_main.cpp", "UserComands")) != 0)
        return errcode;

    FILE* input_file = fopen ("input.txt", "r");
    assert (input_file != NULL);

    char cmd[MAXLENGTH] = "";

    while (true) {
        // PrintStack (stack);

        if (fscanf (input_file, "%s", cmd) <= 0) {
            printf ("incorrect comand input\n");

            return BAD_INPUT;
        }

        // TODO Switch

        if (!strcmp (cmd, "PUSH")) {
            int elem = 0;

            if (fscanf (input_file, "%d", &elem) <= 0) {
                printf ("incorrect argument input for PUSH\n");

                return BAD_INPUT;
            }

            StackPush (stack, elem);

            continue;
        }

        if (!strcmp (cmd, "POP")) {
            StackPop (stack);

            continue;
        }

        if (!strcmp (cmd, "ADD")) {
            StackAdd (stack);

            continue;
        }

        if (!strcmp (cmd, "SUB")) {
            StackSub (stack);

            continue;
        }

        if (!strcmp (cmd, "MUL")) {
            StackMul (stack);

            continue;
        }

        if (!strcmp (cmd, "DIV")) {
            StackDiv (stack);

            continue;
        }

        if (!strcmp (cmd, "SQRT")) {
            StackSqrt (stack);

            continue;
        }

        if (!strcmp (cmd, "HLT")) {
            return NO_ERR;
        }

        printf ("incorrect comand input\n");
        return BAD_INPUT;
        }

    return NO_ERR;
}

