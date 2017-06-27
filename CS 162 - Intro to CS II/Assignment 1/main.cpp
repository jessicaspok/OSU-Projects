/*********************************************************************
** Program Filename: main.cpp
** Author: Jessica Spokoyny
** Date: 01/14/16
** Description: Assignment 1: Implementation of Conway's Game of Life
** Input:
** Output:
*********************************************************************/
#include "life.hpp"

/*********************************************************************
** Function: main
** Description: main is required for program to run
*********************************************************************/

int main()
{
	/* intro for game*/
	cout << endl << "This program runs the game of life." << endl
		<< endl << endl << "There are three options for starting shapes:"
		<< endl << "an oscillator (1), a glider (2), or a glider gun (3)" 
		<< endl << endl;

	/* get shape selection from user */
	int shape;
	cout << "Enter your selection (1 or 2 or 3) : ";
	cin >> shape;
	cout << endl;

	/* get shape's starting location from user */
	cout << "Where would you like to place the top left corner of the shape?" << endl;
	int startRow;
	int startCol;
	
	/* recommend placement for each shape for full viewing */
	if (shape == 1)
	{
		cout << "ROW (choose between 1 - 19) : ";
		cin >> startRow;
		cout << endl;
		cout << "COLUMN (choose between 0 - 38 ) : ";
		cin >> startCol;
		cout << endl;
	}
	
	else if (shape == 2)
	{
		cout << "ROW (choose betwee 0 - 18) : ";
		cin >> startRow;
		cout << endl;
		cout << "COLUMN (choose between 0 - 38) : ";
		cin >> startCol;
		cout << endl;
	}

	else if (shape == 3)
	{
		cout << "ROW (choose between 0 - 11) : ";
		cin >> startRow;
		cout << endl;
		cout << "COLUMN (choose between 0 - 4) : ";
		cin >> startCol;
		cout << endl;
	}

	/* create a new array with extra room on each side */
	int array[80][100];

	/* initialize the array to all dead */
	for (int i = 0; i < 80; i++)
	{
		for (int j = 0; j < 100; j++)
		{
			array[i][j] = 0;
		}
	}

	/* change appropriate cells to alive based on user's shape selection */
	buildShape(array, shape, startRow, startCol);

	/* get number of generations from user */
	int generations;
	
	cout << "How many generations would you like to see performed? ";
	cin >> generations;
	cout << endl;

	/* create new temporary array */
	int temp[80][100];
		
	do
	{
		/* clear the screen */
		system("clear");

		/* print only the 20x40 portion of array */
		for (int i = 30; i < 50; i++)
		{
			for (int j = 30; j < 70; j++)
			{
				if (array[i][j] == 0)
				{
					/* dead cells will be ' ' */
					cout << "-";
				}
				else
				{
					/* live cells will be 'X' */
					cout << "X";
				}
			}
			
			cout << endl;
		}

		/* pause to let user see the movements */
		system("sleep .1");

		/* coppy array to temp array to save pending changes before printing */
		copyArray(array, temp);

		/* loop through all cells to check state */
		for (int i = 0; i < 80; i++)
		{
			for (int j = 0; j < 100; j++)
			{
				/* count number of neighbors */
				int count = 0;
				count = array[i - 1][j - 1]
					+ array[i][j - 1]
					+ array[i + 1][j - 1]
					+ array[i - 1][j]
					+ array[i + 1][j]
					+ array[i - 1][j + 1]
					+ array[i][j + 1]
					+ array[i + 1][j + 1];

				/* cell becomes/remains dead */
				if (count < 2 || count > 3)
				{
					temp[i][j] = 0;
				}

				/* cell becomes/remains alive */
				else if (count == 3)
				{
					temp[i][j] = 1;
				}

				/* cell remains unchanged */
				else
				{
					temp[i][j] = array[i][j];
				}
			}
		}

		/* copy temp array back to array */
		copyArray(temp, array);
		
		/* loop through again for each remaining generation */
		generations--;

	} while (generations > 0);

	return 0;
}
