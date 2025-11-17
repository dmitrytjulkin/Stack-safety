#define GREEN   "\x1b[32m"
#define COLOR_RESET   "\x1b[0m"

const double CANARY1 =  0xEDAEDAEDAEDAEDAE;
const double CANARY2 = 0xBABEBABEBABEBABE;
const double POISON = 0xB011B011B011B011;

struct stack_type {
        size_t size;
        size_t capacity;
        double* data;
};

enum stack_errcodes_type {
        NO_ERR = 0,
        NULL_ERR = 1,
        NO_SPACE_ERR = 2,
        INCORRECT_INPUT = 4,
        INCORRECT_INPUT_ARG = 8,
        OVERFLOWED = 16,
        CANARY_DIED = 32,
        ERR_OPEN_INPUT_FILE = 64,
        ERR_OPEN_ERR_FILE = 128,
        POISON_ERROR = 256
};

const int MAXLENGTH = 10;

void BreakStack (stack_type *stack);
stack_errcodes_type UserComands (stack_type* stack);

stack_errcodes_type StackInit (stack_type* stack);

stack_errcodes_type StackPush (stack_type* stack, double value);
double StackPop (stack_type* stack, stack_errcodes_type* errcode);
stack_errcodes_type StackAdd (stack_type* stack);
stack_errcodes_type StackSub (stack_type* stack);
stack_errcodes_type StackMul (stack_type* stack);
stack_errcodes_type StackDiv (stack_type* stack);

stack_errcodes_type StackDestroy (stack_type* stack);

stack_errcodes_type StackVerify (stack_type* stack, const char* filename, const char* funcname);
stack_errcodes_type StackDump (stack_type* stack, stack_errcodes_type errcode,
                               const char* filename, const char* funcname);
stack_errcodes_type PrintStack (stack_type* stack, FILE* fp);
