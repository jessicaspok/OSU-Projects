#include <iostream>
#include <vector>
//#include <algorithm>
//using namespace std;

std::vector<int> findMode(int array[], int size); // Function Prototype

int main() {
	const int SIZE = 1;
	int array[SIZE] = { 1};

	std::vector<int> displayVector = findMode(array, SIZE);

	for (unsigned int x = 0; x < displayVector.size(); x++)
	{
			std::cout << displayVector[x] << std::endl;
	}

	return 0;
}
