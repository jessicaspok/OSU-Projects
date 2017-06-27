/* CS261- Assignment 1 - Q.4*/
/* Name: Jessica Spokoyny
 * Date: 04/04/2016
 * Solution description: allocates memory for n students,
 * assigns them random id numbers and scores,
 * calls sort function sorts them by score, prints it
 * all to the screen */

#include <stdio.h>
#include<stdlib.h>
#include<math.h>

struct student{
	int id;
	int score;
};

void sort(struct student* students, int n){
     /*Sort the n students based on their score*/
	int i;
	int j;
	struct student temp;

	for (i = 0; i < n - 1; i++)
	{
		for (j = 0; j < n - 1 - i; j++)
		{
			if (students[j + 1].score < students[j].score)
			{
				temp = students[j];
				students[j] = students[j + 1];
				students[j + 1] = temp;
			}
		}
	}
}

int main(){
    /*Declare an integer n and assign it a value.*/
    int n = 10;

    /*Allocate memory for n students using malloc.*/
    struct student *students = malloc(sizeof(struct student)*n);

    /*Generate random IDs and scores for the n students, using rand().*/
    int id;
    int score;
    int i;
    int j;
    _Bool isUnique;

    // generate random id 1-10
    for(i = 0; i < n; i++)
    {
        isUnique = 0;
        id = (rand() % n + 1);

        // check if id already exists
        while (isUnique == 0)
        {
            for(j = 0; j < n; j++)
            {
                // if duplicate
                if(students[j].id == id)
                {
                    id = (rand() % n + 1);
                    j = -1;
                }

                // if unique
                else
                {
                    isUnique = 1;
                }
            }
        }

        score = (rand() % 100 + 1);
        students[i].id = id;
        students[i].score = score;
    }

    /*Print the contents of the array of n students.*/
    printf("\nContents of the array: \n");

    for(i = 0; i < n; i++)
    {
        printf("ID%d Score%d\n",students[i].id,students[i].score);
    }

    /*Pass this array along with n to the sort() function*/
    sort(students, n);

    /*Print the contents of the array of n students.*/
    printf("\nContents of the sorted array: \n");

    for(i = 0; i < n; i++)
    {
        printf("ID%d Score%d\n",students[i].id,students[i].score);
    }

    printf("\n");

    free(students);
    return 0;
}
