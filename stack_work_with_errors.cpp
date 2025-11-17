#include <stdio.h>
#include <math.h>
#include <assert.h>

#include "stack.h"

bool IsZero (double a);
void PrintErrcodes (stack_errcodes_type errcode, FILE* fp);

stack_errcodes_type StackVerify (stack_type* stack, const char* filename, const char* funcname)
{
    stack_errcodes_type errcode = NO_ERR;

    if (stack == NULL) {
        printf ("Program ended with error code %d\n", NULL_ERR);
        printf ("Stack pointer = 0\n");
        errcode = (stack_errcodes_type) (errcode + NULL_ERR);
    }

    if (stack->capacity == 0) {
        StackDump (stack, NO_SPACE_ERR, filename, funcname);
        printf ("Program ended with error code %d\n", NO_SPACE_ERR);
        printf ("Stack capacity equal 0\n");
        errcode = (stack_errcodes_type) (errcode + NO_SPACE_ERR);
    }

    if (stack->size > stack->capacity) {
        StackDump (stack, OVERFLOWED, filename, funcname);
        printf ("Program ended with error code %d\n", OVERFLOWED);
        printf ("Stack size bigger than stack capacity\n");
        errcode = (stack_errcodes_type) (errcode + OVERFLOWED);
    }

    if (!IsZero(stack->data[0] - CANARY1) ||
        !IsZero(stack->data[stack->capacity + 1] - CANARY2)) {
            StackDump (stack, CANARY_DIED, filename, funcname);
            printf ("Program ended with error code %d\n", CANARY_DIED);
            printf ("Canary was changed\n");
            errcode = (stack_errcodes_type) (errcode + CANARY_DIED);
    }

    for (size_t i = stack->size + 1; i <= stack->capacity; ++i) {
        if (!IsZero(stack->data[i] - POISON)) {
            StackDump (stack, POISON_ERROR, filename, funcname);
            printf ("Program ended with error code %d\n", POISON_ERROR);
            printf ("Stack's cell wasn't poisoned\n");
            errcode = (stack_errcodes_type) (errcode + POISON_ERROR);

            break;
        }
    }

    if (IsZero(errcode != NO_ERR))
        StackDump (stack, errcode, filename, funcname);

    return errcode;
}

stack_errcodes_type StackDump (stack_type* stack, stack_errcodes_type errcode,
                               const char* filename, const char* funcname)
{
    FILE* fp = fopen ("errcode_output.txt", "a");

    if (fp == NULL) {
        printf ("Program ended with error code %d\n", ERR_OPEN_ERR_FILE);
        printf ("Failed to open file for error codes\n");
        return ERR_OPEN_ERR_FILE;
    }

    fprintf (fp, "StackDump called from file %s, from function %s\n", filename, funcname);
    fprintf (fp, "with error code(s):\n");

    PrintErrcodes (errcode, fp);

    fprintf (fp, "\nStack size: %zu\n", stack->size);
    fprintf (fp, "Stack capacity: %zu\n", stack->capacity);
    fprintf (fp, "Location of stack [%p]\n", &stack);
    fprintf (fp, "Location of stack data [%p]\n\n", &stack->data);

    if (stack != NULL) {
        fprintf (fp, "Stack data:\n");
        PrintStack (stack, fp);
    }

    fclose (fp);

    return NO_ERR;
}

bool IsZero (double a)
{
    if (fabs(a) < 1e-4)
        return 1;

    return 0;
}

stack_errcodes_type PrintStack (stack_type* stack, FILE* fp)
{
    assert (stack != NULL);
    assert (fp != NULL);

    stack_errcodes_type errcode = NO_ERR;

    for (size_t i = 1; i <= stack->capacity; ++i) {
        if (IsZero(stack->data[i] - POISON))
            fprintf (fp, "[ ] ");

        else
            fprintf (fp, "[%lg] ", stack->data[i]);
    }

    fprintf (fp, "\n\n");

    return errcode;
}

void PrintErrcodes (stack_errcodes_type errcode, FILE* fp) {
    int order = 1;

    while (errcode != 0) {
        if (errcode % 2 != 0)
            fprintf (fp, "%d ", errcode % 2 * order);

        order *= 2;
        errcode = (stack_errcodes_type) (errcode / 2);
    }
}
