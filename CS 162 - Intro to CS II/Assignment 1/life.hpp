/*********************************************************************
** Program Filename: life.hpp
** Author: Jessica Spokoyny
** Date: 01/14/16
** Description: header file with function declarations for life.cpp
*********************************************************************/

#ifndef LIFE_HPP
#define LIFE_HPP

#include <iostream>
using namespace std;

void copyArray(int original[80][100], int copy[80][100]);

void buildShape(int arr[80][100], int shape, int row, int col);

#endif