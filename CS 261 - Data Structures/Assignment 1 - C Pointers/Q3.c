/* CS261- Assignment 1 - Q.3*/
/* Name: Jessica Spokoyny
 * Date: 04/04/2016
 * Solution description: allocates an
 * array of n integers, prints it, calls
 * sort function to sort the values,
 * prints again */

#include <stdio.h>
#include<stdlib.h>
#include<math.h>


void sort(int* number, int n){
    /*Sort the given array number , of length n*/
    if(n == 0)
    {
        return;
    }

    int i;
    int j;
    int temp;

    for (i = n - 1; i > 0; i--)
    {
        for (j = 0; j < i; j++)
        {
            if (number[j] > number[j + 1])
            {
                temp = number[j];
                number[j] = number[j + 1];
                number[j + 1] = temp;
            }
        }
    }
}

int main(){
    /*Declare an integer n and assign it a value of 20.*/
    int n = 20;

    /*Allocate memory for an array of n integers using malloc.*/
    int *intArr = malloc(n * sizeof(int));

    /*Fill this array with random numbers, using rand().*/
    int i;

    for (i = 0; i < n; i++)
    {
        intArr[i] = rand() % 100 + 1;
    }

    /*Print the contents of the array.*/
    printf("\nContents of the array: \n");

    for(i = 0; i < n; i++)
    {
        printf("%d \n",intArr[i]);
    }

    /*Pass this array along with n to the sort() function of part a.*/
    sort(intArr, n);

    /*Print the contents of the array.*/
    printf("\nSorted contents of the array: \n");

    for(i = 0; i < n; i++)
    {
        printf("%d\n",intArr[i]);
    }

    printf("\n");
    free(intArr);

    return 0;
}
