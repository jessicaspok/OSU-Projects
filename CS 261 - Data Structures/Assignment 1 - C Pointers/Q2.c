/* CS261- Assignment 1 - Q.2*/
/* Name: Jessica Spokoyny
 * Date: 04/04/2016
 * Solution description: passes variables
 * a, b, c to function foo. foo doubles a,
 * halves b, assigns c to the sum of a
 * and b, then returns c. prints results.
 */

#include <stdio.h>
#include <stdlib.h>

int foo(int* a, int* b, int c){
    /*Set a to double its original value*/
    *a = *a * 2;

    /*Set b to half its original value*/
    *b = *b / 2;

    /*Assign a+b to c*/
    c = *a + *b;

    /*Return c*/
    return c;
}

int main(){
    /*Declare three integers x,y and z and initialize them to 5, 6, 7 respectively*/
    int x = 5;
    int y = 6;
    int z = 7;
    int fooVal;

    /*Print the values of x, y and z*/
    printf("\nThe value of x is: %d \n",x);
    printf("The value of y is: %d \n",y);
    printf("The value of z is: %d \n",z);

    /*Call foo() appropriately, passing x,y,z as parameters*/
    fooVal = foo(&x,&y,z);

    /*Print the value returned by foo*/
    printf("\nThe value returned by foo is: %d \n",fooVal);

    /*Print the values of x, y and z again*/
    printf("\nThe value of x is: %d \n",x);
    printf("The value of y is: %d \n",y);
    printf("The value of z is: %d \n\n",z);


    /*Is the return value different than the value of z?  Why?*/
    /* Yes, the return value is different than the value of z
    * because z was passed by value to foo (a copy of z was
    * passed). a and b were passed by reference (the original
    * a and b were passed) so their values changed in the
    * function.*/

    return 0;
}


