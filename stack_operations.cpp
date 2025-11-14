#include <stdio.h>
#include <assert.h>
#include <string.h>

#include "stack.h"

stack_errcodes_type UserComands (stack_type* stack)
{
    StackOk (stack, "UserComands");

    FILE* input_file = fopen ("input.txt", "r");
    assert (input_file != NULL);

    char cmd[MAXLENGTH] = "";

    while (true) {
        // PrintStack (stack);

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

stack_errcodes_type StackPush (stack_type* stack, int value)
{
    StackOk (stack, "StackPush");

    if (stack->size == stack->capacity - 1) {
        stack->capacity += 10;

        stack->data = (double*) realloc (stack->data, stack->capacity * sizeof(double));

        stack->data[stack->capacity - 1] = CANARY;
    }

    stack->data[stack->size++] = value;

    StackOk (stack, "StackPush");

    return NO_ERR;
}

double* StackPop (stack_type* stack)
{
    StackOk (stack, "StackPop");

    double* last_elem = &stack->data[stack->size - 1];
    printf ("pop out: [%lg]\n", *last_elem);

    --stack->size;
    stack->data[stack->size] = 0;

    StackOk (stack, "StackPop");

    return last_elem;
}

stack_errcodes_type StackAdd (stack_type* stack)
{
    StackOk (stack, "StackAdd");

    stack->data[stack->size - 2] += stack->data[stack->size - 1];
    stack->data[stack->size - 1] = 0;
    --stack->size;

    StackOk (stack, "StackPop");

    return NO_ERR;
}

stack_errcodes_type StackSub (stack_type* stack)
{
    StackOk (stack, "StackSub");

    stack->data[stack->size - 2] -= stack->data[stack->size - 1];
    stack->data[stack->size - 1] = 0;
    --stack->size;

    StackOk (stack, "StackSub");

    return NO_ERR;
}

stack_errcodes_type StackMul (stack_type* stack)
{
    StackOk (stack, "StackMul");

    stack->data[stack->size - 2] *= stack->data[stack->size - 1];
    stack->data[stack->size - 1] = 0;
    --stack->size;

    StackOk (stack, "StackMul");

    return NO_ERR;
}

stack_errcodes_type StackDiv (stack_type* stack)
{
    StackOk (stack, "StackDiv");

    stack->data[stack->size - 2] /= stack->data[stack->size - 1];
    stack->data[stack->size - 1] = 0;
    --stack->size;

    StackOk (stack, "StackDiv");

    return NO_ERR;
}
