#include <stdio.h>
#include <stdlib.h>

const int CANARY = 0x12345678;

int main ()
{
    char* ptr = (char*)&CANARY;
    int num_bytes = sizeof(CANARY);


    printf("Представление числа %d в памяти:\n", CANARY);

    for (int i = 0; i < num_bytes; i++) {
        printf("%02x ", ptr[i]);
    }

    printf ("\n");
}
