#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "stack.h"

stack_errcodes_type UserCmds (stack_type* stack);

int main ()
{
    stack_type stack;

    StackInit (&stack);

    printf (GREEN "passed initializing\n" COLOR_RESET);

    int err = UserCmds (&stack);

    PrintStack (&stack);

    printf (GREEN "passed reading users commands\n" COLOR_RESET);

    StackDestroy (&stack);

    printf (GREEN "passed destroying stack\n" COLOR_RESET);

    return 0;
}

stack_errcodes_type UserCmds (stack_type* stack)
{
    FILE* input_file = fopen ("input.txt", "r");
    assert (input_file != NULL);

    char cmd[MAXLENGTH] = "";

    while (true) {
        if (fscanf (input_file, "%s", cmd) <= 0) {
            printf ("incorrect comand input\n");

            return BAD_INPUT;
        }

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

        if (!strcmp (cmd, "HLT")) {
            return NO_ERR;
        }

        printf ("incorrect comand input\n");
        return BAD_INPUT;
        }

    return NO_ERR;
}

void PrintStack (stack_type* stack)
{
    assert (stack != NULL);

    for (size_t i = 0; i < stack->capacity; ++i)
        printf ("[%d] ", stack->data[i]);

    printf ("\n");
}
