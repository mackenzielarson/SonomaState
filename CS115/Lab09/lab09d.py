__author__ = 'Mackenzie'
__author__ = 'Mackenzie'
"""
    Author: Mackenzie Larson

    Description: The program reads a sequence of integers and fixes inversion, until the numbers
    are sorted from smallest to largest, based on user's input.

    This lab is used as the basis for lab09a.py
"""

RED = '\033[91m'
END = '\033[0m'

from graphics import *
from time import sleep

G_WINDOW_WIDTH = 1400
G_WINDOW_HEIGHT = 800
BASE_LINE_Y = G_WINDOW_HEIGHT - 50
GAP_BETWEEN_RECTANGLES = 4
HEIGHT_MULTIPLIER = 2
RECTANGLE_WIDTH = 20

seq1_points = [17, 177, 72, 273, 37, 341, 152, 282, 180, 250, 31, 10, 39, 33, 204, 154,
                11, 55, 178, 202, 144, 247, 220, 148, 22, 137, 306, 271, 111, 236,
                85, 169, 147, 214, 196, 20, 50, 30, 240, 275, 139, 215, 319, 15,
                21, 107, 90, 69, 280, 140, 19]


seq1_points = [17, 177, 72, 273, 37, 341, 152, 282, 180, 250, 31, 10, 39, 33, 204, 154,
                11, 55, 178, 202, 144, 247, 220, 148, 22, 137]


def create_and_draw_rectangles(numbers, win):
    rectangles = []
    bar = Rectangle(Point(4, BASE_LINE_Y - numbers[0] * HEIGHT_MULTIPLIER) , Point(24, BASE_LINE_Y))
    bar.setFill('yellow')
    bar.draw(win)
    rectangles.append(bar)

    for i in range(1, len(numbers)):
        bar = Rectangle(Point(4 ,BASE_LINE_Y - numbers[i] * HEIGHT_MULTIPLIER), Point(24,BASE_LINE_Y))
        bar.move(i * (GAP_BETWEEN_RECTANGLES + RECTANGLE_WIDTH), 0)
        rectangles.append(bar)
        bar.setFill('yellow')
        bar.draw(win)

    return rectangles

def find_selected_rectangle(c_point,rectangles):

    click_point_x = c_point.getX()
    click_point_y = c_point.getY()
    for i in range(len(rectangles)):
        x1 = rectangles[i].getP1().getX()
        y1 = rectangles[i].getP1().getY()
        x2 = rectangles[i].getP2().getX()
        y2 = rectangles[i].getP2().getY()
        if click_point_x > x1 and click_point_x < x2:
            if click_point_y > y1 and click_point_y < y2:
                rectangles[i].setFill('dark blue')
                sleep(.095)
                return i
    return None

def identify_rect_inversions(rectangles, numbers, win):

    for i in range (len(rectangles)):
        if i == 0:
            rectangles[i].setFill('yellow')
        if i > 0:
            if numbers[i] < numbers [i - 1]:
                rectangles[i].setFill('red')
                win.update()
            else:
                rectangles[i].setFill('yellow')
                win.update()
    return


    """
    Color the rectangles in rectangles that represent an inversion in numbers in red.

    rectangles: a list of rectangles.
    numbers: a list of numbers. When defined, rectangles[i] represents numbers[i].

    return value: None
    """

def get_num_values():
    global seq1_points
    return len(seq1_points)


def get_value():
    global seq1_points
    for point in seq1_points:
        yield point
    yield None


def next_value():
    return next(next_value.points)


next_value.points = get_value()


def echo(numbers, in_red):
    """
    Prints a list of numbers and their indices on one line.

    :param numbers: a list of integers to print
    :param in_red: inversion in "numbers" will be printed in red if "in_red" is True
    :return: None
    """

    input_size = len(numbers)
    if input_size == 0:
        return # Nothing to print

    # print the indices
    print(end="|")
    for i in range(input_size):
        print(str(i).rjust(4), sep="", end="|")
    print()

    # print the values in the list
    print("|", str(numbers[0]).rjust(4), sep="", end="|")
    for i in range(1, input_size):
        if in_red:
            if numbers[i] < numbers[i - 1]:
                print(RED + str(numbers[i]).rjust(4) + END, sep="", end="|")
            else:
                print(str(numbers[i]).rjust(4), sep="", end="|")
        else:
            print(str(numbers[i]).rjust(4), sep="", end="|")

    print()


def count_inversions(numbers):
    """
    Counts and returns the number of inversion in "numbers"

    :param numbers: a list of read-only numbers
    :return: the number of inversions
    """

    input_size = len(numbers)
    inversions = 0
    for i in range(1, input_size):
        if numbers[i] < numbers[i - 1]:
            inversions += 1
    return inversions


def get_input():
    """
    Using "next_point()", reads input values, stores them in a list, and returns the list.

    :return: a list of zero or more values; the values are expected to be integers
    """
    p = next_value()
    numbers = []
    while p is not None:
        numbers.append(p)
        p = next_value()
    return numbers


def fix_left_inversion(pos, numbers, rectangles, win):
    """
    Fixes an inversion whose index is in "pos" in the left direction.

    :param pos: the index of the inversion to fix
    :param numbers: a list of numbers possibly with numbers[pos-1] > numbers[pos]
    """

    while pos > 0 and numbers[pos] < numbers[pos - 1]:
        rectangles[pos].move(-24, 0)
        rectangles[pos-1].move(24,0)

        numbers[pos-1], numbers[pos] = numbers[pos], numbers[pos-1]
        rectangles[pos-1], rectangles[pos] = rectangles[pos], rectangles[pos -1]


        win.update()
        pos -= 1


def fix_right_inversion(pos, numbers, rectangles, win):
    """
    Fixes an inversion whose index is in "pos" in the right direction.

    :param pos: the index of the inversion to fix
    :param numbers: a list of numbers possibly with numbers[pos] > numbers[pos+1]
    """

    num_list_elements = len(numbers)
    print(num_list_elements)
    print(len(rectangles))
    while pos < num_list_elements - 1 and numbers[pos] > numbers[pos + 1]:
        #print(pos)
        rectangles[pos].move(RECTANGLE_WIDTH + GAP_BETWEEN_RECTANGLES, 0)
        rectangles[pos+1].move(-RECTANGLE_WIDTH + GAP_BETWEEN_RECTANGLES,0)

        numbers[pos+1], numbers[pos] = numbers[pos], numbers[pos+1]
        rectangles[pos+1], rectangles[pos] = rectangles[pos], rectangles[pos +1]


        win.update()
        pos += 1


def fix_inversion(pos, numbers, rectangle, win):
    """
    Fixes a left or a right inversion.

    :param pos: the index of the inversion to fix
    :param numbers: a list of integers with possibly an inversion at "pos"
    :param direction: "left" or "right"
    """
    if pos > 0 and numbers[pos] < numbers[pos - 1]:
        fix_left_inversion(pos, numbers, rectangle, win)

    elif pos < len(numbers) - 1 and numbers[pos] > numbers[pos + 1]:
        fix_right_inversion(pos, numbers, rectangle, win)

def find_an_inversion(numbers):
    for i in range(1, len(numbers)):
        if numbers[i] < numbers[i-1]:
            return i

def main():
    """
    Reads a list of integers and then repeatedly fixes inversion based on user's input.

    """

    numbers = get_input()
    win = GraphWin("Lab09b", G_WINDOW_WIDTH, G_WINDOW_HEIGHT)
    rectangles = create_and_draw_rectangles(numbers,win)
    identify_rect_inversions(rectangles, numbers, win)

    for i in range (len(numbers)+1):
        center_of_text = Point(i * 24-9, BASE_LINE_Y + 10)
        text_to_display = Text(center_of_text, str(i-1))
        text_to_display.setSize(8)
        text_to_display.setTextColor("black")
        text_to_display.draw(win)

    win.getMouse()


    #echo(numbers, True)
    inversions = count_inversions(numbers)
    print("\nThere are", inversions, "inversions.\n")

    while inversions > 0:

        pos = find_an_inversion(numbers)
        fix_inversion(pos, numbers, rectangles, win)
        identify_rect_inversions(rectangles, numbers, win)
        inversions = count_inversions(numbers)

        win.update()
    win.getMouse()

    echo(numbers, True)

main()


