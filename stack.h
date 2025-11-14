#define GREEN   "\x1b[32m"
#define COLOR_RESET   "\x1b[0m"

const double CANARY =  0x123456789ABCDEF1;

struct stack_type {
        size_t size;
        size_t capacity;
        double* data;
};

enum stack_errcodes_type {
        NO_ERR,
        NULL_ERR,
        NO_SPACE_ERR,
        BAD_INPUT,
        OVERFLOWED,
        CANARY_DIED
};

const int MAXLENGTH = 10;

void PrintStack (stack_type* stack);

stack_errcodes_type StackInit (stack_type* stack);

stack_errcodes_type UserComands (stack_type* stack);
stack_errcodes_type StackPush (stack_type* stack, int value);
double* StackPop (stack_type* stack);
stack_errcodes_type StackAdd (stack_type* stack);
stack_errcodes_type StackSub (stack_type* stack);
stack_errcodes_type StackMul (stack_type* stack);
stack_errcodes_type StackDiv (stack_type* stack);

void StackDestroy (stack_type* stack);

void BreakStack (stack_type *stack);
stack_errcodes_type StackOk (stack_type* stack, const char* name_of_function);
stack_errcodes_type StackVerify (stack_type* stack);
void StackDump (stack_type* stack, stack_errcodes_type errcode, const char* name_of_function);
