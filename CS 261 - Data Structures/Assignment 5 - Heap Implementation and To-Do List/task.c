/*
 * CS 261 Assignment 5
 * Name: Jessica Spokoyny
 * Date: 05/13/2016
 */

#include "task.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

/**
 * Creates a new task with the given priority and name.
 * @param priority
 * @param name
 * @return  The new task.
 */
Task* taskNew(int priority, char* name)
{
    Task* newTask = malloc(sizeof(Task));

    // assign name and priority
    strcpy(newTask->name, name);
    newTask->priority = priority;

    return newTask;
}

/**
 * Frees a dynamically allocated task.
 * @param task
 */
void taskDelete(Task* task)
{
    free(task);
}

/**
 * Casts left and right to Task pointers and returns
 * -1 if left's priority < right's priority,
 *  1 if left's priority > right's priority,
 *  0 if left's priority == right's priority.
 * @param left  Task pointer.
 * @param right  Task pointer.
 * @return
 */
int taskCompare(void* left, void* right)
{
    // assign pointers for left and right tasks
    Task* leftTask;
    leftTask = (Task*)left;
    Task* rightTask;
    rightTask = (Task*)right;

    // compare priority of the tasks
    if(leftTask->priority > rightTask->priority)
	{
      return 1;
    }

    else if(leftTask->priority < rightTask->priority)
	{
      return -1;
	}

    else
	{
      return 0;
	}
}

/**
 * Prints a task as a (priority, name) pair.
 * @param value  Task pointer.
 */
void taskPrint(void* value)
{
    Task* task = (Task*)value;
    printf("(%d, %s)", task->priority, task->name);
}
