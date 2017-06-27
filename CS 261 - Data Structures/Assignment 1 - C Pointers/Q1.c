/* CS261- Assignment 1 - Q.1*/
/* Name: Jessica Spokoyny
 * Date: 04/04/2016
 * Solution description: allocates memory for 10 students,
 * assigns them random id numbers and scores, finds min, max
 * avg score, prints it all to the screen */

#include <stdio.h>
#include<stdlib.h>
#include<math.h>

struct student{
	int id;
	int score;
};

struct student* allocate(){
     /*Allocate memory for ten students*/
     struct student* stu = malloc(10*sizeof(struct student));

     /*return the pointer*/
     return stu;
}

void generate(struct student* students){
     /*Generate random and unique ID and scores for ten students, ID being between 1 and 10, scores between 0 and 100*/
    int id;
    int score;
    int i;
    int j;
    _Bool isUnique;

    // generate random id 1-10
    for(i = 0; i < 10; i++)
    {
        isUnique = 0;
        id = (rand() % 10 + 1);

        // check if id already exists
        while (isUnique == 0)
        {
            for(j = 0; j < 10; j++)
            {
                // if duplicate
                if(students[j].id == id)
                {
                    id = (rand() % 10 + 1);
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
}

void output(struct student* students){
     /*Output information about the ten students in the format:
              ID1 Score1
              ID2 score2
              ID3 score3
              ...
              ID10 score10*/
    int i;

    printf("\n");
    for(i=0; i < 10; i++)
    {
        printf("ID%d Score%d \n",students[i].id,students[i].score);
    }
}

void summary(struct student* students){
     /*Compute and print the minimum, maximum and average scores of the ten students*/
     int i;
     int sum = 0;
     float avg = 0;
     int min;
     int max;

     // find average
     for(i = 0; i < 10; i++)
     {
         sum += students[i].score;
     }

     avg = (sum / 10.0);

     // find min
     min = students[0].score;

     for(i = 0; i < 10; i++)
     {
         if(students[i].score < min)
         {
             min = students[i].score;
         }
     }

     // find max
     max = students[0].score;

     for(i = 0; i < 10; i++)
     {
         if(students[i].score > max)
         {
             max = students[i].score;
         }
     }

    // print summary
    printf("\nMinimum Score: %d \n",min);
    printf("Maximum Score: %d \n",max);
    printf("Average Score: %f \n\n",avg);
}

void deallocate(struct student* stud){
     /*Deallocate memory from stud*/
    if(stud != NULL)
    {
        free(stud);
    }
}

int main(){
    struct student* stud = NULL;

    /*call allocate*/
    stud = allocate();

    /*call generate*/
    generate(stud);

    /*call output*/
    output(stud);

    /*call summary*/
    summary(stud);

    /*call deallocate*/
    deallocate(stud);

    return 0;
}
