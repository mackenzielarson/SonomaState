/****************************
Author: Mackenzie Larson 
WATTS 460 HOMEWORK 3
fraction.cpp
This program is the creation of a usable fraction class
Operators in this file include: 
+ - * / += -= *= /= != == > < >= <= 
***************************/ 

#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <vector> 
#include <string>
#include <algorithm>
#include <stdlib.h>
#include <cstdlib>
#include "fraction.h"

using namespace std;

Fraction::Fraction()
{
  numerator = 0;
  denominator = 1;
  whole = 0; 
  decimal = 0.0; 
}

Fraction::Fraction(int numerator, unsigned denominator)
{
  this->numerator = numerator;
  this->denominator = denominator; 
}

Fraction::Fraction(int whole, unsigned numerator, unsigned denominator)
{  
  if(whole < 0)
    this->numerator = -(numerator) + (whole * int(denominator));
  else 
    this -> numerator = numerator + (whole * int(denominator));
  this -> denominator = denominator; 
  this->whole = whole;
  //  cout << this->whole << " " << this->numerator << "/" << this->denominator << endl;
}

Fraction::Fraction(float)
{
  this->decimal = decimal; 
}

bool Fraction::Valid() const
{
  if(denominator == 0)
    return false;
  if(whole != 0 && numerator < 0)
    return false;
  else
    return true;  
}

int Fraction::Whole() const
{
  return this->numerator/int(this->denominator);
}

int Fraction::Numerator() const
{
  return numerator;
}

unsigned Fraction::Denominator() const
{
  return denominator; 
}

//Equals operator
//Will check to see if fraction a == fraction b
bool Fraction::operator == (const Fraction &f) const
{
  //Convert the first fraction to improper (easier to compare) 
  int firstnumer = 0;
  int firstden = 0;
  if (whole < 0)
    firstnumer = (whole * denominator) - numerator;
  else
    firstnumer = (whole * denominator) + numerator;
  firstden = denominator;

  //Convert the second fraction to improper (easier to compare both fractions)
  int otherNumer = 0;
  int otherDen = 0; 
  if (f.whole < 0)
    otherNumer = (f.whole * f.denominator) - f.numerator;
  else
    otherNumer = (f.whole * f.denominator) + f.numerator;
  otherDen = f.denominator;

  //If fraction 1 numerator equals fraction 2's numerator and same for both denominators,
  //Then (true) the == operator is true
  //If one or neither of the cases is true, the == operator is not right
  if (firstnumer == otherNumer && firstden == otherDen)
    return true;
  else  
    return false; 
   
}

//Not equals operator
bool Fraction::operator != (const Fraction &f) const
{
  
  //Convert both fractions to improper (easier to compare)
  int firstnumer = 0;
  int firstden = 0;
  if (whole < 0)
    firstnumer = (whole * denominator) - numerator;
  else
    firstnumer = (whole * denominator) + numerator;
  firstden = denominator;

  int otherNumer = 0;
  int otherDen = 0;
  if (f.whole < 0)
    otherNumer = (f.whole * f.denominator) - f.numerator;
  else
    otherNumer = (f.whole * f.denominator) + f.numerator;
  otherDen = f.denominator;

  //If the numerator does not equal the other numerator
  //of the denominator does not equal the other denominator then != holds true 
  if (firstnumer != otherNumer || firstden != otherDen)
    return true;
  else
    return false; 
   
}

//Less than operator 
bool Fraction::operator < (const Fraction &f) const
{
  
  //Convert both fractions to improper as this is easier to compare than mixed 
  int firstnumer = 0;
  int firstden = 0;
  if (whole < 0)
    firstnumer = (whole * denominator) - numerator;
  else
    firstnumer = (whole * denominator) + numerator;
  firstden = denominator;

  int otherNumer = 0;
  int otherDen = 0;
  if (f.whole < 0)
    otherNumer = (f.whole * f.denominator) - f.numerator;
  else
    otherNumer = (f.whole * f.denominator) + f.numerator;
  otherDen = f.denominator;

  return ((firstnumer * otherDen) < (otherNumer * firstden));  
  //If the numerator / denominator is less than the second numerator/ second denominator
  //Return true 
  /*if ((firstnumer/firstden) < (otherNumer/otherDen))
    return true;
  else
    return false;
  */ 
}

bool Fraction::operator <= (const Fraction &f) const
{
  
  int firstnumer = 0;
  int firstden = 0;
  if (whole < 0)
    firstnumer = (whole * denominator) - numerator;
  else
    firstnumer = (whole * denominator) + numerator;
  firstden = denominator;

  int otherNumer = 0;
  int otherDen = 0;
  if (f.whole < 0)
    otherNumer = (f.whole * f.denominator) - f.numerator;
  else
    otherNumer = (f.whole * f.denominator) + f.numerator;
  otherDen = f.denominator;

  if ((firstnumer/firstden) <= (otherNumer/otherDen))
    return true;
  else
    return false;
   
}

bool Fraction::operator > (const Fraction &f) const
{
  
  int firstnumer = 0;
  int firstden = 0;
  if (whole < 0)
    firstnumer = (whole * denominator) - numerator;
  else
    firstnumer = (whole * denominator) + numerator;
  firstden = denominator;

  int otherNumer = 0;
  int otherDen = 0;
  if (f.whole < 0)
    otherNumer = (f.whole * f.denominator) - f.numerator;
  else
    otherNumer = (f.whole * f.denominator) + f.numerator;
  otherDen = f.denominator;

  if ((firstnumer/firstden) > (otherNumer/otherDen))
    return true;
  else
    return false;
   
}

bool Fraction::operator >= (const Fraction &f) const
{
  
  int firstnumer = 0;
  int firstden = 0;
  if (whole < 0)
    firstnumer = (whole * denominator) - numerator;
  else
    firstnumer = (whole * denominator) + numerator;
  firstden = denominator;

  int otherNumer = 0;
  int otherDen = 0;
  if (f.whole < 0)
    otherNumer = (f.whole * f.denominator) - f.numerator;
  else
    otherNumer = (f.whole * f.denominator) + f.numerator;
  otherDen = f.denominator;

  if ((firstnumer/firstden) >= (otherNumer/otherDen))
    return true;
  else
    return false;
   
}

Fraction Fraction::operator + (const Fraction &f) const
{
  
  Fraction(0,0,0); 
  Fraction sum ;

  if (whole < 0)
    sum.numerator = (whole * denominator) - numerator;
  else 
    sum.numerator = (whole * denominator) + numerator;

  sum.denominator = denominator;
  
  int otherNumer = 0;
  if (f.whole < 0)
    otherNumer = (f.whole * f.denominator) - f.numerator;
  else 
    otherNumer = (f.whole * f.denominator) + f.numerator;

  
  sum.numerator = (sum.numerator * f.denominator) + (sum.denominator * otherNumer);
  sum.denominator = sum.denominator * f.denominator;


  sum.reduce();

  return sum; 
}

Fraction Fraction::operator - (const Fraction &f) const
{
  Fraction minus = Fraction(0,0,1); 
  if (whole < 0)
      minus.numerator = (whole * denominator) - numerator;
  else 
    minus.numerator = (whole * denominator) + numerator;
 
  int otherNumer = 0;
  if (f.whole < 0)
    otherNumer = (f.whole * f.denominator) - f.numerator;
  else 
    otherNumer = (f.whole * f.denominator) + f.numerator;

  minus.numerator = (minus.numerator * f.denominator) - (minus.denominator * otherNumer);
  minus.denominator = minus.denominator * f.denominator;

  minus.reduce();

  return minus;
  
}

Fraction Fraction::operator * (const Fraction &f) const
{
  Fraction mult = Fraction(0,1,1); 
  if (whole < 0) 
    mult.numerator = (denominator * whole) - numerator;
  else 
    mult.numerator = (denominator * whole) + numerator;

  mult.denominator = denominator;
  
  int otherNumer = 0;
  if (f.whole < 0) 
    otherNumer = (f.denominator * f.whole) - f.numerator;
  else 
    otherNumer = (f.denominator * f.whole) + f.numerator;
  
  mult.numerator = otherNumer * mult.numerator;
  mult.denominator = f.denominator * mult.denominator;
  
  mult.reduce();
  return mult;
}

Fraction Fraction::operator / (const Fraction &f) const
{
  Fraction div = Fraction(0,0,1); 
  if (whole < 0) {
    div.numerator = (denominator * whole ) - numerator;
  }else {
    div.numerator = (denominator * whole) + numerator;
  }

  div.denominator = denominator;
  
  int otherNumer = 0;
  if(f.whole < 0 ) {
    otherNumer = (f.denominator * f.whole) - f.numerator;
  }else {
    otherNumer = (f.denominator * f.whole) + f.numerator;
  }

  div.numerator = div.numerator * f.denominator;
  div.denominator = div.denominator * otherNumer;

  div.reduce();
  return div;
  
}

Fraction Fraction::operator+=(const Fraction &f)
{
  if (whole < 0)
    {
      numerator = (whole * denominator) - numerator;
    }
  else {
  numerator = (whole * denominator) + numerator;
  }
  
  int otherNumer = 0;
  if (f.whole < 0){
    otherNumer = (f.whole * f.denominator) - f.numerator;
  }
  else {
  otherNumer = (f.whole * f.denominator) + f.numerator;
  }
  
  numerator = numerator * f.denominator + denominator * otherNumer;
  denominator = denominator * f.denominator;

  reduce();

  return *this;
}

Fraction Fraction::operator-=(const Fraction &f)
{

  if (whole < 0)
    {
      numerator = (whole * denominator) - numerator;
    }
  else {
    numerator = (whole * denominator) + numerator;
  }

  int otherNumer = 0;
  if (f.whole < 0){
    otherNumer = (f.whole * f.denominator) - f.numerator;
  }
  else {
    otherNumer = (f.whole * f.denominator) + f.numerator;
  }

  numerator = numerator * f.denominator - denominator * otherNumer;
  denominator = denominator * f.denominator;

  reduce();

  return *this;
  
}

Fraction Fraction::operator*=(const Fraction &f)
{
  if( whole == 0 && numerator == 0 && denominator == 1){
    numerator = 1;
    numerator = (denominator * whole) + numerator;
    int otherNumer = 0;
    otherNumer = (f.denominator * f.whole) + f.numerator;

    numerator = otherNumer * numerator;
    denominator = f.denominator * denominator;
    return *this;
  }
  else {
    if (whole < 0) {
      numerator = (denominator * whole) - numerator;
    }
    else {
    numerator = (denominator * whole) + numerator;
    }
    
    int otherNumer = 0;
    if (f.whole < 0) {
      otherNumer = (f.denominator * f.whole) - f.numerator;
    }
    else {
    otherNumer = (f.denominator * f.whole) + f.numerator;
    }
    
    numerator = otherNumer * numerator;
    denominator = f.denominator * denominator;

    reduce(); 
    return *this;
  }
  
}

Fraction Fraction::operator/=(const Fraction &f)
{
 
  if (whole < 0) {
    numerator = (denominator * whole ) - numerator;
  }else {
    numerator = (denominator * whole) + numerator;
  }
  int otherNumer = 0;
  if(f.whole < 0 ) {
    otherNumer = (f.denominator * f.whole) - f.numerator;
  }else {
    otherNumer = (f.denominator * f.whole) + f.numerator;
  }

  numerator = numerator * f.denominator;
  denominator = denominator * otherNumer;

  reduce();
  return *this; 
  
}

//Input operator
//Read in line by line (from main)
//Store the whole, numerator and denominator
//But store the fraction as improper (will get changed to mixed when reducing) 
istream & operator >> (istream &in, Fraction & f)
{
  int Whole;
  int Num;
  unsigned Den;
  char slash;
  
  in >> Whole >> Num >> slash >> Den;
  
  f.whole = Whole;
  if (Whole < 0)
    {
    f.numerator = Whole * int(Den) - Num;
  }
  else {
    f.numerator = Whole * int(Den) + Num;
  }
  
  f.denominator = Den;

  //Reduce the fraction now so we don't have to worry about it later! 
  f.reduce(); 

  return in; 
}


int Fraction::gcd(int numerator, int denominator) {
    if(denominator == 0)
      return numerator;
    else
      return gcd(denominator, abs(numerator) % denominator);
}


void Fraction::reduce() {

    int thenumer = (whole * (int)denominator) + numerator;

    if (denominator == 0) {
      whole = 0;
      numerator = 0;
      denominator = 1;
    }
    else 
      whole = int(numerator/int(denominator));

    //DECIMAL
    float thedecimal;
    
    thedecimal = whole + (numerator/(double)denominator);
    decimal = thedecimal;
      
    bool numisneg = false;
    if (numerator < 0 )
      {
	numisneg = true;
	numerator = abs(numerator);
	numerator = numerator % denominator;
      }

    if (numisneg == true) {
      numerator = numerator * -1;
    }

    if (numisneg == false) {
      numerator = numerator % denominator; 
    }
    

    if (whole < 0 && numerator <0 ) {
      numerator = abs(numerator);
    } 
   
    if (numerator != 0 || denominator != 0){
      int divis = gcd(numerator, denominator);
      numerator = numerator/divis;
      denominator = denominator/divis; 
    }

    if(numerator < 0 && denominator < 0) {
      numerator *= -1;
      denominator *= -1;
    }
   
}

//OUTPUT OPERATOR
//The output operator outputs the fraction in mixed form 
ostream & operator <<(ostream &output, const Fraction &f) {
 
  int wholeprint = (int)f.whole;
  int numerp = f.numerator; 
  
  bool numisneg = false;
  if (f.numerator < 0 && wholeprint != 0)
    {
      numisneg = true;
      int numerp = abs(f.numerator); 
      numerp = numerp % f.denominator;
    }

  if (numisneg == true) {
    numerp = -1 * numerp;
  }
  
  if (numisneg == false){
    int numerp = f.numerator % f.denominator;
  }
  
  if (wholeprint < 0 && numerp < 0) {
    numerp = abs(numerp);
  }

  //Output the fraction in mixed form 
  output << wholeprint << " " << numerp << "/" << f.denominator;

  return output;
  

}
 
