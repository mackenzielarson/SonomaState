"""
Program: CS 115 Lab 6e
Author: Mackenzie Larson 
Description: This program will read a positive integer and decompose it into the sum
   of power of twos.
"""


def main():

    i_num = int(input("Enter a number to decompose into the sum of powers of 2: "))
    
   
    if i_num <= 0:
        print("")
        
    while i_num > 0:
        n = 0 
        two_to_n = 1
        while two_to_n < i_num:
            n += 1
            two_to_n = two_to_n * 2

        if two_to_n > i_num: # we must have gone too far
            two_to_n = two_to_n / 2
            n -= 1

        i_num = i_num - two_to_n
        
        if i_num > 0:
            print("2^", n, " +", sep="", end=" ")
        else: 
            print("2^", n, sep="")

        
main()
