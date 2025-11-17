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

stack_errcodes_type UserComands (stack_type* stack)
{
    stack_errcodes_type errcode = NO_ERR;

    if ((errcode = StackVerify (stack, "stack_main.cpp", "UserComands")) != NO_ERR)
        return errcode;

    FILE* const input_file = fopen ("input.txt", "r");

    if (input_file == NULL) {
        StackDump (stack, ERR_OPEN_INPUT_FILE, "stack_main.cpp", "UserComands");
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
                StackDump (stack, INCORRECT_INPUT_ARG, "stack_main.cpp", "UserComands");
                printf ("Program ended with error code %d\n", INCORRECT_INPUT_ARG);
                printf ("Incorrect argument input for function PUSH\n");
                return INCORRECT_INPUT_ARG;
            }

            StackPush (stack, elem);

            continue;
        }

        if (!strcmp (cmd, "POP")) {
            errcode = NO_ERR;
            printf ("pop out: [%lg]\n", StackPop (stack, &errcode));

            if (errcode != NO_ERR)
                break;

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

        if (!strcmp (cmd, "HLT"))
            return NO_ERR;

        StackDump (stack, INCORRECT_INPUT, "stack_main.cpp", "UserComands");
        printf ("Program ended with error code %d\n", INCORRECT_INPUT);
        printf ("Incorrect type of comand for stack\n");
        return INCORRECT_INPUT;
    }

    return NO_ERR;
}
