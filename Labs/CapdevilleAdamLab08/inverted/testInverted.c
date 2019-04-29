#include "inverted.h"

PROC *table;

int main(int argc, char **argv)
{
    if (argc < 2)
    {
        printf("USE: <prog name> <memory size> <frame size>\n");
        exit(EXIT_FAILURE);
    }

    initInverted(&table, strtol(argv[1], NULL, 10), strtol(argv[2], NULL, 10));

    printf("translate(1, 10, 0) = %ld\n", translate(table, 1, 10, 0));
    printf("translate(1, 20, 456) = %ld\n", translate(table, 1, 20, 456));
    printf("translate(2, 10, 0) = %ld\n", translate(table, 2, 10, 0));
    printf("translate(1, 20, 456) = %ld\n", translate(table, 1, 20, 456));

    exit(EXIT_SUCCESS);
}
