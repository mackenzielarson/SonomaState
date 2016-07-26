/************************************************
0;136;0cAuthor: Mackenzie Larson 
Assignment: HW 1 CS460 Programming languages
Date: 1/30/16
Description: 
This program will read in a list of fractions from a .txt file in the format wholenumber numerator/denominator \n
The program will then sort the fractions into ascending order while also reducing the fractions. 

NOTE / UPDATE: 
* Development time = roughly 5-6 hours (I had to research tokens/ fraction rules as I am a bit rusty!) 

Didn't realize this HW was not to be comiled with c++ 11... 
RUN: g++ filename.cpp
Old code to run c++11 still there in comments :) 

NEW UPDATE: 
First submission was so slow (bubble sort) that it did not complete the last two test cases. 
I am using the c++ built in sort function this time around to improve on speed(hopefully)! 

 ***********************************************/ 
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstdlib>
#include <sstream>
#include <string> 
#include <vector>
#include <algorithm>

using namespace std;
e
//Definition of numdata struct
struct fraction
{
  int whole;
  float numerator;
  float denominator;
  int gcf; 
  int temp; 
  float decimal; 
};

//Prototypes for functions used by my program
int ReadFile (ifstream & input); 

//Sort by comparing decimals
bool DecimalSort(const fraction &a, const fraction &b)
{
  return a.decimal < b.decimal;
}

//Main Function 
int main (int argc, char * argv[])
{
  //Check to see if the user entered an input file name
  //Exit if no file name
  if (argc < 2)
    {
      cout << "Usage: "<< argv[0] << " <filename>. **Missing filename**\n";
      exit(1);
    }

  //Open the input file
  ifstream input (argv[1]);

  //Check to see if the file was successfully opened
  //Exit if no file found
  if (input.fail())
    {
      cout << "File: " << argv[1] << " not found\n";
      exit(2); 
    }

  //Function call to read function 
  ReadFile (input); 

  //Close file
  input.close ();

  return 0; 
}

int ReadFile(ifstream & infile)
{

  //Set up array for my fractions 
  vector <fraction> array;
  string line;

  //Tokenize string to see what are the numbers and what is whitespace
  //Will then use tokens to separate the whole number from the fraction portion 
  fraction input; 

  if (infile.is_open())
    {
      while ( getline (infile,line) )
	{
	  istringstream isstring(line);
	  string number; 
	  vector <string> token;

	  //Will separate the whole number and the fraction per line 
	  while (isstring >> number){
	    token.push_back(number); 
	  }

	  //Using string stream to take in the tokens and translate them to floats/ ints
	  //CANNOT USE STOI OR STOF bc not using c++11 to compile 
	  stringstream ss;
	  stringstream ssn; 
	  stringstream ssn2; 
	  //token[0] is the wholenumber and token[1] is the "fraction" part of the string
	  //find the denominator-- grab the second token, find the "/" symbol and look at everything beyond it until the line ends
	  float denominator; 
	  ss << token[1].substr(token[1].find("/") + 1); 
	  ss >> denominator;
	 
	  //Old code from c++11 attempt-- keeping for future reference 
	  //float denominator = stof(token[1].substr(token[1].find("/") + 1)); 

	  //NUMERATOR
	  //Same principle as the denominator, start bu finding the "/" and looking at everything before it that wasn't the whole numer
	  //We do need to grab the whole nmber token[0] to go to improper fraction land
	  float numerator;
	  float numer1;
	  float numer2;
	  
	  ssn << token[1].substr(0, token[1].find("/"));
          ssn2 << token[0];
	  
	  ssn >> numer1;
	  ssn2 >> numer2;

	  //Check if the whole num is neg or positive and properly go to improper by either mulitplying -1 to the numerator if the whole number was negative or not
	  if (numer2 < 0)
	    {
	      numerator = (-1 * numer1) + numer2 * denominator;
	    }
	  else
	    {
	      numerator = numer1 + numer2 * denominator; 
	    }
	  
	  //Reduce the fraction before storing/storing it
	  //How to reduce a fraction?
	  //Use the greatest common factor of the numerator and the denominator! 
	  int gcf;
	  if (numerator  == 0 && denominator == 0)
	    {
	      gcf = 1;
	    }
	  else if (denominator == 0)
	    {
	      gcf = numerator;
	    }
	  else if (numerator != 0 && numerator >0) {
	    int a = numerator, b = denominator;
	    while ( a != b)
	      if ( a < b )
		b -= a;
	      else
		a -= b;
	    gcf = b;
	  }
	  else if (numerator != 0 && numerator < 0) {
	    int a = numerator * -1, b = denominator;
	    while ( a != b)
	      if ( a < b )
		b -= a;
	      else
		a -= b;
	    gcf = b;
	  }
	  
	  //I will later divide the numer and denom by the gcd to reduce them when printed 
	  //for now, sotre the gcf
	  input.gcf = gcf;

	  //Convert the fraction to decimal to make sorting easier/faster
	  float decimal; 
	  int wholenum = numerator/denominator; 
	  decimal = wholenum + (numerator/(double)denominator);
	  input.decimal = decimal;
	  
	  //store everything back into their proper variables
	  input.denominator = denominator;
	  input.numerator = numerator;
	  array.push_back(input); 
	}
      //Close the file 
      infile.close();
    }
 
  //Using the built in c++ sort function for my sort algorithm
  //Sorting by comparing the decimal values of the fractions
  sort(array.begin(), array.end(), DecimalSort);
 
  for (int i = 0; i < array.size(); ++i)
    {
      
      //Using this example: 3 2/3; when the fraction is inproper, it is 11/3
      //The whole number: The numerator divided by the denominator: 11 / 3 = 3 
      //The numerator: The numerator % denominator (the remainder): 11 % 3 = 2
      //The denominator: Simply call the stored denominator: 3
      int wholenum =(int)array[i].numerator/(int)array[i].denominator;
      int numerator = ((int)array[i].numerator % (int)array[i].denominator) / (int)array[i].gcf;
      int denominator = (int)array[i].denominator /(int)array[i].gcf; 

      // Remove cases of double negative i.e. -2 -2/4 will simplify to -2 1/2 
            if (wholenum < 0)
	      {
		numerator = abs(numerator); 
	      } 

      //Print the final fraction 
            cout << wholenum << " " << numerator << "/" << denominator << endl; 

	    //cout decimal to check the order of the fractions
	    // cout << (float)array[i].decimal << endl; 
    }
  return 0; 
}
