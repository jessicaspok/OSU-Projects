/* CS261- Assignment 1 - Q. 0*/
/* Name: Jessica Spokoyny
 * Date: 04/04/2016
 * Solution description: Prints value and address of integer x
 */

#include <stdio.h>
#include <stdlib.h>

void fooA(int* iptr){
     /*Print the value pointed to by iptr*/
     printf("The value pointed to by iptr is: %d \n", *iptr);

     /*Print the address pointed to by iptr*/
     printf("The address pointed to by iptr is: %p \n", iptr);

     /*Print the address of iptr itself*/
     printf("The address of iptr itself is: %p \n", &iptr);
}

int main(){

    /*declare an integer x*/
    int x = 10;

    /*print the address of x*/
    printf("\nThe address of x is: %p \n", &x);

    /*Call fooA() with the address of x*/
    fooA(&x);

    /*print the value of x*/
    printf("The value of x is: %d \n\n", x);

    return 0;
}
