/******************
Mackenzie Larson
3/19/16
Project 01
LexicalAnalyzer.h

*******************/

#ifndef LEX_H
#define LEX_H

#include <iostream>
#include <fstream>
#include <string>
#include "SyntacticalAnalyzer.h"

using namespace std;

enum tokenType {
  ERROR_T, IDENT_T, INTLIT_T, FLTLIT_T, STRLIT_T,
  CHARLIT_T, EOF_T, NL_T, CR_T, TAB_T, PLUS_T, MINUS_T,
  MULT_T, EXP_T, DIV_T, IDIV_T, MOD_T, LT_T, GT_T, LTE_T,
  GTE_T, EQUAL_T, NOTEQ_T, LPAREN_T, RPAREN_T, LBRACKET_T,
  RBRACKET_T, LBRACE_T, RBRACE_T, AT_T, COMMA_T, COLON_T,
  PERIOD_T, ASSIGN_T, SEMI_T, PLUSEQ_T, MINUSEQ_T, MULTEQ_T,
  DIVEQ_T, IDIVEQ_T, MODEQ_T, EXPEQ_T, AND_T, AS_T, ASSERT_T,
  BREAK_T, CLASS_T, CONT_T, DEF_T, DEL_T, ELIF_T, ELSE_T, EXCEPT_T,
  EXEC_T, FINALLY_T, FOR_T, FROM_T, GLOBAL_T, IF_T, IMPORT_T,
  IN_T, IS_T, LAMBDA_T, NOT_T, OR_T, PASS_T, RAISE_T, RETURN_T, TRY_T, WHILE_T,
  WITH_T, YIELD_T, TRUE_T, FALSE_T, NONE_T, ABS_T, ALL_T, ANY_T, ASCII_T,
  BIN_T, BOOL_T, BYTEARR_T, BYTE_T, CHR_T, DICT_T, DIR_T, DIVMD_T, ENUMR_T,
  FILTR_T, FLOAT_T, FRMT_T, FZSET_T, GATTR_T, GLBLS_T, HATTR_T, HASH_T, HEX_T,
  INPUT_T, INT_T, ITER_T, LEN_T, LIST_T, MAP_T, MAX_T, MIN_T,
  NEXT_T, OBJ_T, OCT_T, OPEN_T, POW_T, PRINT_T, RANGE_T, RVS_T,
  ROUND_T, SET_T, SLICE_T, SRTD_T, STR_T, SUM_T, SUP_T, TUPL_T

};

class Token {
 public:
  Token();
  static const string* token_names;
  static string typeToString(tokenType T);
  tokenType type;
  string val;
  
};

class LexicalAnalyzer 
{
    public:
        LexicalAnalyzer(); 
	~LexicalAnalyzer ();

	void OpenFile (string filename); 
	
	int Line();
	int Pos();
	int Errors(); 
	int CommentCount();
	
	Token* GetToken (ifstream& f); 
	tokenType identToType(const string& ident); 
	int GetTokenName (const char& c);
	string GetLexeme () const; 	
	
	//Error reporting 
	void ReportLine(Token* t, int linecount, int pos, int commentcounter);
	void ReportListing(Token* t, int linecount, int pos);
	void ReportError(); 

   private:
	ifstream input;
	ofstream listing;
	ofstream debug;
	tokenType token;
	string line;
       	string lexeme;
	int errors, curLine, linecount, pos, commentcounter;
};
	
#endif
