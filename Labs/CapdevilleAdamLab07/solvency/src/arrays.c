/**
 * Name: Adam Capdeville
 * Lab/task: Lab 5
 * Date: 02/25/2019 
**/
#include "arrays.h"

void arraycpy(double to[], double from[], int num)
{
    for (int i = 0; i < num; i++)
        to[i] = from[i];
}

bool lessOrSame(double a[], double b[], int num)
{
    for (int i = 0; i < num; i++)
        if (a[i] > b[i])
            return false;
    return true;
}

void add(double a[], double b[], int num)
{
    for (int i = 0; i < num; i++)
        a[i] += b[i];
}

void sub(double a[], double b[], int num)
{
    for (int i = 0; i < num; i++)
        a[i] -= b[i];
}

void sub2(double a[], double b[], double c[], int num)
{
    for (int i = 0; i < num; i++)
        a[i] = b[i] - c[i];
}

void set(bool b, double a[], int num)
{
    for (int i = 0; i < num; i++)
        a[i] = b;
}

bool allTrue(bool a[], int num)
{
    for (int i = 0; i < num; i++)
        if (!a[i])
            return false;
    return true;
}

void display(double array[], int num)
{
    printf(" [ ");
    for (int i = 0; i < num; i++)
        printf("%8.2f", array[i]);
    printf("]");
}

