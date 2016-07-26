/**********************************
Author: Mackenzie Larson 
Date:4/28/16 
This program will take a list of fractions, generate a sum for all the fractions, and sort the list & put it out
to the command line 
**********************************/ 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "SetLimits.h"
#include "fraction.h"
#include "vector.h"

//Read param
int f_read(struct Fraction f, FILE *input); 

struct Fraction f_initialize(struct Fraction f){
  f.whole = 0;
  f.num = 0;
  f.den = 0;
  return f;
}

int main(int argc, char* argv[]){

  struct Fraction F;
  F = f_initialize(F);
  
  FILE * in = fopen (argv[1], "r");
  if (in == NULL){
    printf ("ERROR! Unable to open file. \n");
    return 1;
  }
  f_read(F, in); 

  SetLimits(); 
}

int f_read(struct Fraction F, FILE *in){
  struct Fraction* List = malloc(sizeof(struct Fraction) * 1000000);
  vector v;
  vector_init(&v);
  
  int count = 0;
  long whole, num, den;
  char temp;
  //Scan each line 
  while(fscanf(in, "%ld %ld %c %ld", &whole, &num, &temp, &den) != EOF){
    F.whole = whole;
    if (F.whole < 0)
      F.num = num * -1;
    else
      F.num = num;
    F.den = den;
    List[count] = F;

    vector_add(&v, &F);
    count++;
  }
  fclose(in);

  int i;
  
  // This will first reduce all the fractions, then turn them improper
  for (i = 0; i < count; i++){
    List[i] = f_reduce(List[i]);
  }

  // Find the sum of the fractions
  struct Fraction sum = f_sum(List, count);
  printf("The sum of the fractions is: ");
  f_print(sum);

  //Sort the list of the fractions 
  printf("\n");
  f_sort(List, count);
  for (i = 0; i < count;i++){
    f_sort(List,count);
  }
  //Print the final list of fractions
  for (i = 0; i < count; i++){
    f_print(List[i]);
  }
  
}
