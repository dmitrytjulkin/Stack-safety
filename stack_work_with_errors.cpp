#include <stdio.h>
#include <math.h>

#include "stack.h"

bool IsZero (double a);

stack_errcodes_type StackVerify (stack_type* stack, const char* filename, const char* funcname)
{
    if (stack == NULL) {
        StackDump (stack, NULL_ERR, filename, funcname);
        printf ("Program ended with error code %d\n", NULL_ERR);
        printf ("Stack pointer = 0\n");
        return NULL_ERR;
    }

    if (stack->capacity == 0) {
        StackDump (stack, NO_SPACE_ERR, filename, funcname);
        printf ("Program ended with error code %d\n", NO_SPACE_ERR);
        printf ("Stack capacity equal 0\n");
        return NO_SPACE_ERR;
    }

    if (stack->size > stack->capacity) {
        StackDump (stack, OVERFLOWED, filename, funcname);
        printf ("Program ended with error code %d\n", OVERFLOWED);
        printf ("Stack size bigger than stack capacity\n");
        return OVERFLOWED;
    }

    if (!IsZero(stack->data[0] - CANARY1) ||
        !IsZero(stack->data[stack->capacity - 1] - CANARY2)) {
            StackDump (stack, CANARY_DIED, filename, funcname);
            printf ("Program ended with error code %d\n", CANARY_DIED);
            printf ("Canary was changed\n");
            return CANARY_DIED;
    }

    return NO_ERR;
}

stack_errcodes_type StackDump (stack_type* stack, int errcode,
                               const char* filename, const char* funcname)
{
    FILE* fp = fopen ("errcode_output.txt", "a");

    if (fp == NULL) {
        // is it necessary to do stackdump here?
        printf ("Program ended with error code %d\n", ERR_OPEN_ERRCODE);
        printf ("Failed to open file for error codes\n");
        return ERR_OPEN_ERRCODE;
    }

    fprintf (fp, "StackDump called from file %s, from function %s\n", filename, funcname);
    fprintf (fp, "with error code %d\n", errcode);
    fprintf (fp, "Stack size: %zu\n", stack->size);
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
    stack_errcodes_type errcode = NO_ERR;

    for (size_t i = 0; i < stack->capacity; ++i)
        fprintf (fp, "[%lg] ", stack->data[i]);

    fprintf (fp, "\n\n");

    return errcode;
}
