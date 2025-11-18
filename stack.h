#define GREEN   "\x1b[32m"
#define COLOR_RESET   "\x1b[0m"

#define RETURN_IF_ERR if (errcode != NO_ERR) return errcode

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
        STACK_NULL_ERR = 1,
        STACK_DATA_NULL_ERR = 2,
        NO_SPACE_ERR = 4,
        ILLEGAL_SIZE = 8,
        INCORRECT_INPUT = 16,
        INCORRECT_INPUT_ARG = 32,
        OVERFLOWED = 64,
        CANARY_DIED = 128,
        CANARY_IN_DANGER = 256,
        ERR_OPEN_INPUT_FILE = 512,
        ERR_OPEN_ERR_FILE = 1024,
        POISON_ERROR = 2048,
        DIVISION_BY_ZERO = 4096
};

const int MAXLENGTH = 10;

void BreakStack (stack_type *stack);
stack_errcodes_type UserCommands (stack_type* stack);

stack_errcodes_type StackInit (stack_type* stack);

stack_errcodes_type StackResize (stack_type* stack);
stack_errcodes_type StackPush (stack_type* stack, double value);
double StackPop (stack_type* stack, stack_errcodes_type* errcode);
stack_errcodes_type StackAdd (stack_type* stack);
stack_errcodes_type StackSub (stack_type* stack);
stack_errcodes_type StackMul (stack_type* stack);
stack_errcodes_type StackDiv (stack_type* stack);

stack_errcodes_type StackDestroy (stack_type* stack);

stack_errcodes_type StackVerify (stack_type* stack, const char* filename,
                                 const char* funcname, int num_string);
stack_errcodes_type StackDump (stack_type* stack, stack_errcodes_type errcode,
                               const char* filename, const char* funcname, int num_string);
stack_errcodes_type PrintStack (stack_type* stack, FILE* fp);
bool IsZero (double a);
void PrintErrcodes (stack_errcodes_type errcode, FILE* fp);


#define PRE_VERIFY                                                                      \
        stack_errcodes_type errcode = NO_ERR;                                           \
                                                                                        \
        if ((errcode = StackVerify (stack, __FILE__, __func__, __LINE__)) != NO_ERR)    \
                return errcode;                                                         \


#define POST_VERIFY                                                                     \
        if (errcode != NO_ERR &&                                                        \
            (errcode = StackVerify (stack, __FILE__, __func__, __LINE__)) != NO_ERR)    \
                return errcode;                                                         \

#define DUMP(errcode) StackDump (stack, errcode, __FILE__, __func__, __LINE__)
