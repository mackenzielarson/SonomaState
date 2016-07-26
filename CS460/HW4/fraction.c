/******************************
Author: Mackenzie Larson 
Date: 4/29/16
This program will read in a list of fractions, sort them and add them 
******************************/ 
#include <stdio.h>
#include <stdlib.h>
#include <float.h>
#include <stdbool.h>
#include "fraction.h"

void f_print(struct Fraction f){

  int n_whole = f.num/f.den;
  int n_num = f.num % f.den;
  f.whole += n_whole;
  f.num = n_num;

  bool breakout = false; 
  if (f.num < 0 && f.whole == 0){
    f.num = f.num * -1;
    printf("0 -%d/%d\n", f.num, f.den);
    breakout = true;
  }
  else if (f.num < 0 && f.whole < 0){
    f.num = f.num * -1;
    printf("%d %d/%d\n", f.whole, f.num, f.den);
  }
  else
    printf("%d %d/%d\n", f.whole, f.num, f.den);
   
}

//Algorithm for GCD used in reducing
int f_gcd(int x, int y) {
  while (x && y) {
    if (x >= y) {
      x %= y;
    }
    else {
      y %= x;
    }
    if (y == 1 || x == 1) {
      return 1;
    }
  }
  return x + y;
}

//Reduce the fraction based on the GCD
struct Fraction f_reduce (struct Fraction f){
  int d;
  if (f.num <= -1){
    d = f_gcd((-1 * f.num), f.den);
  }else {
    d = f_gcd(f.num, f.den);
  }
  f.num /= d;
  f.den /= d;
  return f;
}

bool f_compare (struct Fraction f1, struct Fraction f2){
  //Comparison----- check whole numbers first
  if (f1.whole < f2.whole)
    return false;
  else if (f1.whole > f2.whole)
    return true;
  //if the whole numbers are the same convert the numer/denom to decimal and compare
  else
    {
      float dec1, dec2;
      dec1 = (float)f1.num / (float)f1.den;
      dec2 = (float)f2.num / (float)f2.den;
      if (dec1 > dec2)
	return true;
      else
	return false;
    }
}

void f_sort(struct Fraction all[], int size){
  int i = 0;
  int j = 0;
  int temp = 0;
  for (i; i < size - 1; i++){
    for (j = i + 1; j < size; j++){
      if(f_compare(all[j], all[i]) == false){
	struct Fraction temp = all[j];
	all[j] = all[i];
	all[i] = temp;
      }
    }
  }
}

//Will calculate the sum of the fractions in the list
struct Fraction f_sum(struct Fraction all[], int count){
  struct Fraction sum;
  sum.num = 0;
  sum.den = 1;
  int i;
  for(i = 0; i < count; i++){
    //if the denominators are equal, add the numerators (den won't change)
    if (all[i].den == sum.den){
      sum.num = sum.num + all[i].num;
    }
    //if the denominators are not equal, must calculate new denominator
    else {
      sum.num = (int) ((all[i].whole * all[i].den + all[i].num) * sum.den) + sum.num * all[i].den;
      sum.den = (int) all[i].den * sum.den;
    }
    //if numerator is 0, the denominator must be a 1
    if (sum.num == 0)
      sum.den = 1;
  }
  //reduce the final sum 
  sum = f_reduce(sum);
  return sum;
}
