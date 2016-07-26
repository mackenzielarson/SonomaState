__author__ = 'Mackenzie Larson'

"""
   Description: This program creates a two dimensional array, call
      it m, populates it with random values in the range [-10,
      10]. It then creates another matrix, call it cm, of the same
      size where cm[i][j] contains the count of the number of
      elements that are adjacent to m[i][j] and are positive integers.

   Author: Mackenzie Larson
"""

from random import randint, seed

def create_2d_matrix(rows, columns):
    """
    Creates and returns a two dimensional array with "rows" rows
    and "columns" columns. The elements will contain zeros.
    """
    two_d = []
    for i in range(rows):
        two_d.append([])
        for j in range(columns):
            two_d[i].append(0)
    return two_d


def populate_with_random_values(matrix):
    """
    Populates each element of "matrix" with a random value in the
    closed range [-10, 10].

    """
    seed(23)
    rows = len(matrix)
    for row in range(rows):
        for col in range(len(matrix[row])):
            matrix[row][col] = randint(-10, 10)


def neighbor_count(i, j, grid):
    """
    Counts and returns the number of non-zero, positive integers that are
    adjacent to grid[row][column].

    """
    total = 0
    # top mid
    if i - 1 >= 0 and grid[i-1][j] > 0:
        total +=1

    # bottom mid
    if i + 1 < (len(grid)) and grid[i + 1][j] > 0:
        total +=1

    # left side
    if j - 1 >= 0 and grid[i][j-1] > 0:
        total +=1

    # right side
    if j + 1 < (len(grid[i])) and grid[i][j+1] > 0:
        total +=1

    # top left corner
    if i-1 >= 0 and j-1 >= 0 and grid[i-1][j-1] > 0:
        total +=1

    # top right corner
    if i-1 >=0 and j+1 < (len(grid[i])) and grid[i-1][j+1] >0:
        total +=1

    # bottom left corner
    if i+1 < (len(grid)) and j-1 >=0 and grid[i+1][j-1] >0:
        total +=1

    # bottom right corner
    if i+1 < (len(grid)) and j+1 < (len(grid[i])) and grid[i+1][j+1] >0:
        total +=1

    return total


def create_2d_count_matrix(matrix, count_matrix):
    """
    Creates and returns a new two dimensional array whose number of
    rows and columns are equal to that of "matrix". Each element of
    this new array contain the count of the number of positive
    integers that are adjacent to its corresponding element in "matrix".

    """


    for i in range(len(matrix)):
        for j in range(len(matrix[i])):
            count_matrix[i][j] = neighbor_count(i, j, matrix)
    return count_matrix


def rjust_by_n(number, n):
    """
    Returns a string of length "n" with number right-justified in it.

    number: an integer value with "n" or fewer digits
    n: a positive integer value

    return value: a string of length "n" with number right-justified in it.
    """
    #Unessicary function because we placed the r just elsewhere
    return str(number).rjust(n)
    pass

def print_2d_matrix(matrix):
    """
    Prints a two dimensional array, one row per line.

    """
    for i in range(len(matrix)):
        for j in range(len(matrix[i])):
            print(str(matrix[i][j]).rjust(4), '', end='')
        print()


def main():
    matrix = create_2d_matrix(4, 6)
    populate_with_random_values(matrix)
    print("The original matrix.\n")
    print_2d_matrix(matrix)

    print()
    count_matrix = create_2d_matrix(4, 6)
    count_matrix = create_2d_count_matrix(matrix, count_matrix)
    print("The 'count' matrix.\n")
    print_2d_matrix(count_matrix)


main()
