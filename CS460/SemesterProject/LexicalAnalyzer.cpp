/******************
Mackenzie Larson 
3/19/16
Project 01
LexicalAnalyzer.cpp

*******************/ 

#include <iomanip>
#include <cstdlib>
#include "LexicalAnalyzer.h"
#include "table.h"
#include <iostream>
#include <string>

using namespace std;

static const string Token_names[] = {
  "ERROR_T", "IDENT_T", "INTLIT_T", "FLTLIT_T", "STRLIT_T",
  "CHARLIT_T", "EOF_T", "NL_T", "CR_T", "TAB_T", "PLUS_T", "MINUS_T",
  "MULT_T", "EXP_T", "DIV_T", "IDIV_T", "MOD_T", "LT_T", "GT_T", "LTE_T",
  "GTE_T", "EQUAL_T", "NOTEQ_T", "LPAREN_T", "RPAREN_T", "LBRACKET_T",
  "RBRACKET_T", "LBRACE_T", "RBRACE_T", "AT_T", "COMMA_T", "COLON_T",
  "PERIOD_T", "ASSIGN_T", "SEMI_T", "PLUSEQ_T", "MINUSEQ_T", "MULTEQ_T",
  "DIVEQ_T", "IDIVEQ_T", "MODEQ_T", "EXPEQ_T", "AND_T", "AS_T", "ASSERT_T",
  "BREAK_T", "CLASS_T", "CONT_T", "DEF_T", "DEL_T", "ELIF_T", "ELSE_T", "EXCEPT_T",
  "EXEC_T", "FINALLY_T", "FOR_T", "FROM_T", "GLOBAL_T", "IF_T", "IMPORT_T",
  "IN_T", "IS_T", "LAMBDA_T", "NOT_T", "OR_T", "PASS_T", "RAISE_T", "RETURN_T", "TRY_T", "WHILE_T",
  "WITH_T", "YIELD_T", "TRUE_T", "FALSE_T", "NONE_T", "ABS_T", "ALL_T", "ANY_T", "ASCII_T",
  "BIN_T", "BOOL_T", "BYTEARR_T", "BYTE_T", "CHR_T", "DICT_T", "DIR_T", "DIVMD_T", "ENUMR_T",
  "FILTR_T", "FLOAT_T", "FRMT_T", "FZSET_T", "GATTR_T", "GLBLS_T", "HATTR_T", "HASH_T", "HEX_T",
  "INPUT_T", "INT_T", "ITER_T", "LEN_T"," LIST_T", "MAP_T", "MAX_T", "MIN_T",
  "NEXT_T", "OBJ_T", "OCT_T", "OPEN_T", "POW_T", "PRINT_T", "RANGE_T", "RVS_T",
  "ROUND_T", "SET_T", "SLICE_T", "SRTD_T", "STR_T", "SUM_T", "SUP_T","TUPL_T"			
			       };

const string* Token::token_names = Token_names;

string Token::typeToString(tokenType T) {
  return Token::token_names[T]; 
}

LexicalAnalyzer::LexicalAnalyzer() {
  curLine = 0;
  errors = 0; 
  linecount = 1;
  pos = 0;
  commentcounter= 0; 
}

Token::Token()
{
  type = EOF_T;
  val = "";
}

int LexicalAnalyzer::Line() {
  return linecount; 
}

int LexicalAnalyzer::Pos() {
  return pos; 
}

int LexicalAnalyzer::Errors() {
  return errors; 
}

int LexicalAnalyzer::CommentCount() {
  return commentcounter;
}


void LexicalAnalyzer::OpenFile(string filename)
{
  //Open the input file, create the lst and dbg files 
  //Create the header for the lst and dbg files
  //Initialize the error count 
  input.open( filename.c_str() );
  listing.open( (filename.substr(0,filename.length()-3) + ".lst").c_str() );
  debug.open( (filename.substr(0,filename.length()-3) + ".dbg").c_str() );
  listing << "Project 01 Python Lexical Analysis for file:\t" << filename << endl << endl;
  debug << "Project 01 Python Debug output for file:\t" << filename << endl << endl;
  errors = 0;  
}

LexicalAnalyzer::~LexicalAnalyzer ()
{
  //Will clear the output files and close them  
  listing.flush();
  listing.close();
  debug.flush();
  debug.close();
}

Token* LexicalAnalyzer::GetToken (ifstream& f)
{
  //This function will grab the token (in format THISISATOKEN_T)
  //And find the lexeme associated with that token
  
  //Create a new token each time 
  Token* T =  new Token();
  int state = 0;
  char c; 

  //Handling NEW LINE NL_T & RETURN CR_T
  if (f.peek() == '\n' || f.peek() == '\r'){
      linecount++;
      pos = 0;
  }   

  //Handle tabs
  //In python tabs are 4 spaces...
  //If we count 4 spaces (white space) in a row, we have a tab TAB_T
  //Therefore we must track the white space count 
  int whiteSpace = 0;
  for (int i =0; i < 4; ++i){
    if (f.peek() == ' ' ){
      f.get();
      whiteSpace++;
      pos++; 
    }
    else {
      break;
    }
  } 
  
  //If we have not reached the end of the file, finish finding the token 
  if( !f.eof() ) {
    while( state < 98 ) {
      //If we have found a tab then the lexeme is '\t'
      if (whiteSpace == 4){
	c = '\t';
	pos++; 
      }
      
      //Otherwise, get the lexeme
      else {
	c = f.get();
      }

      
      // Handling comments (state 19)
      if (state == 19){
	state = stateTable[state][GetTokenName(c)];
	if (state == 0){
	  T->val = "";
	  commentcounter++; 
	  f.putback(c);
	  linecount++; 
	}
	
      }
      //Anything else that isnt a comment
      //Get the token name from the state table 
      else {
	state = stateTable[state][GetTokenName(c)];
	T->val += c;
      }
      pos++;
    }

    // Generate the type of the token based on the state
    T->type = static_cast<tokenType>(state-98);
    
    // Putback if the state was not an error state;
    if( state != 98 ) {
      T->val = T->val.substr( 0, T->val.length()-1 );
      T->val += c;
      pos--;
    } else {
      errors += 1;
    }

    //If the token type is found to be an identifier,
    //Go to the function identtotype to get the specific token for that identifier 
    if( T->type == IDENT_T ) {
      T->type = identToType( T->val );
    }
    
    //Handling types that require putback
    //Tokens that require putback are lexemes that might have something following them
    //For example, the > symbol could be on its own or followed by a = (>=) 
    if(T->type == IDENT_T || T->type == INTLIT_T || T->type == FLTLIT_T ||
       T->type == PLUS_T || T->type == MINUS_T || T->type == MULT_T ||
       T->type == EXP_T || T->type == DIV_T || T->type == IDIV_T ||
       T->type == MOD_T || T->type == GT_T || T->type == LT_T ||
       T->type == ASSIGN_T || T->type == PERIOD_T )
      {
	f.putback(c);
	T->val =  T->val.substr(0, T->val.length()-1);
      }
  }
  
  return T;
}


tokenType LexicalAnalyzer::identToType( const string& identifier)
{
  //Identifier to type will have already realized that the token is an identifier
  //It will then match the ident to the proper token name
  //This is a giant if statement 
  tokenType result = IDENT_T;
  string ident = identifier.substr(0, identifier.length() -1);
  //  cout << "\"" << ident << "\"" << endl;
  if( ident == "and") {
    result = AND_T;
  } else if ( ident == "as" ) {
    result = AS_T ;
  } else if ( ident == "assert" ) {
    result = ASSERT_T;
  } else if ( ident == "break" ) {
    result = BREAK_T;
  } else if ( ident == "class" ) {
    result = CLASS_T;
  } else if ( ident == "continue" ) {
    result = CONT_T;
  } else if ( ident == "def" ) {
    result = DEF_T;
  } else if ( ident == "del" ) {
    result = DEL_T ;
  } else if ( ident == "elif" ) {
    result = ELIF_T;
  } else if ( ident == "else" ) {
    result = ELSE_T;
  } else if ( ident == "except" ) {
    result = EXCEPT_T;
  } else if ( ident == "exec" ) {
    result = EXEC_T;
  } else if ( ident == "finally" ) {
    result = FINALLY_T;
  } else if ( ident == "for" ) {
    result = FOR_T ;
  } else if ( ident == "from" ) {
    result = FROM_T;
  } else if ( ident == "global" ) {
    result = GLOBAL_T;
  } else if ( ident == "if" ) {
    result = IF_T;
  } else if ( ident == "import" ) {
    result = IMPORT_T;
  } else if ( ident == "in" ) {
    result = IN_T;
  } else if ( ident == "is" ) {
    result = IS_T ;
  } else if ( ident == "lambda" ) {
    result = LAMBDA_T;
  } else if ( ident == "not" ) {
    result = NOT_T;
  } else if ( ident == "or" ) {
    result = OR_T;
  } else if ( ident == "pass" ) {
    result = PASS_T;
  } else if ( ident == "raise" ) {
    result = RAISE_T;
  } else if ( ident == "return" ) {
    result = RETURN_T ;
  } else if ( ident == "try" ) {
    result = TRY_T;
  } else if ( ident == "while" ) {
    result = WHILE_T;
  } else if ( ident == "with" ) {
    result = WITH_T;
  } else if ( ident == "yield" ) {
    result = YIELD_T;
  } else if ( ident == "TRUE" ) {
    result = TRUE_T;
  } else if ( ident == "FALSE" ) {
    result = FALSE_T ;
  } else if ( ident == "None" ) {
    result = NONE_T;
  } else if ( ident == "abs" ) {
    result = ABS_T;
  } else if ( ident == "all" ) {
    result = ALL_T;
  } else if ( ident == "any" ) {
    result = ANY_T;
  } else if ( ident == "ascii" ) {
    result = ASCII_T;
  } else if ( ident == "bin" ) {
    result = BIN_T ;
  } else if ( ident == "bool" ) {
    result = BOOL_T;
  } else if ( ident == "bytearray" ) {
    result = BYTEARR_T;
  } else if ( ident == "bytes" ) {
    result = BYTE_T;
  } else if ( ident == "chr" ) {
    result = CHR_T;
  } else if ( ident == "dict" ) {
    result = DICT_T;
  } else if ( ident == "dir" ) {
    result = DIR_T ;
  } else if ( ident == "divmod" ) {
    result = DIVMD_T;
  } else if ( ident == "enumerate" ) {
    result = ENUMR_T;
  } else if ( ident == "filter" ) {
    result = FILTR_T;
  } else if ( ident == "float" ) {
    result = FLOAT_T;
  } else if ( ident == "format" ) {
    result = FRMT_T;
  } else if ( ident == "frozenset" ) {
    result = FZSET_T ;
  } else if ( ident == "getattr" ) {
    result = GATTR_T;
  } else if ( ident == "globals" ) {
    result = GLBLS_T;
  } else if ( ident == "hasattr" ) {
    result = HATTR_T;
  } else if ( ident == "hash" ) {
    result = HASH_T;
  } else if ( ident == "hex" ) {
    result = HEX_T;
  } else if ( ident == "input" ) {
    result = INPUT_T ;
  } else if ( ident == "int" ) {
    result = INT_T;
  } else if ( ident == "iter" ) {
    result = ITER_T;
  } else if ( ident == "len" ) {
    result = LEN_T;
  } else if ( ident == "list" ) {
    result = LIST_T;
  } else if ( ident == "map" ) {
    result = MAP_T;
  } else if ( ident == "max" ) {
    result = MAX_T ;
  } else if ( ident == "min" ) {
    result = MIN_T;
  } else if ( ident == "next" ) {
    result = NEXT_T;
  } else if ( ident == "object" ) {
    result = OBJ_T;
  } else if ( ident == "oct" ) {
    result = OCT_T;
  } else if ( ident == "open" ) {
    result = OPEN_T;
  } else if ( ident == "pow" ) {
    result = POW_T ;
  } else if ( ident == "print" ) {
    result = PRINT_T;
  } else if ( ident == "range" ) {
    result = RANGE_T;
  } else if ( ident == "reversed" ) {
    result = RVS_T;
  } else if ( ident == "round" ) {
    result = ROUND_T;
  } else if ( ident == "set" ) {
    result = SET_T;
  } else if ( ident == "slice" ) {
    result = SLICE_T ;
  } else if ( ident == "sorted" ) {
    result = SRTD_T;
  } else if ( ident == "str" ) {
    result = STR_T;
  } else if ( ident == "sum" ) {
    result = SUM_T;
  } else if ( ident == "super" ) {
    result = SUP_T;
  } else if ( ident == "tuple" ) {
    result = TUPL_T;
  }

  return result;
  
}

int LexicalAnalyzer::GetTokenName ( const char& c)
{
  // This function will return the token name string for the token

  //c corresponds to a state in the state table 
  int result = 0; 
  // Alphabet state (2)
  if( (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')  ) {
    result = 2;
  }
  // Numeric State (1)
  else if( (c >= '0' && c <= '9') ) {
      result = 1;
    }
  //Special char states
  else {
      switch( c ) {
      case '\n':
	result = 4;
	break;
      case '\r':
	result = 5;
	break;
      case '\t':
	result = 6;
	break;
      case ' ':
	result = 0;
	break;
      case '_':
	result = 3;
	break;
      case '.':
	result = 25;
	break;
      case '+':
	result = 7;
	break;
      case '-':
	result = 8;
	break;
      case '/':
	result = 10;
	break;
      case '*':
	result = 9;
	break;
      case '%':
	result = 11;
	break;
      case '=':
	result = 14;
	break;
      case '<':
	result = 12;
	break;
      case '>':
	result = 13;
	break;
      case '"':
	result = 27;
	break;
      case '\'':
	result = 28;
	break;
      case '\\':
	result = 29;
	break;
      case '#':
	result = 30;
	break;
      case '(':
	result = 16;
	break;
      case ')':
	result = 17;
	break;
      case '[':
	result = 18;
	break;
      case ']':
	result = 19;
	break;
      case '{':
	result = 20;
	break;
      case '}':
	result = 21;
	break;
      case '@':
	result = 22;
	break;
      case ',':
	result = 23;
	break;
      case ';':
	result = 26;
	break;
      case ':':
	result = 24;
	break;
      case '!': result = 15;
	break;
      default: result = 31;
	break;
      }
    }
  return result; 
}


void LexicalAnalyzer::ReportLine(Token* t, int linecount, int pos, int commentcounter)
{

  //Print the line from the orig. program
  /*  if(commentcounter > 0 && linecount != curLine){
    linecount--;
    curLine++;
    string line;
    getline(input, line);
    listing << linecount << "\t" << line << endl;
    debug << linecount << "\t" << line << endl; 
    commentcounter = 0;
    linecount++;     
  }
  */

  //linecount++; 

  //Print the line to the .lst and .dbg files
  if(linecount > curLine)
    {
     
      string line;
      getline( input, line );
      listing << linecount << "\t" << line << endl;
      debug   << linecount << "\t" << line << endl;
      curLine++; 
      
    }
  //New line is a special case so print the token and a custom lexeme 
  if(Token::typeToString(t->type) == "NL_T"){
    debug << linecount << "\t" << "\t" << Token::typeToString( t->type ) << "\t" << "\\n" << endl;
  }

  //Report the error where it happens 
  else if( Token::typeToString(t->type) == "ERROR_T" ) {
    debug << "Error: Invalid character '" << t->val << "' at " << linecount << "," << pos << endl;
    debug << linecount << "\t"  << "\t" << Token::typeToString( t->type ) << "\t" << t->val << endl;
    listing   << "Error: Invalid character '" << t->val << "' at " << linecount << "," << pos << endl;
  }

  //if the token type wasn't an error, report the token and lexeme
  else {
    //    linecount++; 
    ReportListing( t, linecount, pos );
    }  
  
}

//Will print the tokens and lexemes associated with each line
void LexicalAnalyzer::ReportListing(Token* t, int linecount, int pos)
{

  //The first three statements are special cases to print lexemes (new line, tab and return)
  if(Token::typeToString(t->type) == "NL_T"){
    debug << linecount << "\t" << "\t" << Token::typeToString( t->type ) << "\t" << "\\n" << endl;
  }
  
  else if(Token::typeToString(t->type) == "TAB_T"){
    debug << linecount << "\t" << "\t" << Token::typeToString( t->type ) <<  "\t" << "\\t" << endl;
  }

  else if(Token::typeToString(t->type) == "CR_T"){
    debug << linecount << "\t" << "\t" << Token::typeToString( t->type ) << "\t" << "\\r" << endl;
  } 

  //print the tokens and lexemes corresponding to everything else!
  else {
    debug << linecount << "\t"  << "\t" << Token::typeToString( t->type ) << "\t" << t->val << endl;
  }

}

//Print the errors to the command line
// dbg and lst files 
void LexicalAnalyzer::ReportError() {
  debug << " " << endl;
  listing << " " << endl; 
  debug << errors << " Error(s) found in input file" << endl;
  listing << errors << " Error(s) found in input file" << endl; 

  cout << errors << " Error(s) found in input file" << endl; 
}
