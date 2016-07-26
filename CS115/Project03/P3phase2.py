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
    p1_x = []
    p2_x = []
    p1_y = []
    p2_y = []

    for i in range (rows):
        p1 = Point(x, y)
        p2 = Point( x + (columns+1) * WIDTH_OF_IMAGES, y)
        p1_y.append(y)
        #line = Line(p1, p2)
        #line.draw(win)

        y += HEIGHT_OF_IMAGES
        p2_y.append(y)


    y = Y_OFFSET

    for i in range (columns):
        p1 = Point(x, y)
        p2 = Point( x, y + (rows+1) * WIDTH_OF_IMAGES)
        p1_x.append(x)
        #line = Line(p1, p2)
        #line.draw(win)

        x += HEIGHT_OF_IMAGES
        p2_x.append(x)


    draw_grid = []
    for row in range(rows):
        draw_grid.append([])
        for col in range(columns):
            draw_grid[row].append(col)
    for row in range(rows):
        for col in range (len(draw_grid[row])):
            draw_grid[row][col] = Rectangle(Point(p1_x[col], p1_y[row]), Point(p2_x[col], p2_y[row]))
    for i in range (len(draw_grid)):
        for j in range (len(draw_grid[i])):
            draw_grid[i][j].draw(win)


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

    return draw_grid

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
    tiles = []
    x = X_OFFSET
    y = Y_OFFSET
    for i in range (len(game_board_markers)):
        row_tiles = []
        for j in range (len(game_board_markers[i])):
            tile_image = Image(Point(x + WIDTH_OF_IMAGES // 2, y + HEIGHT_OF_IMAGES // 2), TILE_IMAGE)
            tile_image.draw(win)

            row_tiles.append(tile_image)
            x += WIDTH_OF_IMAGES

        tiles.append(row_tiles)

        y += HEIGHT_OF_IMAGES
        x = X_OFFSET

    return tiles

def convert_click_to_row_column(click_point, draw_grid):
    p1 = draw_grid.getP1()
    p2 = draw_grid.getP2()
    if click_point.getX() >= p1.getX() and click_point.getX() <= p2.getX():
        if click_point.getY() >= p1.getY() and click_point.getY()<= p2.getY():
            return True
    else:
        return False

def tile_to_remove(click_point, draw_grid):
    for i in range(len(draw_grid)):
        for j in range (len(draw_grid[i])):
            uncover = convert_click_to_row_column(click_point, draw_grid[i][j])
            if uncover:
                return i, j
    return None, None

def expose_empty_cells (game_board_markers, tiles, i, j, win):

    game_board_markers[i][j] = EXPOSED_CELL


    if i - 1 >= 0 and tiles[i-1][j] != None and game_board_markers[i-1][j] != 13:
        tiles[i-1][j].undraw()
        tiles[i-1][j] = None
        if game_board_markers[i-1][j] == 0:
            expose_empty_cells(game_board_markers, tiles, i-1, j, win)
        game_board_markers[i-1][j] = EXPOSED_CELL


    if i + 1 < (len(game_board_markers)) and tiles[i+1][j] != None and game_board_markers[i + 1][j] != 13:
        tiles[i+1][j].undraw()
        tiles[i+1][j] = None
        if game_board_markers[i+1][j] == 0:
            expose_empty_cells(game_board_markers, tiles, i+1, j, win)
        game_board_markers[i+1][j] = EXPOSED_CELL



    if j - 1 >= 0 and tiles[i][j-1] != None and game_board_markers[i][j-1] != 13:
        tiles[i][j-1]. undraw()
        tiles[i][j-1] = None
        if game_board_markers[i][j-1] == 0:
            expose_empty_cells(game_board_markers, tiles, i, j-1, win)
        game_board_markers [i][j-1] = EXPOSED_CELL



    if j + 1 < (len(game_board_markers[i])) and tiles[i][j+1] != None and game_board_markers[i][j+1] != 13:
        tiles[i][j+1]. undraw()
        tiles[i][j+1] = None
        if game_board_markers[i][j+1] == 0:
            expose_empty_cells(game_board_markers, tiles, i, j+1, win)
        game_board_markers [i][j+1] = EXPOSED_CELL



    if i-1 >= 0 and j-1 >= 0 and tiles[i-1][j-1] != None and game_board_markers[i-1][j-1] != 13:
        tiles[i-1][j-1].undraw()
        tiles[i-1][j-1] = None
        if game_board_markers[i-1][j-1] == 0:
            expose_empty_cells(game_board_markers, tiles, i-1, j-1, win)
        game_board_markers[i-1][j-1] = EXPOSED_CELL


    if i-1 >=0 and j+1 < (len(game_board_markers[i])) and tiles[i-1][j+1] != None and game_board_markers[i-1][j+1] != 13:
        tiles[i-1][j+1]. undraw()
        tiles[i-1][j+1] = None
        if game_board_markers[i-1][j+1] == 0:
            expose_empty_cells(game_board_markers, tiles, i-1, j+1, win)
        game_board_markers [i-1][j+1] = EXPOSED_CELL



    if i+1 < (len(game_board_markers)) and j-1 >=0 and tiles[i+1][j-1] != None and game_board_markers[i+1][j-1] != 13:
        tiles[i+1][j-1]. undraw()
        tiles[i+1][j-1] = None
        if game_board_markers[i+1][j-1] == 0:
            expose_empty_cells(game_board_markers, tiles, i+1, j-1, win)
        game_board_markers [i+1][j-1] = EXPOSED_CELL


    if i+1 < (len(game_board_markers)) and j+1 < (len(game_board_markers[i])) and tiles[i+1][j+1] != None and game_board_markers[i+1][j+1] != 13:
        tiles[i+1][j+1]. undraw()
        tiles[i+1][j+1] = None
        if game_board_markers[i+1][j+1] == 0:
            expose_empty_cells(game_board_markers, tiles, i+1, j+1, win)
        game_board_markers [i+1][j+1] = EXPOSED_CELL



def expose_all_mines(game_board_marker, tiles, win):
    for i in range (len(game_board_marker)):
        for j in range (len(game_board_marker[i])):
            if game_board_marker[i][j] == MINE_CELL:
                tiles[i][j].undraw()

def delete_tiles(tiles, cells, game_board_marker, rows, win):
    while 2 > 1:
        click_point = win.getMouse()
        row, column = tile_to_remove(click_point, cells)

        if row is None:
            continue

        elif game_board_marker[row][column] == EXPOSED_CELL:
            continue

        elif game_board_marker[row][column] >= 1 and game_board_marker[row][column] <= 8:
            tiles[row][column].undraw()
            game_board_marker[row][column] = EXPOSED_CELL
            tiles[row][column] = None

        elif game_board_marker[row][column] == MINE_CELL:
            expose_all_mines(game_board_marker, tiles, win)
            #happy.undraw()
            #draw_lose(rows, win)

        elif game_board_marker[row][column] == 0:
            expose_empty_cells(game_board_marker, tiles, row, column, win)



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
    tiles = add_tiles(game_board_marker, win)

    delete_tiles(tiles, draw_grid, game_board_marker, rows, win)


    win.getMouse()


main()
