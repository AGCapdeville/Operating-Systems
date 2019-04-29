/**
 * Name: Adam Capdeville
 * Lab/task: Lab 5
 * Date: 02/25/2019 
**/
#include "bank.h"

int main(int argc, char *argv[])
{
    // load a configuration from a file if a file name provided as a command line argument by switching
    // stdin to the file temporarily
    // otherwise, the configuration will be read from the "regular" stdin
    int savedstdin = dup(STDIN_FILENO);
    if (argc > 1)
        if (freopen(argv[1], "r", stdin) == NULL)
        {
            printf("Cannot read from file %s\n%s (errno = %d)).\n", argv[1], strerror(errno), errno);
            exit(1);
        }

    // get the name of the input file
    loadBankState();

    // close the temporary stdin coming from the file
    fflush(stdin);
    fclose(stdin);

    // switch back to the "regular" stdin
    stdin = fdopen(savedstdin, "r");

    // run the simulation
    bankTeller();
}

