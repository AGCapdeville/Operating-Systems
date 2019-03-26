/**
 * Name: Adam Capdeville
 * Lab/task: Lab 7
 * Date: 03/11/2019
**/

#include "bank.h"

int numOfCustomers;        // the number of customers of the bank
int numOfAccounts;         // the number of accounts offered by the bank

double *available;    // the amount available of each customer
double **maximum;     // the maximum demand of each customer
double **allocation;  // the amount currently allocated to each customer
double **need;     // the remaining needs of each customer

/***
 * Read the state of the bank from a file.
 *
 * The file format is as follows:
 *
 * <num of customers> <num of accounts>
 * <initial state of accounts>
 * <max needs for each customer>
 *
 * e.g.,
 *
 * 5 3
 * 15 10 5
 * 7,5,3
 * 3,2,2
 * 9,0,2
 * 2,2,2
 * 4,3,3
 *
 * Any of  ", \n\t" is a valid separator
 *
 */
void loadBankState()
{
    // create the bank
    initBank();

    // read initial values for maximum array
    for (int i = 0; i < numOfCustomers; i++)
        addBankCustomer(i);
}

/***
 * Initialize the bank for a number of accounts and customers.
 */
void initBank()
{
    double in[2];
    readLine(in);
    numOfCustomers = (int) in[0];
    numOfAccounts = (int) in[1];

    available = calloc(numOfAccounts, sizeof(double));
    readLine(available);

    // initialize the accounts
    maximum = calloc(numOfCustomers, sizeof(double *));
    allocation = calloc(numOfCustomers, sizeof(double *));
    need = calloc(numOfCustomers, sizeof(double *));

}

/***
 * This function adds a customer to the bank system.
 * It records its maximum fund demand with the bank.
 */
void addBankCustomer(int customerNum)
{
    maximum[customerNum] = calloc(numOfAccounts, sizeof(double));
    readLine(maximum[customerNum]);

    allocation[customerNum] = calloc(numOfAccounts, sizeof(double));
    // we start with zero allocated

    need[customerNum] = calloc(numOfAccounts, sizeof(double));
    arraycpy(need[customerNum], maximum[customerNum], numOfAccounts);

    //finnish[customerNum] = calloc()
}

/***
 * Outputs the state of the bank; i.e., funds in each account of each customer
 */
void displayBankState()
{
    printf("%13s", "Available =");
    display(available, numOfAccounts);

    printf("\n%13s", "Allocation =");
    for (int i = 0; i < numOfCustomers; i++)
        display(allocation[i], numOfAccounts);

    printf("\n%13s", "Max =");
    for (int i = 0; i < numOfCustomers; i++)
        display(maximum[i], numOfAccounts);

    printf("\n%13s", "Need =");
    for (int i = 0; i < numOfCustomers; i++)
        display(need[i], numOfAccounts);

    printf("\n");
}

/***
 * Determines whether granting a request for loan results in leaving
 * the system in a safe state or not.
 */
bool solvencyTest(int customerNum, double *request)
{
    // TODO implement

    double work[numOfAccounts];
    for(int i = 0; i < numOfAccounts; i++)
    {
        work[i] = available[i];
    }

    double** tempNeed;
    tempNeed = calloc(numOfCustomers, sizeof(double *));
    for(int i = 0; i < numOfCustomers; i++)
    {
        tempNeed[i] = malloc(numOfAccounts * sizeof(double));
        arraycpy(tempNeed[i], need[i], numOfAccounts);
    }
    

    

    if( lessOrSame(request, need[customerNum], numOfAccounts) ){
        if( lessOrSame(request, available, numOfAccounts) ){
            sub(work, request, numOfAccounts);
            sub(tempNeed[customerNum], request, numOfAccounts); // modify temp need
            for(int i = 0; i < numOfCustomers; i++)
            {
                // make sure everyone can pull their 
                // after customerNum pull request
                // any indvidual customer can pull all of their money
                for(int j = 0; j < numOfAccounts; j++)
                {
                    if( tempNeed[i][j] > work[j] ){
                        //printf("\n need of a customer > Available , customer: %d work: %d\n",i,j);
                        return false;
                    }
                }
            }
        }else
        {
            //printf("request is greater than what is available\n");
            return false;
        }
    }else
    {
        //printf("request is greater than need\n");
        return false;
    }
    
    return true; // TODO: modify as appropriate
}

/***
 * Make a request for a loan.
 */

bool borrow(int customerNum, double funds[])
{
    bool ret = solvencyTest(customerNum, funds);
    // TODO: complete

    if(ret == true){    // take funds from Available & Need
        sub(available,funds, numOfAccounts);
        add(allocation[customerNum],funds,numOfAccounts);
        sub(need[customerNum],funds,numOfAccounts);
    }
    return ret;
}

/***
 * Repay a loan.
 */
bool repay(int customerNum, double funds[])
{
    bool ret = lessOrSame(funds, allocation[customerNum], numOfAccounts);
    // TODO: complete

    if(ret == true){
        add(available, funds, numOfAccounts);
        sub(allocation[customerNum], funds, numOfAccounts);
        add(need[customerNum], funds, numOfAccounts);
    }

    return ret;
}


/***
 * In a loop, take input from the standard console until 'Q' or 'q' is entered.
 *
 * Each input should have the following syntax:
 *
 * {Q[UIT] | ST[ATUS] | [BO[RROW] | RE[PAY]] <customer number>  {<account funds> ...}}
 *
 * e.g. (for 3 accounts and with at least 2 customers):
 *
 * ST
 * BO 1 3 2 1
 * RE 1 1 0 1
 * QUIT
 *
 */
void bankTeller()
{
    // now loop reading requests to withdraw or deposit funds
    double request[numOfAccounts];
    char *inp = malloc(MAX_LINE_SIZE * sizeof(char));
    while (fgets(inp, MAX_LINE_SIZE, stdin) != 0)
    {
        if (strlen(inp) == 0)
            goto exception;

        // need a copy, since "line" will be used for tokenizing, so
        // it will change until it gets NULL; we would nnot be able to re-use it
        char *line = strdup(inp);

        // get transaction type - borrow (BO) or repay (RE) or ST (status)
        line[strlen(line) - 1] = '\0';

        if (line == NULL)
            goto exception;

        char *trans = strsep(&line, " ,\t");
        strToUpper(&trans); // so the case does not matter

        printf("REQUEST: %s\n", trans);
        if (trans[0] == 'Q')
        {
            displayBankState();
            exit(1);
        }
        else if (strncmp(trans, "STATUS", 2) == 0)
            displayBankState();
        else
        {
            if ((strncmp(trans, "BORROW", 2) != 0) && (strncmp(trans, "REPAY", 2) != 0))
                goto exception;

            // get the customer number making the tranaction
            if (line == NULL)
                goto exception;

            int custNum = strtod(strsep(&line, " "), NULL);
            printf("CLIENT %d: ", custNum);

            if (custNum >= numOfCustomers)
                goto exception;

            // get the resources involved in the transaction
            for (int i = 0; i < numOfAccounts; i++)
            {
                if (line == NULL)
                    goto exception;

                request[i] = strtod(strsep(&line, " ,\t"), NULL);
            }

            display(request, numOfAccounts);

            // now check the transaction type
            if (strncmp(trans, "BORROW", 2) == 0)
            {
                if (borrow(custNum, request))
                    printf("\n*APPROVED*\n");
                else
                    printf("\n*DENIED*\n");
            }
            else if (strncmp(trans, "REPAY", 2) == 0)
            {
                if (repay(custNum, request))
                    printf("\n*APPROVED*\n");
                else
                    printf("\n*DENIED*\n");
            }
            continue;
            exception:
            printf("\nExpected input: Q[UIT] | ST[ATUS] | [BO[RROW] | RE[PAY]] <customer number> <resource #1> <#2> <#3> ...\n");
            continue;
        }
    }
}

/***
 * Read a line of values separated by a set of delimeters from a file into an array
 */
void readLine(double array[])
{
    char *line = malloc(MAX_LINE_SIZE * sizeof(char));
    fgets(line, MAX_LINE_SIZE, stdin);
    char *tok;
    int i = 0;
    while ((tok = strsep(&line, ", \n\t")) != NULL)
        if (strlen(tok) > 0)
            array[i++] = strtod(tok, NULL);

    free(line);
}

/***
 * Convert the string to upper case
 */
void strToUpper(char **s)
{
    for (char *c = *s; *c; c++)
        if (isascii(*c) && islower(*c))
            *c = toupper(*c);
}
