/*************************
Author: Mackenzie Larson 
Date: 3/18/16 
Class: CS454 
 g++ LarsonP1Ex3.cpp  -std=c++11
PROBLEM 3: 
Write a program that takes as input a string w (over the alphabet{a,…,z})and out puts a
regular expression R such that L(R)includes all strings that are at edit- distance 1 from w.
(A string is said to be at edit-distance 1 from w if performing one of the operations listed
below on produces w:(a)replace one letter of s by an arbitrary letter,(b)delete a letter
of s, or (c)insert a new letter in any position of s.For example,dg,dogs,dag have edit distance
1 from dog.But god,dagretc.are not at edit distance 1 from dog.)

*************************/
#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include <iomanip>
using namespace std;

int main ()
{
  string s; 
  cout << "What string would you like to enter? " << endl;
  cin >> s; 

  cout << "Original string was: " << s <<endl;
  cout << "Your grep statement is: " << endl;
  cout << "egrep ' " ; 

  //Replace a letter in a string
  //We want to replace a letter in the string but it cannot match the current letter (we don't want the
  //output the include the original string because the original isn't edit distance 1 away from the original)
  // [^i] means that the regex will include all letters except "i"
  //Example: Dog with the following replace would be "[^d]og | d[^o]g | do[^g]"
  //string s = "dog";
  //cout << "Replace a letter of the string: " << endl; 
  for (int i  =0; i < s.size(); i++){
    //Save the original string 
    string orig = s;
    string a = "[";
    string b = "^";
    string c = "]";
    string temp = " "; 
    temp = s[i];
    //create the string with format "[^x]" 
    string final = a + b + temp + c; 

    s.erase(s.begin()+i);
    s.insert(i, final);
    cout << "^" << s << "$|";
    //Erase the new string and start over with a fresh string 
    s.erase(i); 
    s = orig; 
    cout << "";
  }

  //Remove a letter from any point of the string
  //Example: Dog with the following deletion would be  "og | dg | do" 
  //cout << "Remove a letter from the string" << endl;
  for (int i = 0; i < s.size(); i++) {
    string temp = " ";
    temp = s[i];
    s.erase(s.begin()+i);
    cout << "^" <<s << "$|";
    s.insert(i, temp);
  }

  //Insert a letter into any point of the input string
  //Example: Dog with the following insertion would be ".dog | d.og | do.g " 
  // cout << "Insert a letter into any point of the string" << endl;
  for (int i = 0; i < s.size(); i++){
    char instr = '.'; 
    s.insert(i, 1, instr); 
    cout << "^" << s << "$|";
    s.erase(s.begin()+i); 
  }
  //Final case, insert a "." at the end of the input string for the last insertion
  //Example: Dog with the following would result in the final insertion case (after last char in string " | dog. "
  cout << "^" << s << ".$'" << endl; 
  
  return 0; 
}
