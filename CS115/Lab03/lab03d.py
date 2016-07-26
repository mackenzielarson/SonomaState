"""
Program: CS 115 Lab 3
Author: Mackenzie Larson
Description: This program will ask the user for a value of N
    and then compute the approximate value of pi using a series.
"""
import math  # This will be important later


def main():
    # Get the term number N
    print ("This program will approximate the value of pi using a series.")
    term_number_N = int(input("How many terms should I compute? "))
    sum = 0
    for i in range(1, term_number_N+1):
        # Calculate the denominator
        denominator = 2 * i - 1

        # Calculate 4 divided by the denominator
        entire_term = 4 / (denominator)

        # Calculate sign
        sign = ((-1) ** i) * (-1)

        # Calculate sum
        sum = sum + (entire_term * sign)

    # Calculate difference calculated from pi
    print ("The difference between pi and my approximation is ",
            math.pi-sum, "." , sep="")
    
main()
