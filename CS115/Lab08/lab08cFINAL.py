__author__ = 'Mackenzie'
"""

Program: CS 115 Lab 08 (lab08c.py)
Author: Mackenzie Larson
Description: This program uses the graphics package to animate two circles to rotate around each other.
                ******* NOTE: My program uses a time.sleep import because I was working off of my personal computer and
                the circles moved too quickly for whatever reason--- the program may be slow when checked!****

"""


from graphics import *


win = GraphWin('Animation', 600, 500, autoflush=False)
radius = 20
diameter = 2 * radius
gap_between_balls = 6
height = 100           # height of the imaginary rectangle.
initial_y = 450
x_left_ball = 300
x_right_ball = x_left_ball + gap_between_balls + diameter


# ball1 = create the right circle using (x_right_ball, initial_y) and radius
ball1_center = Point(x_right_ball, initial_y)
ball1 = Circle(ball1_center, radius)
ball1.setFill('orange')
ball1.draw(win)

# ball2 = create the left circle
ball2_center = Point(x_left_ball, initial_y)
ball2 = Circle(ball2_center, radius)
ball2.setFill('red')
ball2.draw(win)

win.getMouse()

dx_pixels = 1    # number of pixels to move a ball left or right in every loop iteration
dy_pixels = 2    # number of pixels to move a ball up or down in every loop iteration

n = 2  # number of times that the right ball moves around the imaginary rectangle.
       # Your program should work for any value of n. So, change it to 3, 4, 5, 6
       # as you test your solution.

# ball 1 move up
for i in range(height):
    ball1.move(0,-dy_pixels)
    from time import sleep
    time.sleep(.0095)
    win.update()


for j in range (n * 2):
    # ball moves sideways
    for i in range(gap_between_balls + diameter):
        ball1.move(-dx_pixels,0)
        ball2.move(dx_pixels, 0)
        time.sleep(.0095)
        win.update()
    if j == n * 2 - 1:
        for i in range (height):
            ball2.move(0, -dy_pixels)
            time.sleep(.0095)
            win.update()
        break
    # ball move up/down
    for i in range (height):
        ball1.move(0, dy_pixels)
        ball2.move(0, -dy_pixels)
        time.sleep(.0095)
        win.update()

    dx_pixels = -dx_pixels
    dy_pixels = -dy_pixels




win.getMouse()
win.update()