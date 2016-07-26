"""
Program: CS 115 Lab 3
Author: Mackenzie Larson
Description: This program will ask the user for a value of N
    and then compute the N_th term in a sequence.
"""
import math  # This will be important later


def main():
    # Get the term number N
    term_number_N = int(input("Enter a number: "))
    print ("You entered: ", term_number_N)

    # Calculate the denominator
    denominator = 2 * term_number_N - 1

    print ("Denominator: ", denominator)

    # Calculate 4 divided by the denominator
    entire_term = 4 / (denominator)

    print (entire_term)

    # Calculate sign
    sign = ((-1) ** term_number_N) * (-1)

    # Multiply value of term N by sign value
    print ("Term", term_number_N , "is:" , entire_term * sign)
    
main()
