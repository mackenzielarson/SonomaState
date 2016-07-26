/******************
Mackenzie Larson
3/19/16
Project 01
SyntaticalAnalyzer.h

*******************/

#ifndef SYN_H
#define SYN_H

#include <iostream>
#include <fstream>
#include <string>
#include "LexicalAnalyzer.h"


using namespace std;

class SyntacticalAnalyzer 
{
    public:
	SyntacticalAnalyzer (string filename);
	~SyntacticalAnalyzer ();
    private:
	//			       	LexicalAnalyzer * lex;
	//       	tokenType token;
};
	
#endif
