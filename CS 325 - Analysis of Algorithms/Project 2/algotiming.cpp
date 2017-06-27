//
//  main.cpp
//  CS325_Project2
//
//  Created by Edward Francis on 2/2/17.
//  Copyright © 2017 Edward Francis. All rights reserved.
//

#include <vector>
#include <string>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <stdio.h>
#include <chrono>


typedef struct{int coins; std::string values; bool found;} solution;

solution changedp(std::vector<int>* values, int amount);
solution changegreedy(std::vector<int>* values, int amount);
solution changedc(std::vector<int>* values, int amount);

int main(int argc, char *argv[])
{
    
    std::vector<int> values{};
    int startValue = 1;
    int endValue = 300;
    int interval = 1;


    int coinVal;
    
    std::cout << "Welcome to the coin change algorithm timing program." << std::endl;
    
    std::cout << "Please enter your coin values one at a time, followed by a -1 to indicate the end of your set." << std::endl;
    int inputVal = 0;
    
    while(1){
        std::cin >> inputVal;
        if(inputVal == -1)
            break;
        else
        	values.push_back(inputVal);
    }
    
    int* valuesCounts = new int[values.size()];
    for(int i = 0; i < values.size(); i++)
        valuesCounts[i] = 0;
    
    std::cout << "Please enter a start value for A: ";
    std::cin >> startValue;
    std::cout << std::endl;
    std::cout << "Please enter an end value for A: ";
    std::cin >> endValue;
    std::cout << std::endl;
    std::cout << "Please enter an interval between values of A: ";
    std::cin >> interval;
    
    std::cout << "The current coin values in the vector are:" << std::endl;
    for(int i = 0; i < values.size(); i++){
        std::cout << values[i] << " ";}
    std::cout << std::endl;
    std::cout << "The program will calculate coins and running time (ms) for several values of A, based on these settings:" << std::endl;
    std::cout << "Starting value: " << startValue << std::endl;
    std::cout << "Ending value: " << endValue << std::endl;
    std::cout << "Interval: " << interval << std::endl;
    
    std::chrono::time_point<std::chrono::system_clock> start, end;
    std::chrono::duration<double> elapsed_seconds;
    
    std::cout << "Algorithm: DP" << std::endl;
    std::cout << "A\tCoins\tTime\tCoinVals" << std::endl;
    for(int a = startValue; a <= endValue; a +=  interval){
        start = std::chrono::system_clock::now();
        solution result = changedp(&values, a);
        end = std::chrono::system_clock::now();
        elapsed_seconds = end - start;
        
        for(int i = 0; i < values.size(); i++)
            valuesCounts[i] = 0;
        std::stringstream ss(result.values);
        while(ss >> coinVal){
            for(int i = 0; i < values.size(); i++){
            if(coinVal == values[i])
                valuesCounts[i]++;}}
        std::cout << a << "\t" << result.coins <<  "\t" << elapsed_seconds.count() * 1000000  << "\t";
        for(int i = 0; i < values.size(); i++){
            std::cout << valuesCounts[i] << " ";
        }
        std::cout << std::endl;
    }
    
    std::cout << "Algorithm: Greedy" << std::endl;
    std::cout << "A\tCoins\tTime\tCoinVals" << std::endl;
    for(int a = startValue; a <= endValue; a +=  interval){
        start = std::chrono::system_clock::now();
        solution result = changegreedy(&values, a);
        end = std::chrono::system_clock::now();
        elapsed_seconds = end - start;
        
        for(int i = 0; i < values.size(); i++)
            valuesCounts[i] = 0;
        std::stringstream ss(result.values);
        while(ss >> coinVal){
            for(int i = 0; i < values.size(); i++){
                if(coinVal == values[i])
                    valuesCounts[i]++;}}
        std::cout << a << "\t" << result.coins <<  "\t" << elapsed_seconds.count() * 1000000  << "\t";
        for(int i = 0; i < values.size(); i++){
            std::cout << valuesCounts[i] << " ";
        }
        std::cout << std::endl;
    }
    
    std::cout << "Algorithm: Slow" << std::endl;
    std::cout << "A\tCoins\tTime\tCoinVals" << std::endl;
    for(int a = startValue; a <= endValue; a +=  interval){
        start = std::chrono::system_clock::now();
        solution result = changedc(&values, a);
        end = std::chrono::system_clock::now();
        elapsed_seconds = end - start;
        
        for(int i = 0; i < values.size(); i++)
            valuesCounts[i] = 0;
        std::stringstream ss(result.values);
        while(ss >> coinVal){
            for(int i = 0; i < values.size(); i++){
                if(coinVal == values[i])
                    valuesCounts[i]++;}}
        std::cout << a << "\t" << result.coins <<  "\t" << elapsed_seconds.count() * 1000000 << "\t";
        for(int i = 0; i < values.size(); i++){
            std::cout << valuesCounts[i] << " ";
        }
        std::cout << std::endl;
    }
    delete [] valuesCounts;
    return 0;
}

//Dynamic programming algorithm
solution changedp(std::vector<int>* values, int amount){
    
    //set up a table to store solutions to known amounts, and fill in bottom-up from amount 0 to amount requested.
    solution* sTable = new solution[amount + 1];
    
    for(int i = 0; i < amount; i++){
        sTable[i].found = 0;
        sTable[i].coins = -1;
        sTable[i].values = "";}
    
    sTable[0].coins = 0;
    sTable[0].found = 1;
    sTable[0].values = "";
    
    solution outcome;
    
    //build the table from the bottom up
    for(int i= 1; i <= amount; i++){
        int minCoins = amount + 1;
        int newCoin;
        std::string minCoinString = "";
        
        //find the best subproblem solution, if any
        for(int j = 0; j < (*values).size(); j++){
            int index = i - (*values)[j];
            if (index >= 0 && sTable[index].found == 1)
            	{
                if(sTable[index].coins < minCoins){
                        minCoins = sTable[index].coins;
                        minCoinString = sTable[index].values;
                        newCoin = (*values)[j];}
                }
        	}
        
        //if a solution has been found, update table based on earlier entries
        if(minCoins < amount + 1){
            sTable[i].coins = minCoins + 1;
            std::ostringstream newString;
            newString << minCoinString << " " << newCoin;
            sTable[i].values = newString.str();
            sTable[i].found = 1;
        	}
    	else{
            sTable[i].values = "No Solution Found";
            sTable[i].found = 0;
            sTable[i].coins = 0;}
    	}
    
	//update table
    outcome = sTable[amount];
    delete [] sTable;
    return outcome;}

//Greedy algorithm
solution changegreedy(std::vector<int>* values, int amount) {
    solution outcome;
    outcome.values = "";
    outcome.coins = 0;
    int i = (*values).size() - 1;
    while (amount > 0 && i >= 0 ) {
        if (amount >= (*values)[i]) {
        	amount = amount - (*values)[i];
            std::ostringstream newString;
            newString << outcome.values << " " << (*values)[i];
            outcome.values = newString.str();
            outcome.coins++;
            }
        else
            i--;}
    if(amount > 0){
        outcome.values = "No Solution Found";
    }
        
    return outcome;
    }

//Divide and conquer algorithm
solution changedc(std::vector<int>* values, int amount) {
    
    solution outcome;
    outcome.coins = 0;
    outcome.values = "No Solution Found";
    outcome.found = 0;
    
    //base cases
    for(int i = 0; i < (*values).size(); i++){
        if(amount == (*values)[i]){
            std::ostringstream newString;
            newString << (*values)[i];
            outcome.values = newString.str();
            outcome.coins = 1;
            outcome.found = 1;
            return outcome;
        }
    }
    if (amount < (*values)[0]){
        outcome.values = "No Solution Found";
    	outcome.coins = 0;
    	outcome.found = 0;
        return outcome;}

    //holds array of candidate solutions
    solution* solutionsArray = new solution[(*values).size()];
    for (int i = 0; i < (*values).size(); i++)
        solutionsArray[i] = changedc(values, amount - (*values)[i]);
    
    int minVal = amount + 1;
    int index = 0;
    bool foundOne = 0;
    for (int i = 0; i < (*values).size(); i++) {
        if (solutionsArray[i].coins <= minVal && solutionsArray[i].found == 1) {
            minVal = solutionsArray[i].coins;
            index = i;
            foundOne = 1;
        }
    }
    if(foundOne == 1){
        solutionsArray[index].coins++;
        std::ostringstream newString;
        newString << solutionsArray[index].values << " " << (*values)[index];
        solutionsArray[index].values = newString.str();
    	outcome = solutionsArray[index];
    }
    delete [] solutionsArray;
    return outcome;
}
