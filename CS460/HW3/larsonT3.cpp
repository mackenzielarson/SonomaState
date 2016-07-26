/***********************
Author: Mackenzie Larson 
WATTS 460 HOMEWORK 3
larsonH3.cpp
This program uses the fraction class to sort and 
compute operations using a list of fractions from a .txt file
***********************/

#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstdlib>
#include <sstream>
#include <set>
#include <vector>
#include <algorithm>
#include "SetLimits.h"
#include "fraction.h"

using namespace std;

int main (int argc, char * argv[])
{
  //Check to see if there was an input file name 
  if (argc < 2)
    {
      cout << "Usage: "<< argv[0] << " <filename>. **Missing filename**\n";
      exit (1);
    }

  //Open the input file
  ifstream input(argv[1]);

  //Check to see if the file was successfully opened
  //Exit if no file found
  if (input.fail())
    {
      cout << "File: " << argv[1] << " not found\n";
      exit(2);
    }

  //Read in fractions from file into vector
  Fraction readin;
  vector<Fraction> v_fraction;
  while (!input.eof()){
    string line;
    getline(input, line);
    if (line == "")
      break;
  
    istringstream ss = istringstream(line);

    ss >> readin;

    v_fraction.push_back(readin);
  }

  //Other operator tests
  cout << "OPERATOR TESTS: " << endl; 
  Fraction t1 = v_fraction[0];
  cout << "\nFRACTION t1 = " << t1; 
  Fraction t2 = v_fraction[1];
  cout << "\nFRACTION t2 = " << t2; 
  Fraction t3 = t1 + t2; 
  cout << "\nTESTING +: t1 + t2: " << t3; 
  Fraction t4 = t1 - t2; 
  cout << "\nTESTING -: t1 - t2: " << t4;
  Fraction t5 = t1 / t2;
  cout << "\nTESTING /: t1 / t2: " << t5; 
  Fraction t6 = t1 * t2;
  cout << "\nTESTING *: t1 * t2: " << t6 << endl; 

  if (t1 == t2)
    cout << "TESTING ==: t1 does equal t2 (TRUE)" << endl;
  else
    cout << "TESTING ==: t1 does NOT equal t2 (FALSE)" << endl;

  if (t1 != t2)
    cout << "TESTING !=: t1 does not equal t2 (TRUE)" << endl;
  else
    cout << "TESTING !=: t1 does equal t2 (FALSE)" << endl;

  if (t1 < t2)
    cout << "TESTING <: t1 is less than t2 (TRUE)" << endl;
  else
    cout << "TESTING <: t1 is NOT less than t2 (FALSE)" << endl;
  
  if (t1 <= t2)
    cout << "TESTING <=: t1 is less than or equal to t2 (TRUE)" << endl;
  else
    cout << "TESTING <=: t1 is NOT less than or equal to t2 (FALSE)" << endl;

  if (t1 > t2)
    cout << "TESTING >: t1 is greater than t2 (TRUE)" << endl;
  else
    cout << "TESTING >: t1 is NOT greater than t2 (FALSE)" << endl;
  
  if (t1 >= t2)
    cout << "TESTING >=: t1 is greater than or equal to t2 (TRUE)" << endl;
  else
    cout << "TESTING >=: t1 is NOT greater than or equal to t2 (FALSE)" << endl;

  cout << " " << endl;
  
  //BEFORE SORTING OPERATIONS
  cout << "Before sorting: ";

  Fraction Valid(); 

  Fraction sum;
  for (int i = 0; i < v_fraction.size(); i++) {
    sum += v_fraction[i]; 
  }
  sum.Valid(); 
  if (sum.Valid() == true)
    {
      cout << "\n\tThe sum of the fractions is: " << sum << " (valid)";
    }
  if (sum.Valid() == false)
    {
      cout << "\n\tThe sum of the fractions is: " << sum << " (NOT valid)";
    }
  
  Fraction difference = v_fraction[0];
  for (int i = 1; i < v_fraction.size(); i++) {
    difference -= v_fraction[i];
  }
  difference.Valid(); 
  if (difference.Valid() == true)
    {
      cout << "\n\tThe difference of the fractions is: " << difference << " (valid)";
    }
  if (difference.Valid() == false)
    {
      cout << "\n\tThe difference of the fractions is: " << difference << " (NOT valid)";
    }
  
  Fraction product;
  for (int i = 0; i < v_fraction.size(); i++) {
    product *= v_fraction[i];
  }
  product.Valid(); 
  if (product.Valid() == true)
    {
      cout << "\n\tThe product of the fractions is: " << product << " (valid";
    }
  if (product.Valid() == false)
    {
      cout << "\n\tThe product of the fractions is: " << product << " (NOT valid)";
    }
  
  Fraction quotient = v_fraction[0];
  for(int i = 1; i < v_fraction.size(); i++){
    quotient /= v_fraction[i];
  }
  quotient.Valid(); 
  if (quotient.Valid() == true)
    {
      cout << "\n\tThe quotient of the fractions is: " << quotient << " (valid)";
    }
  if (quotient.Valid() == false)
    {
      cout << "\n\tThe quotient of the fractions is: " << quotient << " (NOT valid)";
    }
  

  //SORT THE FRACTIONS
  //Using built in sort function 
  sort(v_fraction.begin(), v_fraction.end());
  

  //Reset sum product and difference
  sum = Fraction(0,0,1); 
  product = Fraction(0,0,1);
  difference = Fraction(0,0,1);

  //OPERATIONS AFTER SORT
  for (int i = 0; i < v_fraction.size(); i++) {
    sum += v_fraction[i];
    product *= v_fraction[i];
  }
  
  Fraction diffaftersort = v_fraction[0];
  for (int i = 0; i < v_fraction.size() - 1; i++) {
    diffaftersort -= v_fraction[i+1];
  }

  Fraction quotAfterSort = v_fraction[0];
  for(int i = 1; i < v_fraction.size(); i++) {
    quotAfterSort /= v_fraction[i];
  }
  
  //AFTER SORT
  cout << "\nAfter sorting: ";
  sum.Valid();
  diffaftersort.Valid();
  product.Valid();
  quotAfterSort.Valid(); 
  if (sum.Valid() == true)
      cout << "\n\tThe sum of the fractions is: " << sum << " (valid)";
  if (sum.Valid() == false)
      cout << "\n\tThe sum of the fractions is: " << sum << " (NOT valid)";
  if (diffaftersort.Valid() == true)
    cout << "\n\tThe difference of the fractions is: " << diffaftersort << " (valid)";
  if (diffaftersort.Valid() == false)
    cout << "\n\tThe difference of the fractions is: " << diffaftersort << " (NOT valid)";
  if (product.Valid() == true)
      cout << "\n\tThe product of the fractions is: " << product << " (valid";
  if (product.Valid() == false)
      cout << "\n\tThe product of the fractions is: " << product << " (NOT valid)";
  if (quotAfterSort.Valid() == true)
      cout << "\n\tThe quotient of the fractions is: " << quotAfterSort << " (valid)";
  if (quotAfterSort.Valid() == false)
      cout << "\n\tThe quotient of the fractions is: " << quotAfterSort << " (NOT valid)";
  
  cout << "\n"; 
  
  //PRINT LIST OF SORTED FRACTIONS (ALSO REDUCED)
  for (int i = 0; i < v_fraction.size(); i++) {
    cout << "\n" << v_fraction[i];
  }
  cout << "\n"; 

  input.close();

  SetLimits();
  
  return 0;
}
 

