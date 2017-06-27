/***************************************************************************
** Author: Jessica Spokoyny
** Date: July 31, 2015
** Description: this function takes as parameters an array of ints and the 
size of the array, and returns a vector containing the mode(s)
***************************************************************************/

#include <vector>
#include <algorithm>
using namespace std;

vector<int> findMode(int num[], int size)
{
	int maxFrequency = 1;
	int count = 1;
			
	vector<int> modes;

	// loop to get highest number of occurences beginning at 1st element
	for (int i = 0; i < size; i++) 
	{
		for (int j = i; j < size; j++)
		{
			if (num[i] == num[j] && (i != j))
			{
				count++;

				// compare each value's counter to the value for 
				// maxFrequency and replace if higher
				if (count > maxFrequency)
					maxFrequency = count;
			}

			// initialize count back to 1 before looping again
			else 
				count = 1;
		}
	}

	// loop through again to compare each value to the max frequency
	for (int i = 0; i < size; i++) 
	{
		for (int j = i; j < size; j++)
		{
			if (num[i] == num[j] && (i != j))
			{
				count++;

				// push the number that has the the highest frequency 
				// into the vector
				if (count == maxFrequency)
					modes.push_back(num[i]);
			}

			// initialize count back to 1 before looping again
			else
				count = 1;
		}

		// if none of the numbers repeat, then push all into the vector
		if (maxFrequency == 1)
			modes.push_back(num[i]);
	}
	
	// sort the values in the resulting vector in ascending order
	sort(modes.begin(), modes.end());
	
	return modes;

};
