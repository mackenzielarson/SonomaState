__author__ = 'Mackenzie Larson'

from graphics import *

import random

TILE_IMAGE = 'tile.gif'
FLAG_IMAGE = 'flag.gif'
MINE_IMAGE = 'mine.gif'
LOSE_IMAGE = 'lose.gif'
SMILEY_IMAGE = 'smiley.gif'
BLANK_CELL = 0
EXPOSED_CELL = 10
MINE_CELL = 13
MAX_ADJACENT_MINES = 8
WIDTH_OF_IMAGES = 32
HEIGHT_OF_IMAGES = 32
LEFT_OFFSET = 100
RIGHT_OFFSET = 100
TOP_OFFSET = 120
BOTTOM_OFFSET = LEFT_OFFSET // 2
X_OFFSET = LEFT_OFFSET
Y_OFFSET = TOP_OFFSET



def create_minesweeper_matrix(rows, columns):
    minesweeper_matrix = []
    for i in range(rows):
        minesweeper_matrix.append([])
        for j in range(columns):
            minesweeper_matrix[i].append(0)
    return minesweeper_matrix

def print_game_board(game_board_marker):
    for i in range(len(game_board_marker)):
        for j in range(len(game_board_marker[i])):
            print(str(game_board_marker[i][j]).rjust(4), '', end='')
        print()

def populate_with_mines(game_board_markers, number_of_mines):
    random.seed(23)
    """All cells of the game_board_markers that is passed to the following function contain zeros.
    This function randomly selects number_of_mines cells of this two dimensional array and
    designates them as mine-cells. On return, number_of_mines cells of game_board_markers
    will contain MINE_CELL."""

    sizex = len(game_board_markers) - 1
    sizey = len(game_board_markers[0]) - 1

    while number_of_mines > 0:
        # put a mine somewhere

        randx = random.randint(0, sizex)
        randy = random.randint(0, sizey)

        if game_board_markers[randx][randy] != MINE_CELL:
            game_board_markers[randx][randy] = MINE_CELL
            number_of_mines -= 1



def update_neighbor_count(game_board_markers, i, j):
    total = 0
    if game_board_markers[i][j] != 13:
        # top mid
        if i - 1 >= 0 and game_board_markers[i-1][j] == 13:
            total +=1

        # bottom mid
        if i + 1 < (len(game_board_markers)) and game_board_markers[i + 1][j] == 13:
            total +=1

        # left side
        if j - 1 >= 0 and game_board_markers[i][j-1] == 13:
            total +=1

        # right side
        if j + 1 < (len(game_board_markers[i])) and game_board_markers[i][j+1] == 13:
            total +=1

        # top left corner
        if i-1 >= 0 and j-1 >= 0 and game_board_markers[i-1][j-1] == 13:
            total +=1

        # top right corner
        if i-1 >=0 and j+1 < (len(game_board_markers[i])) and game_board_markers[i-1][j+1] == 13:
            total +=1

        # bottom left corner
        if i+1 < (len(game_board_markers)) and j-1 >=0 and game_board_markers[i+1][j-1] == 13:
            total +=1

        # bottom right corner
        if i+1 < (len(game_board_markers)) and j+1 < (len(game_board_markers[i])) and game_board_markers[i+1][j+1] == 13:
            total +=1
    else:
        return 13
    return total



def draw_the_grid(rows, columns, win):
    x = X_OFFSET
    y = Y_OFFSET

    for i in range (rows + 1):
        p1 = Point(x, y)
        p2 = Point( x + (columns) * WIDTH_OF_IMAGES, y)

        line = Line(p1, p2)
        line.draw(win)
        y += HEIGHT_OF_IMAGES

    x = X_OFFSET
    y = Y_OFFSET
    for i in range (columns + 1):
        p1 = Point(x, y)
        p2 = Point( x, y + (rows) * WIDTH_OF_IMAGES)

        line = Line(p1, p2)
        line.draw(win)
        x += HEIGHT_OF_IMAGES

    for i in range(rows):
        center_of_text = Point(X_OFFSET // 1.2, y + 18)
        text_to_display = Text(center_of_text, i)
        text_to_display.setSize(10)
        text_to_display.draw(win)
        y += HEIGHT_OF_IMAGES
    win.update()
    x = X_OFFSET
    for j in range(columns):
        center_of_text = Point(x + 15 , Y_OFFSET// 1.2 )
        text_to_display = Text(center_of_text, j)
        text_to_display.setSize(10)
        text_to_display.draw(win)
        x += HEIGHT_OF_IMAGES
    win.update()

def create_2d_count_matrix(game_board):

    for i in range(len(game_board)):
        for j in range(len(game_board[i])):
            game_board[i][j] = update_neighbor_count(game_board, i, j)


    return game_board

def draw_board_numbers(game_board_markers, game_board_images, win):
    x = X_OFFSET
    y = Y_OFFSET
    for i in range(len(game_board_markers)):
        for j in range(len(game_board_markers[i])):
            center_of_text = Point(x + WIDTH_OF_IMAGES // 2, y + HEIGHT_OF_IMAGES // 2)
            text_to_display = Text(center_of_text, game_board_markers[i][j])

            if game_board_markers [i][j] != 0:
                text_to_display.setSize(10)
                text_to_display.draw(win)

            x += WIDTH_OF_IMAGES

        y += HEIGHT_OF_IMAGES
        x = X_OFFSET

def add_mine_count(game_board_markers, win):
    x = X_OFFSET
    y = Y_OFFSET
    for i in range (len(game_board_markers)):
        for j in range (len(game_board_markers[i])):
            if game_board_markers[i][j] == 13:
                mine_image = Image(Point(x + WIDTH_OF_IMAGES // 2, y + HEIGHT_OF_IMAGES // 2), MINE_IMAGE)
                mine_image.draw(win)
            x += WIDTH_OF_IMAGES

        y += HEIGHT_OF_IMAGES
        x = X_OFFSET

def add_tiles(game_board_markers, win):
    x = X_OFFSET
    y = Y_OFFSET
    for i in range (len(game_board_markers)):
        for j in range (len(game_board_markers[i])):
            tile_image = Image(Point(x + WIDTH_OF_IMAGES // 2, y + HEIGHT_OF_IMAGES // 2), TILE_IMAGE)
            tile_image.draw(win)
            x += WIDTH_OF_IMAGES

        y += HEIGHT_OF_IMAGES
        x = X_OFFSET

def main():
    level_selection = input("Enter a level of difficulty: ")
    if level_selection == 'beginner':
        # Beginner game
        rows = 9
        columns = 9
        num_mines = 10
        win = GraphWin('Minesweeper', 500, 500)
    elif level_selection == 'intermediate':
        # Intermediate
        rows = 16
        columns = rows
        num_mines = 40
        win = GraphWin('Minesweeper', 700, 700)
    elif level_selection == 'expert':
        # Expert
        rows = 16
        columns = 30
        num_mines = 99
        win = GraphWin('Minesweeper', 1200, 700)
    else:
        print("You failed to pick a correct size!")


    game_board_marker = create_minesweeper_matrix(rows, columns)
    populate_with_mines(game_board_marker, num_mines)
    create_2d_count_matrix(game_board_marker)
    draw_board_numbers(game_board_marker, None, win)
    draw_grid = draw_the_grid(rows, columns, win)
    print_game_board(game_board_marker)
    add_mine_count(game_board_marker, win)
    #add_tiles(game_board_marker, win)

    win.getMouse()


main()