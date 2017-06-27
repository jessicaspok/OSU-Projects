#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "dynamicArray.h"
#include "task.h"

int main(int argc, const char * argv[])
{
  	TYPE task1;
	TYPE task2;
	TYPE task3;
	TYPE task4;
	TYPE task5;
	TYPE task6;
	TYPE task7;
	TYPE task8;
	TYPE task9;
	TYPE task10;

	DynamicArray *mainList;
	mainList = dyNew(10);

	/* create tasks */
	task1 = taskNew(9, "a");
	task2 = taskNew(9, "b");
	task3 = taskNew(9, "c");
	task4 = taskNew(9, "d");
	task5 = taskNew(9, "e");
	task6 = taskNew(9, "f");
	task7 = taskNew(9, "g");
	task8 = taskNew(9, "h");
	task9 = taskNew(9, "i");
	task10 = taskNew(9, "j");

	/* add tasks to the dynamic array */
	dyHeapAdd(mainList, task1, taskCompare);
	dyHeapAdd(mainList, task2, taskCompare);
	dyHeapAdd(mainList, task3, taskCompare);
	dyHeapAdd(mainList, task4, taskCompare);
	dyHeapAdd(mainList, task5, taskCompare);
	dyHeapAdd(mainList, task6, taskCompare);
	dyHeapAdd(mainList, task7, taskCompare);
	dyHeapAdd(mainList, task8, taskCompare);
	dyHeapAdd(mainList, task9, taskCompare);
	dyHeapAdd(mainList, task10, taskCompare);



	printf("Elements added.. Before Sort: \n");
    dyPrint(mainList, taskPrint);

	// sort
	dyHeapSort(mainList, taskCompare);

	printf("\nAfter Sort: \n");
	dyPrint(mainList, taskPrint);

	while (dySize(mainList) > 0)
    {
        // remove min
        dyHeapRemoveMin(mainList, taskCompare);

        printf("\nAfter dyHeapRemoveMin: \n");
        dyPrint(mainList, taskPrint);

        // sort
        dyHeapSort(mainList, taskCompare);

        printf("\nAfter Sort: \n");
        dyPrint(mainList, taskPrint);
    }
	return 0;
}
