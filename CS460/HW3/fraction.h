/************************
Author: Mackenzie Larson
WATTS 460 HW3 

 ***********************/ 

#ifndef FRACTION_H
#define FRACTION_H
#include <iostream>
#include <vector> 

using namespace std;

class Fraction
{
 public:
  Fraction ();
  Fraction (int, unsigned);
  Fraction (int, unsigned, unsigned);
  Fraction (float);
  bool Valid () const;
  int Whole () const;
  int Numerator () const;
  unsigned Denominator () const;
  bool operator == (const Fraction &) const;
  bool operator != (const Fraction &) const;
  bool operator < (const Fraction &) const;
  bool operator <= (const Fraction &) const;
  bool operator > (const Fraction &) const;
  bool operator >= (const Fraction &) const;
  Fraction operator + (const Fraction &) const;
  Fraction operator - (const Fraction &) const;
  Fraction operator * (const Fraction &) const;
  Fraction operator / (const Fraction &) const;
  Fraction operator += (const Fraction &f);
  Fraction operator -= (const Fraction &);
  Fraction operator *= (const Fraction &);
  Fraction operator /= (const Fraction &);
  friend ostream & operator << (ostream &, const Fraction &f);
  friend istream & operator >> (istream &, Fraction &f);

 private:
  int numerator, denominator, whole;
  float decimal;
  
  bool fractionNegative;

  
  vector<string> vectorofints; 

  vector<float> vectorofdeci; 
  
  int gcd(int numerator, int denominator);

  void reduce(); 
   
};
#endif
