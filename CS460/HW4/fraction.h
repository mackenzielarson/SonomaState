/********************************
Author: Mackenzie Larson 
DATE: 4/29/16 
**********************************/ 
#ifndef FRACTION_H
#define FRACTION_H

#include <stdbool.h>

struct Fraction{
  int whole;
  int num;
  int den;
};

int f_gcd(int x, int y); 
bool f_compare(struct Fraction f1, struct Fraction f2);
void f_sort(struct Fraction all[], int size);
struct Fraction f_reduce(struct Fraction f); 
struct Fraction f_sum(struct Fraction List[], int count);
void f_print(struct Fraction f); 

#endif
