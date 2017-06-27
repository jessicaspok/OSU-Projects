/*	stack.c: Stack application. */
#include <stdio.h>
#include <stdlib.h>
#include "dynArray.h"


/* ***************************************************************
Using stack to check for unbalanced parentheses.
***************************************************************** */

/* Returns the next character of the string, once reaches end return '0' (zero)
	param: 	s pointer to a string
	pre: s is not null
*/
char nextChar(char* s)
{
	static int i = -1;
	char c;
	++i;
	c = *(s+i);
	if ( c == '\0' )
		return '\0';
	else
		return c;
}

/* Checks whether the (), {}, and [] are balanced or not
	param: 	s pointer to a string
	pre: s is not null
	post: returns 1 if balanced, 0 if not
*/
int isBalanced(char* s)
{
	int capacity = 10;
	char c;

	if(s == 0)
	{
		printf("Error: argument required\n");
		return 0;
	}

	DynArr* symArr = newDynArr(capacity);

	do
	{
		c = nextChar(s);
        // push left brackets on stack
		if((c =='(')||(c =='{')||(c =='['))
		{
			pushDynArr(symArr,c);
		}

		// check right brackets match
		if((c ==')')||(c =='}')||(c ==']'))
		{
			// if stack is empty
			if(!sizeDynArr(symArr))
			{
				return 0;
			}

            // check each type of bracket
			else
			{
				if (c == ')')
				{
					if (topDynArr(symArr) == '(')
					{
						popDynArr(symArr);
					}
				}
				if (c == '}')
				{
					if (topDynArr(symArr) == '{')
					{
						popDynArr(symArr);
					}
				}
				if (c == ']')
				{
					if (topDynArr(symArr) == '[')
					{
						popDynArr(symArr);
					}
				}
			}
		}
	}while(c !='\0');

	// if end result is empty stack, all brackets are balanced
	if(sizeDynArr(symArr) == 0)
	{
		return 1;
	}

	return 0;
}

int main(int argc, char* argv[]){

	char* s=argv[1];
	int res;

	printf("Assignment 2\n");

	res = isBalanced(s);

	if (res)
		printf("The string %s is balanced\n",s);
	else
		printf("The string %s is not balanced\n",s);

	return 0;
}
