__author__ = 'Mackenzie Larson'
"""

Program: CS 115 Lab 08 (lab08a_1.py)
Author: Mackenzie Larson
Description: This program uses the graphics package to create a number of circles.

"""
from graphics import *

num_circles = 5
win = GraphWin("Circles", 400, 600)
radius = 30
colors = ['red', 'blue', 'green', 'yellow', 'orange']

for i in range(num_circles):
    click_point = win.getMouse()           # Get the point on the window where the mouse was clicked
    circle = Circle(click_point, radius)   # Create a circle centered at the point of the click
    circle.setFill(colors[i])              # Each circle gets a different color from list, colors
    circle.draw(win)

# wait for the user to click the mouse one more time before we close the window.
win.getMouse()
win.close()