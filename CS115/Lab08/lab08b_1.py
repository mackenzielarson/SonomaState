__author__ = 'Mackenzie Larson'
"""

Program: CS 115 Lab 08 (lab08b_1.py)
Author: Mackenzie Larson
Description: This program uses the graphics package to animate the domino effect involving three balls.

"""
from graphics import *
radius = 20
diameter = 2 * radius
v_distance_between_ball_centers = 100
bottom_ball_initial_y = 500
x_ball_center = 250
win = GraphWin('Animation', 600, 500, autoflush=False)

#  c1_center = create a point to represent the center of the bottom-most circle (ball),
#              using x_ball_center and bottom_ball_initial_y
#  write your code for c1_center below this line...
c1_center = Point(x_ball_center, bottom_ball_initial_y)

#  c1 = create the bottom-most circle using c1_center and radius.
c1 = Circle(c1_center, radius)
c1.setFill('blue')
c1.draw(win)

#  c2_center = create a point to represent the center of the middle circle.
#              Calculate its y using bottom_ball_initial_y, v_distance_between_ball_centers,
#              and diameter.
c2_y = bottom_ball_initial_y - v_distance_between_ball_centers - diameter
c2_center = Point(x_ball_center, c2_y)

#  c2 = create the middle circle using c2_center and radius.
#
c2 = Circle(c2_center, radius)
c2.setFill('yellow')
c2.draw(win)

#  c3_center = create a point to represent the center of the middle circle.
#              Calculate its y using the y of the middle circle, v_distance_between_ball_centers
#              and diameter.
c3_y = c2_y - v_distance_between_ball_centers - diameter
c3_center = Point(x_ball_center, c3_y)
#  c3 = create the top-most circle using c3_center and radius.
c3 = Circle(c3_center, radius)
c3.setFill('red')
c3.draw(win)


num_y_pixels_per_move = 2
total_pixels_to_move = v_distance_between_ball_centers
# Now, set up a loop to animate the bottom-most ball and test your program before continuing.
#      during each iteration of the loop, move the bottom-most ball up
#      by num_y_pixels_per_move number of pixels and update the window.
for i in range(total_pixels_to_move // num_y_pixels_per_move):
    c1.move(0, -num_y_pixels_per_move)
    win.update()

# Once you have tested the previous part, set up a loop to animate the middle ball and test it.
#      during each iteration of the loop, move the middle ball up by num_y_pixels_per_move
#      number of pixels.
for i in range(total_pixels_to_move // num_y_pixels_per_move):
    c2.move(0, -num_y_pixels_per_move)
    win.update()

# Now, set up a loop to animate the top ball and test your program.
#      during each iteration of the loop, move the top ball up by num_y_pixels_per_move
#      number of pixels.
for i in range(total_pixels_to_move // num_y_pixels_per_move):
    c3.move(0, -num_y_pixels_per_move)
    win.update()

win.getMouse()
