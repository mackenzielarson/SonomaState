/******************
Mackenzie Larson
3/19/16
Project 01
SyntaticalAnalyzer.cpp

*******************/

#include <iostream>
#include <iomanip>
#include <fstream>
#include "SyntacticalAnalyzer.h"

using namespace std;

SyntacticalAnalyzer::SyntacticalAnalyzer (string filename)
{

  //Open the file in lexical analyzer 
  LexicalAnalyzer lex;
  lex.OpenFile(filename);

  ifstream f;
  f.open(filename.c_str());

  Token* t;

  //While the token does not match the end of file token, report the token based on 
  // line, errors and what the token is 
  while ((t = lex.GetToken(f))->type != EOF_T) {
    lex.ReportLine(t, lex.Line(), lex.Pos(), lex.CommentCount());  
    delete t;
  }
  lex.ReportError(); 
}

SyntacticalAnalyzer::~SyntacticalAnalyzer ()
{
  //   	delete lex;
}
