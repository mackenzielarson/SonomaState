__author__ = 'Mackenzie'
"""

Program: CS 115 Lab 08 (lab08d.py) Extra Credit
Author: Mackenzie Larson
Description: This program uses the graphics package to animate a group of circles to rotate around each other.

"""
from graphics import *

row1_balls = []
row2_balls = []

# Variables
win = GraphWin('Animation', 600, 500, autoflush=False)
radius = 20
diameter = 2 * radius
gap_between_balls = 6
height = 100           # height of the imaginary rectangle.
initial_y = 450
x_left_ball = 70
x_right_ball = x_left_ball + gap_between_balls + diameter

#Row 1
for i in range(5):
    row1_center = Point(x_right_ball, initial_y)
    row1_circle = Circle(row1_center, radius)
    row1_circle.setFill('orange')
    row1_balls.append(row1_circle)
    row1_circle.draw(win)
    x_right_ball = x_right_ball + 2 * diameter + gap_between_balls + 2.5
    win.update()

#Row 2
for i in range(5):
    row2_center = Point(x_left_ball, initial_y)
    row2_circle = Circle(row2_center, radius)
    row2_circle.setFill('yellow')
    row2_balls.append(row2_circle)
    row2_circle.draw(win)
    x_left_ball = x_left_ball + 2 * diameter + gap_between_balls + 3
    win.update()

win.getMouse()

dx_pixels = 1
dy_pixels = 2

n = 2
# Move row 1 up initially
for i in range(height):
    for i in range(len(row1_balls)):
        row1_balls[i].move(0, -dy_pixels)
        update()

# Movement felt/right for both sets of balls
for j in range(n * 2):
    for i in range(gap_between_balls + diameter):
        for i in range(len(row1_balls)):
            row2_balls[i].move(dx_pixels, 0)
            row1_balls[i].move(-dx_pixels, 0)
            win.update()

    # Movement to bring down last row of balls on last turn
    if j == n * 2 - 1:
        for i in range(height):
            for i in range(len(row1_balls)):
                row2_balls[i].move(0, -dy_pixels)
                win.update()
        break
    # Up and down movement for both sets
    for i in range(height):
        for i in range(len(row1_balls)):
            row2_balls[i].move(0, -dy_pixels)
            row1_balls[i].move(0, dy_pixels)
            win.update()


    dx_pixels = -dx_pixels
    dy_pixels = -dy_pixels


win.getMouse()
win.close()
