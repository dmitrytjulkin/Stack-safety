#define GREEN   "\x1b[32m"
#define COLOR_RESET   "\x1b[0m"

const double CANARY1 =  0xEDAEDAEDAEDAEDAE;
const double CANARY2 = 0xBABEBABEBABEBABE;
const double POISON = 0;

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
        CANARY_DIED,
        ERR_OPEN_ERRCODE
};

const int MAXLENGTH = 10;

void BreakStack (stack_type *stack);
stack_errcodes_type UserComands (stack_type* stack);

stack_errcodes_type StackInit (stack_type* stack);

stack_errcodes_type StackPush (stack_type* stack, int value);
stack_errcodes_type StackPop (stack_type* stack);
stack_errcodes_type StackAdd (stack_type* stack);
stack_errcodes_type StackSub (stack_type* stack);
stack_errcodes_type StackMul (stack_type* stack);
stack_errcodes_type StackDiv (stack_type* stack);
stack_errcodes_type StackSqrt (stack_type* stack);

stack_errcodes_type StackDestroy (stack_type* stack);

stack_errcodes_type StackVerify (stack_type* stack, const char* filename, const char* funcname);
stack_errcodes_type StackDump (stack_type* stack, int errcode,
                               const char* filename, const char* funcname);
stack_errcodes_type PrintStack (stack_type* stack, FILE* fp);
