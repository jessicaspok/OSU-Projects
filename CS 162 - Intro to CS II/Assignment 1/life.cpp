/*********************************************************************
** Program Filename: life.cpp
** Author: Jessica Spokoyny
** Date: 01/14/16
** Description: implementation of functions for Game of Life
*********************************************************************/
#include "life.hpp"

/*********************************************************************
** Function: copyArray
** Description: copies the contents of one array to another array
** Parameters: two int arrays of the same size
*********************************************************************/

void copyArray(int original[80][100], int copy[80][100])
{
	for (int i = 0; i < 80; i++)
	{
		for (int j = 0; j < 100; j++)
		{
			copy[i][j] = original[i][j];
		}
	}
}

/*********************************************************************
** Function: buildShape
** Description: builds the user-selected shape at the user-selected 
**	coordinates. 
** Parameters: an int array, the selected shape, the row and column 
**	where to place the selected shape
*********************************************************************/

void buildShape(int arr[80][100], int shape, int row, int col)
{
	/* adjust user-entered location to account for extra space in array */
	int newRow = row + 30;
	int newCol = col + 30;

	/* create the oscillator */
	if (shape == 1)
	{
		arr[newRow][newCol] = 1;
		arr[newRow][newCol + 1] = 1;
		arr[newRow][newCol + 2] = 1;
	}

	/* create the glider */
	if (shape == 2)
	{
		arr[newRow][newCol] = 1;
		arr[newRow + 1][newCol + 1] = 1;
		arr[newRow + 1][newCol + 2] = 1;
		arr[newRow + 2][newCol] = 1;
		arr[newRow + 2][newCol + 1] = 1;
	}

	/* create the glider gun */
	if (shape == 3)
	{
		arr[newRow][newCol + 24] = 1;
		arr[newRow + 1][newCol + 22] = 1;
		arr[newRow + 1][newCol + 24] = 1;
		arr[newRow + 2][newCol + 12] = 1;
		arr[newRow + 2][newCol + 13] = 1;
		arr[newRow + 2][newCol + 20] = 1;
		arr[newRow + 2][newCol + 21] = 1;
		arr[newRow + 2][newCol + 34] = 1;
		arr[newRow + 2][newCol + 35] = 1;
		arr[newRow + 3][newCol + 11] = 1;
		arr[newRow + 3][newCol + 15] = 1;
		arr[newRow + 3][newCol + 20] = 1;
		arr[newRow + 3][newCol + 21] = 1;
		arr[newRow + 3][newCol + 34] = 1;
		arr[newRow + 3][newCol + 35] = 1;
		arr[newRow + 4][newCol] = 1;
		arr[newRow + 4][newCol + 1] = 1;
		arr[newRow + 4][newCol + 10] = 1;
		arr[newRow + 4][newCol + 16] = 1;
		arr[newRow + 4][newCol + 20] = 1;
		arr[newRow + 4][newCol + 21] = 1;
		arr[newRow + 5][newCol] = 1;
		arr[newRow + 5][newCol + 1] = 1;
		arr[newRow + 5][newCol + 10] = 1;
		arr[newRow + 5][newCol + 14] = 1;
		arr[newRow + 5][newCol + 16] = 1;
		arr[newRow + 5][newCol + 17] = 1;
		arr[newRow + 5][newCol + 22] = 1;
		arr[newRow + 5][newCol + 24] = 1;
		arr[newRow + 6][newCol + 10] = 1;
		arr[newRow + 6][newCol + 16] = 1;
		arr[newRow + 6][newCol + 24] = 1;
		arr[newRow + 7][newCol + 11] = 1;
		arr[newRow + 7][newCol + 15] = 1;
		arr[newRow + 8][newCol + 12] = 1;
		arr[newRow + 8][newCol + 13] = 1;
	}

}