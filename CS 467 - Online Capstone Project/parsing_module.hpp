#ifndef PARSING_MODULE_HPP
#define PARSING_MODULE_HPP

#include <stdlib.h>
#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include "Character.h"
#include "Object.h"
#include "Room.h"
#include "gameLoader.hpp" 

struct Intent {
	std::vector<std::string> verb;
	std::vector<std::string> preposition;
	std::vector<std::string> noun;
	std::vector<int> verbEnumType;
};


enum verbsNum {ELSEIT = 0, go, look, take, help, hint, inventory, talk, arrest, use, enter, knock, drop, hack, drink, saveit, insight, edit, layout}; // Keep this order! Do not jumble

enum roomListCopy{CFAKE,CBAR, CHIDDEN,CPOLICE,CMORGUE,CPHARMACY,CBOBLR,CBOBOFF,	CBOBBR,	CBOBFP,CCLAIRELR,CCLAIREBUNK,CCLAIREBR,
				CCLAIREFP,CBETHLR,CBETHBR,CBETHFP,CSAMLR,CSAMBR,CSAMFP,CTRENTLR,CTRENTBR,CTRENTFP,CMOOSELR,CMOOSEBR,CMOOSEFP,CNUM_OF_ROOMS};

std::string getUserInput();
std::vector<std::string> tokenizeInput(std::string, int);
struct Intent extractIntent(std::vector<std::string>, std::vector<std::string> verbs, std::vector<std::string> nouns, std::vector<std::string> prepositions);
std::string reverseCapitalization(std::string string);
int verbEnumerator(std::string verbs);
std::string nounAliasMassager(std::string noun);
void twoToOneString(struct Intent &intention);
void action(struct Intent &intention, struct gamePkg *game);

template<typename T>
void clearVector(vector<T> &vector) {
	while (!vector.empty())
	{
		vector.pop_back();
	}
}

shared_ptr<Room> find(vector<shared_ptr<Room>> s, std::string name);
shared_ptr<Object> find(vector<shared_ptr<Object>> s, std::string name);
shared_ptr<Character> find(vector<shared_ptr<Character>> s, std::string name);
#endif
