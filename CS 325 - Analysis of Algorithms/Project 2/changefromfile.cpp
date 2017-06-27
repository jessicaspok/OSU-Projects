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

typedef struct{int coins; std::string values; bool found;} solution;

solution changedp(std::vector<int>* values, int amount);
solution changegreedy(std::vector<int>* values, int amount);
solution changedc(std::vector<int>* values, int amount);

int main(int argc, char *argv[])
{

    std::vector<int> values;
    int amount;
    std::fstream sourceFile;
    std::string line;
    int lineCount = 0;
    int getCoinVal;
    
    std::ofstream outputFile;
    std::string outputFileName;
    
    //open input file
    sourceFile.open(argv[1]);
    if(sourceFile.fail())
    { std::cout << "Sorry, source file cannot be opened." << std::endl; return 1;}
    
    //open output file - leave it open until all three algorithms have been applied to the data in the input file
    outputFileName = argv[1];
    int pointIndex = outputFileName.find_last_of(".");
    outputFileName = outputFileName.substr(0, pointIndex);
    outputFileName += "change.txt";
    outputFile.open(outputFileName.c_str(), std::fstream::app);
    if(outputFile.fail()){
        std::cout << "Sorry, file error" << std::endl;
        return 1;}

    
    //THIS SECTION CALLS THE DYNAMIC PROGRAMMING ALGORITHM AND WRITES OUT THE RESULTS TO OUTPUT FILE

    //call make change algorithm after reading each amount.
    //get each line from input file. treat even lines as coin values, odd lines as amounts to make.
    outputFile << std::endl <<  "Algorithm changedp:" << std::endl;
    while (std::getline(sourceFile, line)){
        std::stringstream curLine(line);
        if (lineCount % 2 == 0){
            values.clear();
        	while (curLine >> getCoinVal)
            	values.push_back(getCoinVal);
        	}
        if (lineCount % 2 == 1){
            curLine >> amount;
            solution result = changedp(&values, amount);
            for(int i = 0; i < values.size(); i++)
                outputFile << values[i] << " ";
        	outputFile << std::endl;
            int *coinCounts = new int[values.size()];
            for (int i = 0; i < values.size(); i++)
                coinCounts[i] = 0;
            std::stringstream str(result.values);
            int temp;
            while (str >> temp){
                for (int i = 0; i < values.size(); i++)
                    if(values[i] == temp)
                        coinCounts[i]++;}
            for(int i = 0; i < values.size(); i++)
                outputFile << coinCounts[i] << " ";
            outputFile << std::endl << result.coins;
            outputFile << std::endl << std::endl;
            delete [] coinCounts;
        	}
        lineCount++;
    }
    sourceFile.close();
    
    
    //THIS SECTION CALLS THE GREEDY ALGORITHM AND WRITES OUT THE RESULTS TO OUTPUT FILE
    
    //open input file
    sourceFile.open(argv[1]);
    if(sourceFile.fail())
    { std::cout << "Sorry, file cannot be opened." << std::endl; return 1;}
    
    //call make change algorithm after reading each amount.
    outputFile << std::endl <<  "Algorithm changegreedy:" << std::endl;
    while (std::getline(sourceFile, line)){
        std::stringstream curLine(line);
        if (lineCount % 2 == 0){
            values.clear();
            while (curLine >> getCoinVal)
                values.push_back(getCoinVal);
        }
        if (lineCount % 2 == 1){
            curLine >> amount;
            solution result = changegreedy(&values, amount);
            for(int i = 0; i < values.size(); i++)
                outputFile << values[i] << " ";
            outputFile << std::endl;
            int *coinCounts = new int[values.size()];
            for (int i = 0; i < values.size(); i++)
                coinCounts[i] = 0;
            std::stringstream str(result.values);
            int temp;
            while (str >> temp){
                for (int i = 0; i < values.size(); i++)
                    if(values[i] == temp)
                        coinCounts[i]++;}
            for(int i = 0; i < values.size(); i++)
                outputFile << coinCounts[i] << " ";
            outputFile << std::endl << result.coins;
            outputFile << std::endl << std::endl;
            delete [] coinCounts;
        }
        lineCount++;
    }
    sourceFile.close();
    
    //THIS SECTION CALLS THE SLOW (DIVIDE AND CONQUER) ALGORITHM AND WRITES OUT THE RESULTS TO OUTPUT FILE
    
    //open input file
    sourceFile.open(argv[1]);
    if(sourceFile.fail())
    { std::cout << "Sorry, file cannot be opened." << std::endl; return 1;}
    //call make change algorithm after reading each amount.
    outputFile << std::endl <<  "Algorithm changeslow:" << std::endl;
    while (std::getline(sourceFile, line)){
        std::stringstream curLine(line);
        if (lineCount % 2 == 0){
            values.clear();
            while (curLine >> getCoinVal)
                values.push_back(getCoinVal);
        }
        if (lineCount % 2 == 1){
            curLine >> amount;
            solution result = changedc(&values, amount);
            for(int i = 0; i < values.size(); i++)
                outputFile << values[i] << " ";
            outputFile << std::endl;
            int *coinCounts = new int[values.size()];
            for (int i = 0; i < values.size(); i++)
                coinCounts[i] = 0;
            std::stringstream str(result.values);
            int temp;
            while (str >> temp){
                for (int i = 0; i < values.size(); i++)
                    if(values[i] == temp)
                        coinCounts[i]++;}
            for(int i = 0; i < values.size(); i++)
                outputFile << coinCounts[i] << " ";
            outputFile << std::endl << result.coins;
            outputFile << std::endl << std::endl;
            delete [] coinCounts;
        }
        lineCount++;
    }
    sourceFile.close();
    outputFile.close();
    
    
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
