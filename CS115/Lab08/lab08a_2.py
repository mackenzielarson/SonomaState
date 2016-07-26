__author__ = 'Mackenzie Larson'
"""
Program: CS 115 Lab 08 (lab08a_2.py)
Author: Mackenzie Larson
Description: This program uses the graphics package to create a number of circles.
"""

from graphics import *

win = GraphWin("Animating a Ball", 300, 500, autoflush=False)

circle_center_x = 150
circle_center_y = 400
radius = 30


circle_center = Point(circle_center_x, circle_center_y)
circle = Circle(circle_center, radius)
circle.setFill('yellow')
circle.draw(win)

# Draw a line from the center of the circle before animation to the center
# of the circle after animation.

total_pixels_to_move = 300
circle_y_before_animation = circle_center_y
circle_y_after_animation = circle_center_y - total_pixels_to_move
guide_x = circle_center_x
p1 = Point(guide_x, circle_y_before_animation)
p2 = Point(guide_x, circle_y_after_animation)
guide_line = Line(p1, p2)
guide_line.draw(win)
win.update()

# Give the user a chance to see the objects before the animation
win.getMouse()

# Move the circle up, num_y_pixels_per_move per loop iteration, until
# it moves total_pixels_to_move pixels.
num_y_pixels_per_move = 2
for i in range(total_pixels_to_move // num_y_pixels_per_move):
    circle.move(0, -num_y_pixels_per_move)
    win.update()

# Give the user a chance to see the objects after the animation

win.getMouse()
win.close()
