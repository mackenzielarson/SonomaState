__author__ = 'Mackenzie Larson'

from graphics import *

win = GraphWin("Graphics Elements", 600, 600, autoflush=False)

row1_balls = []
row2_balls = []
row3_balls = []

radius = 20
diameter = radius * 2
h_gap_between_balls = 5    # the horizontal distance between the edges of two adjacent balls.
v_distance_between_ball_centers = 100
row1_x = 100
row1_y = 500

number_of_balls_across = 10     # Your solution should work for any value, not just 10.

x = row1_x   # The center of the left-most ball on the bottom level is (x, row1_y)

# for i in range(number_of_balls_across):
for i in range(number_of_balls_across):
#     create a point to represent the center of the next ball (x, row1_y)
    center_of_next_ball = Point(x, row1_y)
#     create a circle to represent this ball and add fill-color to it.
    c_row1 = Circle(center_of_next_ball, radius)
    c_row1.setFill('blue')
#     add the ball to list, row1_balls.
    row1_balls.append(c_row1)
#     draw this ball.
    c_row1.draw(win)
#     add to x so that it represents the x of the next ball.
    x = x + h_gap_between_balls + diameter
# win.update()   # update the screen.

win.update()

# calculate x and y of the left-most ball for the middle row balls.
row2_x = row1_x
row2_y = row1_y - v_distance_between_ball_centers - diameter
# create the middle row balls, add them to row2_balls, and draw them.
for i in range(number_of_balls_across):
    center_of_next_ball = Point(row2_x, row2_y)
    c_row2 = Circle(center_of_next_ball, radius)
    c_row2.setFill('yellow')
    row2_balls.append(c_row2)
    c_row2.draw(win)
    row2_x = row2_x + diameter + h_gap_between_balls


win.update()

# calculate x and y of the left-most ball for the top row balls.
# create the top row balls, add them to row3_balls, and draw them.
row3_x = row1_x
row3_y = row2_y - v_distance_between_ball_centers - diameter
for i in range(number_of_balls_across):
    center_of_next_ball = Point(row3_x, row3_y)
    c_row3 = Circle(center_of_next_ball, radius)
    c_row3.setFill('orange')
    row3_balls.append(c_row3)
    c_row3.draw(win)
    row3_x = row3_x + diameter + h_gap_between_balls


win.update()
win.getMouse()

num_y_pixels_per_move = 2
for i in range(v_distance_between_ball_centers // num_y_pixels_per_move):
    for i in range(len(row1_balls)):
        row1_balls[i].move(0, -num_y_pixels_per_move)
    win.update()

for i in range(v_distance_between_ball_centers // num_y_pixels_per_move):
    for i in range(len(row2_balls)):
        row2_balls[i].move(0, -num_y_pixels_per_move)
    win.update()

for i in range(v_distance_between_ball_centers // num_y_pixels_per_move):
    for i in range(len(row3_balls)):
        row3_balls[i].move(0, -num_y_pixels_per_move)
    win.update()

win.getMouse()
win.update()
#    move all the balls (a for-loop) on the bottom-most level, one at a time,
#         up by num_y_pixels_per_move pixels.
#    win.update() # update after all balls at this level have been moved up
#         by num_y_pixels_per_move pixels.

# Similar to the ball on the lower-level, animate the balls on the middle level

# Similar to the ball on the middle-level, animate the balls on the top level

