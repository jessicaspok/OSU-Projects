#include "main.hpp"
#include <iostream>
#include <iomanip>
#include <chrono>
#include <stdlib.h>
#include <fstream>
#include <string>
#include <sstream>

typedef struct {
    unsigned left;
    unsigned right;
    int sum;
} maxsubarray;

void findmax_enum(int* array, int size, int* lower, int*upper, int*maxarraysum);
void findmax_enum_better(int* array, int size, int* lower, int*upper, int*maxarraysum);
void findmax_recursive(int* array, int lowerbound, int upperbound, int* lower, int*upper, int*maxarraysum);
void findmax_linear(int array[], int count, int* lowerlim, int*upperlim, int*maxarraysum);


int main()
{
    std::cout << "Welcome to the test driver for the Project 1 max subarray algorithms." << std::endl;
    std::cout << "This program will use four different algorithms to find the maximum subarray" << std::endl;
    std::cout << "within several input arrays provided in file MSS_Problems.txt." << std::endl;
    
    std::cout << "Opening MSS_TestProblems.txt" << std::endl;
    std::ifstream inputFile;
    std::ofstream outputFile;
    inputFile.open("MSS_TestProblems.txt");
    outputFile.open("MSS_Results.txt");
    if(inputFile.fail()){
        std::cout << "Sorry, the file was not found." << std::endl;
        return 1;
    	}
    int baseArray[20]; //each line in MSS_TestProblems.txt contains less than 20 values
    std::string buffer;
       int line = 1;
       while (getline(inputFile, buffer)){
       		std::istringstream myStream(buffer);
       		int i = 0;
       		int count = 0;
       		while(myStream >> baseArray[i]){
           		i++;
                count++;}
           baseArray[19] = count;
           std::cout << "\nMaximum subarray for line " << line << std::endl;
           outputFile << "\nMaximum subarray for line " << line << std::endl;
           
           //find max subarray using linear time algorithm
           int maxlower;
           int maxupper;
           int maxsum;
           findmax_enum(baseArray, baseArray[19], &maxlower, &maxupper, &maxsum);
           std::cout << "Enumumeration algorithm, lower bound: " << maxlower << " Upper bound: " << maxupper << " Sum: " << maxsum << std::endl;
           outputFile << "Enumumeration algorithm, lower bound: " << maxlower << " Upper bound: " << maxupper << " Sum: " << maxsum << std::endl;
           
           //find max subarray using linear time algorithm
           maxlower = maxupper = maxsum = 0;
           findmax_enum_better(baseArray, baseArray[19], &maxlower, &maxupper, &maxsum);
			std::cout << "Enumumeration algorithm (improved), lower bound: " << maxlower << " Upper bound: " << maxupper << " Sum: " << maxsum << std::endl;
           outputFile << "Enumumeration algorithm (improved), lower bound: " << maxlower << " Upper bound: " << maxupper << " Sum: " << maxsum << std::endl;
           
           //find max subarray using linear time algorithm
           maxlower = maxupper = maxsum = 0;
           findmax_recursive(baseArray, 0, baseArray[19] - 1, &maxlower, &maxupper, &maxsum);
           std::cout << "Recursive algorithm, lower bound: " << maxlower << " Upper bound: " << maxupper << " Sum: " << maxsum << std::endl;
           outputFile << "Recursive algorithm, lower bound: " << maxlower << " Upper bound: " << maxupper << " Sum: " << maxsum << std::endl;
           
           //find max subarray using linear time algorithm
           maxlower = maxupper = maxsum = 0;
           findmax_linear(baseArray, baseArray[19], &maxlower, &maxupper, &maxsum);
           std::cout << "Linear-time algorithm, lower bound: " << maxlower << " Upper bound: " << maxupper << " Sum: " << maxsum << std::endl;
           outputFile << "Linear-time algorithm, lower bound: " << maxlower << " Upper bound: " << maxupper << " Sum: " << maxsum << std::endl;
           
           line++;
       }
    inputFile.close();
    outputFile.close();

    return 0;
}

void findmax_enum(int* array, int size, int* lower, int*upper, int*maxarraysum){
    int ml=0;
    int mu=0;
    int i=0;
    int j=0;
    int max = array[0];
    for (i = 0; i < size; i++){
        for (j = i; j < size; j++){
            int total=0;
            for (int k = i; k <= j; k++){
                total+= array[k];
            }
            if (i == j)
                total -= array[j];
            if (total > max){
                max = total;
                ml=i;
                mu=j;
            }
        }
    }
    *lower = ml;
    *upper = mu;
    *maxarraysum = max;
    return;
}

void findmax_enum_better(int* array, int size, int* lower, int*upper, int*maxarraysum){
    int ml=0;
    int mu=0;
    int i=0;
    int j=0;
    int max = array[0];
    for (i = 0; i < size; i++){
        int total = 0;
        for ( j = i; j < size; j++) {
            total+= array[j];
            if (total > max){
                max = total;
                ml=i;
                mu=j;
            }
        }
    }
    *lower = ml;
    *upper = mu;
    *maxarraysum = max;
    return;
}


void findmaxcrossingsubarray(int* array, int lowerbound, int mid, int upperbound, int* crosslow, int* crosshigh, int* crosssum){
    int leftsum = array[mid];
    int rightsum = array[mid + 1];
    int maxleft = mid;
    int maxright = mid + 1;
    int i;
    int j;
    int sum = 0;
    for (i = mid; i >= lowerbound; i--){
        sum = sum + array[i];
        if (sum > leftsum){
            leftsum = sum;
            maxleft = i;
        }
    }
    sum = 0;
    for (j = mid + 1; j <= upperbound; j++){
        sum = sum + array[j];
        if (sum > rightsum){
            rightsum = sum;
            maxright = j;
        }
    }
    *crosslow = maxleft;
    *crosshigh = maxright;
    *crosssum = leftsum + rightsum;
    return;
}

void findmax_recursive(int* array, int lowerbound, int upperbound, int* lower, int*upper, int*maxarraysum){
    if (lowerbound == upperbound){
        *lower = lowerbound;
        *upper = upperbound;
        *maxarraysum = array[lowerbound];
        return;}
    else{
        int mid = (lowerbound + upperbound ) / 2;
        int leftlow, lefthigh, leftsum;
        findmax_recursive(array, lowerbound, mid, &leftlow, &lefthigh, &leftsum);
        int rightlow, righthigh, rightsum;
        findmax_recursive(array, mid+1, upperbound, &rightlow, &righthigh, &rightsum);
        int crosslow, crosshigh, crosssum;
        findmaxcrossingsubarray(array, lowerbound, mid, upperbound, &crosslow, &crosshigh, &crosssum);
        if ((leftsum >= rightsum) && (leftsum >= crosssum)){
            *lower = leftlow;
            *upper = lefthigh;
            *maxarraysum = leftsum;
            return;
        }
        else if ((rightsum >= leftsum) && (rightsum >= crosssum)){
            *lower = rightlow;
            *upper = righthigh;
            *maxarraysum = rightsum;
            return;
        }
        else{
            *lower = crosslow;
            *upper = crosshigh;
            *maxarraysum = crosssum;
            return;
        }
    }
    return;
}


void findmax_linear(int array[], int count, int* lowerlim, int*upperlim, int*maxarraysum) {
    maxsubarray* s = new maxsubarray[count];
    
    s[0].left = 0;
    s[0].right = 0;
    s[0].sum = array[0];
    
    if(count == 1){
        *lowerlim = s[0].left;
        *upperlim = s[0].right = 0;;
        *maxarraysum = array[0];
        delete [] s;
        return;
    }
    
    for (int i = 1; i < count; i++) {
        if (s[i - 1].sum < 0) {
            s[i].left = i;
            s[i].right = i;
            s[i].sum = array[i];
       	}
        else {
            maxsubarray *previous = &s[i - 1];
            s[i].left = previous->left;
            s[i].right = i;
            s[i].sum = previous->sum + array[i];
        }
    }
    
    maxsubarray *max = &s[0];
    
    for (int i = 1; i < count; i++) {
        if (max->sum < s[i].sum)
            max = &s[i];
    }
    
    *lowerlim = (*max).left;
    *upperlim = (*max).right;
    *maxarraysum = (*max).sum;
    
    delete [] s;
    return;
}




