"""
Program: CS 115 Lab 4d
Author: Mackenzie Larson
Description: This program will calculate your BMI.
"""
import sys


def main():
    # Ask user for height in inches
    height = float(input("What is your height in inches? "))

    # Error if height is equal to or less than zero
    if height <= 0:
        print("Error: height should be a positive number.")
        # exit the program
        sys.exit()
        
    # Ask user for weight in pounds
    weight = float(input("What is your weight in pounds? "))

    # Error if weight is equal to or less than zero 
    if weight <= 0:
        print("Error: weight should be a positive number.")
        # exit the program
        sys.exit()

    # Calculate user's height in inches
    height_in_meters = height * 0.0254
    print("Your height in meters is ", height_in_meters, ".", sep="")

    # Calculate the user's mass in kilograms
    mass_in_kilograms = weight / 2.20462
    print("Your mass in kilograms is ", mass_in_kilograms, ".", sep="")

    # Calculate the user's BMI
    bmi = mass_in_kilograms / (height_in_meters ** 2)

    # If BMI is underweight
    if bmi < 18.5:
        print("Your BMI is ", bmi, " (underweight).", sep="")

    # If BMI is normal weight
    elif 18.5 <= bmi < 25.0:
        print("Your BMI is ", bmi, " (normal weight).", sep="")

    # If BMI is overweight
    elif 25.0 <= bmi < 30.0:
        print("Your BMI is ", bmi, " (overweight).", sep="") 

    # If BMI is obese
    else:
       print("Your BMI is ", bmi, " (obese).", sep="")        
        

main()
