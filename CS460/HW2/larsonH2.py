"""
Author: Mackenzie Larson 
Date: 2/16/16
Program: WATTS460 HW 2- Python implementation of fraction sort
         Will take a list of fractions in format [wholenum num/den], sort them in 
         ascending order and will reduce them. The output must match the input format. 
TO RUN: python larsonHW2.py "yourtestcasename".txt
Note: 
* FIRST SUBMISSION: Didn't work.. Error with my sort case
* SECOND SUBMISSION: WORKED with test cases 1 - 4
* THIRD SUBMISSION: Second didn't work with *new* test case 5--- must speed it up
* FOURTH SUBMISSION: Everything works. Addidng some comments and resubmitting!
"""
from sys import argv
from fractions import Fraction

def read_in_file(script, filename):
    txt = open(filename)
    #print "Your filename is: %r " %filename
    #print "The contents of your file are: "
    #print txt.read()
    
    with open(filename, "r") as ins:
        global fract
        fract = []
        for line in ins:
            fract.append(line)
    return fract

# Convert the proper fraction to improper to use python's Fraction to sort the numbers
def prop_to_improp(fract):
    global impropfract
    impropfract = []
    for line in fract:
        num, den = line.split('/')
        whole, num = num.split()
        #Dealing with negative whole numbers (num must become negative)
        if int(whole) < 0:
            newnum = (int(den) * int(whole)) - int(num)
        else:    
            newnum = (int(den) * int(whole)) + int(num) 
        #print "NewNum:"
        #print newnum

        #Will reduce fraction automatically when "fractionizing" num and den. Thanks python! 
        numerator = int(newnum)
        denominator = int(den)
        result = Fraction(numerator, denominator)
        
        #print result
        impropfract.append(result)
    return impropfract

#Taking my sorted inproper fractions and turning back into proper / correct format
def improp_to_prop(reduced):
    global final
    final = []
    for i in reduced:
         num = i.numerator
         den = i.denominator
         # All the rules associated with whole number & numerator (neg or pos or 0) 
         if num < 0:
             wholenum = (-1 * int(num)) / int(den)
             wholenum = int(wholenum) * -1
             if wholenum == 0:
                 numerator = (-1 * int(num)) % int(den)
                 final = str(wholenum) + " " + "-" + str(numerator) + "/" + str(den)
             else: 
                 numerator = (-1 * int(num)) % int(den)
                 final = str(wholenum) + " " + str(numerator) + "/" + str(den)             
         else:
             wholenum = int(num)/ int(den)
             numerator = int(num) % int(den)
             final = str(wholenum) + " " + str(numerator) + "/" + str(den)
         #Print the final output!     
         print final 
    return final 

def main():
    #Call read in file 
    script, filename = argv
    read_in_file(script, filename)

    #print "Not sorted list improper fractions: "
    prop_to_improp(fract)
    #print impropfract
    
    #print "Sorted list of improter fractions: "
    sortedimprop = []
    sortedimprop = sorted (impropfract, key=Fraction)

    #reduced -> proper fraction 
    #print "The final sorted list: "
    improp_to_prop(sortedimprop)

main()          
