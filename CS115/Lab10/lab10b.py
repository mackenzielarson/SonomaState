__author__ = 'student'
import sys



def create_matrix(square_size):
    two_d = []
    for i in range(square_size):
        two_d.append([])
        for j in range(square_size):
            two_d[i].append(0)
    return two_d




def build_magic_square(square):
    """
    Create a magic square in "square"

    square: a two dimensional array whose number of rows and columns are equal
            and len(square) is an odd number.
    return value: None
    """
    magic_value = 1
    square_size = len(square)
    row = 0
    col = square_size // 2
    square_size_squared = square_size * square_size
    i = 0
    while magic_value <= square_size_squared:
        square[row][col] = magic_value

        row -= 1
        col += 1
        if row < 0 and col > square_size - 1:
            row += 2
            col -= 1
        elif row < 0:
            row = square_size - 1
        elif col > square_size - 1:
            col = 0
        elif square[row][col] != 0:
            row += 2
            col -= 1


        magic_value += 1


def print_magic_square(matrix):
    for i in range(len(matrix)):
        for j in range(len(matrix)):
            print(str(matrix[i][j]).rjust(4), '', end='')
        print()

def sum_row_values(matrix, row_number):
    """
    Sums the values of all entries in the row given by "row_number"

    matrix: a two dimensional (square) array
    row_number: an integer value in the range 0 and len(matrix)-1
    return value: the sum of all value of the row indicated by "row_number"
    """
    total = 0
    for j in range( len(matrix[row_number]) ):
        total += matrix[row_number][j]
    return total

def sum_n_row_values(matrix):
    for n in range (len(matrix)):
        total = 0
        for j in range(len(matrix[n]) ):
            total += matrix[n][j]
        #print('The sum of values in row', n, 'is', total)

def sum_col_values(matrix, col_number):
    """
    Sums the values of all entries in the column given by "col_number"

    matrix: a two dimensional (square) array
    col_number: an integer value in the range 0 and len(matrix)-1
    return value: the sum of all values of the column indicated by "row_number"
    """

    for n in range (len(matrix)):
        total = 0
        for j in range(len(matrix[col_number]) ):
            total += matrix[j][col_number]
        #print('The sum of values on column', n, 'is', total)

def sum_top_left_bottom_right_diagonal(matrix):
    """
    Calculates the sum of the values at matrix[0][0], matrix[1][1], etc.

    matrix: a two dimensional (square) matrix
    return value: the sum of values of the top-left to bottom-right
                  diagonal
    """
    sum = 0
    for i in range(len(matrix)):
        sum += matrix[i][i]
    #print('The sum of the diagonal from left to right is', sum)

def sum_top_right_bottom_left_diagonal(matrix):
    """
    Calculates the sum of the values at matrix[0][len(matrix)-1], matrix[1][len(matrix)-2], etc.

    matrix: a two dimensional (square) matrix
    return value: the sum of values of the top-right to bottom-left
                  diagonal
    """
    sum = 0
    for i in range (len(matrix)):
        sum += matrix[i][len(matrix)-1-i]
    #print('The sum of the diagonal from right to left is', sum)

def is_magic_square(matrix):
    """
    returns True if the two dimensional array that "matrix" points to is a
    magic square. Otherwise, it returns False.

    matrix: a two dimensional (square) array.

    return value: True or False.
    """
    tlbr_sum = sum_top_left_bottom_right_diagonal(matrix)
    # calculate the sum of the values of the top-left to
    # bottom-right diagonal. Call it tlbr_sum.

    trbl_sum = sum_top_right_bottom_left_diagonal(matrix)
    # calculate the sum of the values of the top-right to
    # bottom-left diagonal. Call it trbl_sum.

    if tlbr_sum != trbl_sum:
        return False
    # if tlbr_sum is not equal to trbl_sum, return False. Otherwise,
    # proceed.

    sum_of_each_row = sum_n_row_values(matrix)
    if tlbr_sum != sum_n_row_values(matrix):
        return False
    # calculate the sum of each row of the matrix and compare it
    # with tlbr_sum. If the two sums are not equal, return False.
    # Otherwise, proceed.

    sum_of_each_col = sum_col_values(matrix, 0)
    if tlbr_sum != sum_of_each_col:
        return False

    # calculate the sum of each column of the matrix and compare it
    # with tlbr_sum. If the two sums are not equal, return False.
    # Otherwise, proceed.
    return True
    # return True.


def main():
    square_size = int(input("Enter an odd integer to build a magic square: "))
    if square_size % 2 == 0:
        print(square_size, " is not an odd integer. Terminating...")
        sys.exit()

    matrix = create_matrix(square_size)
    build_magic_square(matrix)
    print_magic_square(matrix)
    print()

    is_magic_square(matrix)
    if is_magic_square(matrix) == True:
        print('The above square is a magic square.')


main()