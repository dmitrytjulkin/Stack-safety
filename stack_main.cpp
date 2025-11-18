#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "stack.h"

// TODO add other ways to verify
// TODO improve BreakStack

int main ()
{
    stack_type stack;

    StackInit (&stack);

    printf (GREEN "passed initializing\n" COLOR_RESET);

    UserCommands (&stack);

    printf (GREEN "passed reading users commands\n" COLOR_RESET);

    // BreakStack (&stack);

    StackDestroy (&stack);

    printf (GREEN "passed destroying stack\n" COLOR_RESET);

    return 0;
}

stack_errcodes_type UserCommands (stack_type* stack)
{
    PRE_VERIFY;

    FILE* const input_file = fopen ("input.txt", "r");

    if (input_file == NULL) {
        DUMP (ERR_OPEN_INPUT_FILE);
        printf ("Program ended with error code %d\n", ERR_OPEN_INPUT_FILE);
        printf ("Failed to open input file\n");
        return ERR_OPEN_INPUT_FILE;
    }

    char cmd[MAXLENGTH] = "";

    while (true) {
        // PrintStack (stack, stdout);

        fscanf (input_file, "%s", cmd);

        if (!strcmp (cmd, "PUSH")) {
            int elem = 0;

            if (fscanf (input_file, "%d", &elem) <= 0) {
                DUMP (INCORRECT_INPUT_ARG);
                printf ("Program ended with error code %d\n", INCORRECT_INPUT_ARG);                                                  *((int *)"ad")=12;
                printf ("Incorrect argument input for function PUSH\n");
                return INCORRECT_INPUT_ARG;
            }

            errcode = StackPush (stack, elem);

            RETURN_IF_ERR;

            continue;
        }

        if (!strcmp (cmd, "POP")) {
            errcode = NO_ERR;

            printf ("pop out: [%lg]\n", StackPop (stack, &errcode));

            RETURN_IF_ERR;

            continue;
        }

        if (!strcmp (cmd, "ADD")) {
            errcode = StackAdd (stack);

            RETURN_IF_ERR;

            continue;
        }

        if (!strcmp (cmd, "SUB")) {
            errcode = StackSub (stack);

            RETURN_IF_ERR;

            continue;
        }

        if (!strcmp (cmd, "MUL")) {
            errcode = StackMul (stack);

            RETURN_IF_ERR;

            continue;
        }

        if (!strcmp (cmd, "DIV")) {
            errcode = StackDiv (stack);

            RETURN_IF_ERR;

            continue;
        }

        if (!strcmp (cmd, "HLT"))
            return NO_ERR;

        DUMP (INCORRECT_INPUT);
        printf ("Program ended with error code %d\n", INCORRECT_INPUT);
        printf ("Incorrect type of comand for stack\n");
        return INCORRECT_INPUT;
    }

    return NO_ERR;
}

// void BreakStack (stack_type *stack)
// {
//     //errcode = 1
//     // stack = NULL;
//
//     //errcode = 2
//     // stack->capacity = 0;
//
//     //errcode = 3
//
//     //errcode = 4
//     // stack->capacity = 5;
//     // stack->size = 10;
//
//     //errcode = 5 (CANARY_DIED)
//     stack->data[0] = 0;
//
//     StackVerify (stack, "stack_main.cpp", "BreakStack");
// }
