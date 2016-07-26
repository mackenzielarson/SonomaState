"""
Program: CS 115 Lab 3c
Author: Mackenzie Larson
Description: This program will add up a list of numbers provided by the user.
"""
import math


def main():
    sum = 0

    for i in range(1, 6):
        i = float(input("Enter an integer: "))
        sum = sum + i

    print('The total is:', sum)


main()
