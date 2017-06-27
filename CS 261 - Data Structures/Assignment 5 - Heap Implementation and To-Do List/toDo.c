/*
 * CS 261 Assignment 5
 * Name:
 * Date:
 */

#include "dynamicArray.h"
#include "task.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

/**
 * Loads into heap a list from a file with lines formatted like
 * "priority, name".
 * @param heap
 * @param file
 */
void listLoad(DynamicArray* heap, FILE* file)
{
    const int FORMAT_LENGTH = 256;
    char format[FORMAT_LENGTH];
    snprintf(format, FORMAT_LENGTH, "%%d, %%%d[^\n]", TASK_NAME_SIZE);

    struct Task temp;
    while (fscanf(file, format, &temp.priority, &temp.name) == 2)
    {
        dyHeapAdd(heap, taskNew(temp.priority, temp.name), taskCompare);
    }
}

/**
 * Writes to a file all tasks in heap with lines formatted like
 * "priority, name".
 * @param heap
 * @param file
 */
void listSave(DynamicArray* heap, FILE* file)
{
    int i;
    for (i = 0; i < dySize(heap); i++)
    {
        struct Task* task = dyGet(heap, i);
        fprintf(file, "%d, %s\n", task->priority, task->name);
    }
}

/**
 * Prints every task in heap.
 * @param heap
 */
void listPrint(DynamicArray* heap)
{
    DynamicArray* temp = dyNew(1);
    dyCopy(heap, temp);
    while (dySize(temp) > 0)
    {
        Task* task = dyHeapGetMin(temp);
        taskPrint(task);
        printf("\n");
        dyHeapRemoveMin(temp, taskCompare);
    }
    dyDelete(temp);
}

/**
 * Handles the given command.
 * @param list
 * @param command
 */
void handleCommand(DynamicArray* list, char command)
{
    switch(command)
	{
    // load list from file
    case 'l':
    {
        FILE *inputFile;
        char fileName[TASK_NAME_SIZE];
        printf("\nPlease enter the filename: ");
        scanf("%s", fileName);

        inputFile = fopen(fileName, "r");

        // error loading file
        if (inputFile == NULL)
        {
            fprintf(stderr, "Cannot open %s\n\n", fileName);
        }

        else
        {
            printf("\nThe list has been loaded from file successfully.\n\n");
            listLoad(list, inputFile);
            fclose(inputFile);
        }

        // clear newline
        while (getchar() != '\n');
        break;
    }

    // save list to file
    case 's':
    {
        if(dySize(list) > 0)
        {
            FILE *outputFile;
            char fileName[TASK_NAME_SIZE];
            printf("\nPlease enter the filename: ");
            scanf("%s", fileName);

            outputFile = fopen(fileName, "w");

            // error saving file
            if (outputFile == NULL)
            {
                fprintf(stderr, "Cannot save %s\n\n", fileName);
            }

            else
            {
                printf("\nThe list has been saved into the file successfully.\n\n");
                listSave(list, outputFile);
                fclose(outputFile);
            }

            // clear newline
            while (getchar() != '\n');
        }
        else
        {
            printf("\nYour to-do-list is empty!\n\n");
        }
        break;
    }

    // add a task
    case 'a':
    {
        printf("\nPlease enter the task description: ");
        char name[TASK_NAME_SIZE];
        fgets(name, TASK_NAME_SIZE, stdin);

        // clear newline
        name[strcspn(name, "\n")] = 0;

        // input validation for priority
        int priority;
        do
        {
            printf("Please enter the task priority (0-999): ");
            scanf("%d", &priority);

            // clear newline
            while (getchar() != '\n');
        } while (priority < 0 || priority > 999);

        Task* newTask = taskNew(priority, name);
        dyHeapAdd(list, newTask, taskCompare);
        printf("\nThe task \'%s\' has been added to your to-do list.\n\n", name);
        break;
    }

    // get the first task
    case 'g':
    {
        if(dySize(list) > 0)
        {
            Task* firstTask = dyHeapGetMin(list);
            printf("\nYour first task is: %s\n\n", firstTask->name);
        }
        else
        {
            printf("\nYour to-do-list is empty!\n\n");
        }
        break;

    }

    // remove the first task
    case 'r':
    {
        if(dySize(list) > 0)
        {
            Task* firstTask = dyHeapGetMin(list);
            printf("\nYour first task \'%s\' has been removed from the list.\n\n", firstTask->name);
            dyHeapRemoveMin(list, taskCompare);
        }
        else
        {
            printf("\nYour to-do-list is empty!\n\n");
        }
        break;
    }

    // print the list
    case 'p':
    {
        if(dySize(list) > 0)
        {
            printf("\nYour to-do list:\n");
            listPrint(list);
            printf("\n");
        }
        else
        {
            printf("\nYour to-do-list is empty!\n\n");
        }
        break;
    }

    case 'e':
    {
        printf("\nBye!\n\n");
        break;
    }

    // invalid selection
    default:
    {
        printf("Invalid Selection...\n");
        break;
    }
    }
}

int main()
{
    // Implement
    printf("\n\n** TO-DO LIST APPLICATION **\n\n");
    DynamicArray* list = dyNew(8);
    char command = ' ';
    do
    {
        printf("Press:\n"
               "'l' to load to-do list from a file\n"
               "'s' to save to-do list to a file\n"
               "'a' to add a new task\n"
               "'g' to get the first task\n"
               "'r' to remove the first task\n"
               "'p' to print the list\n"
               "'e' to exit the program\n"
        );
        command = getchar();
        // Eat newlines
        while (getchar() != '\n');
        handleCommand(list, command);
    }
    while (command != 'e');
    dyDelete(list);
    return 0;
}
