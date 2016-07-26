__author__ = 'student'

from random import randint, seed

SPACES_PER_DIGIT = 4

def sum_adjacent_elements(list_of_numbers, idx):
    """
    Add the values of the elements adjacent to list_of_numbers[idx]

    list_of_numbers: a list of integers
    idx: a value in the range 0 and len(list_of_numbers)-1
    return value: the sum of the elements adjacent to list_of_numbers[idx]
    """
    idx = []
    for i in range (len(list_of_numbers)):
        if i == 0:
            idx.append(list_of_numbers[1])
        if i >= 1 and i < (len(list_of_numbers) - 1):
            adjacent_sum = list_of_numbers[i - 1] + list_of_numbers[i + 1]
            idx.append(adjacent_sum)
        if i == (len(list_of_numbers)-1):
            last_adjacent_sum = list_of_numbers[i-1]
            idx.append(last_adjacent_sum)

    return idx

def rjust_by_n(number, n):
    """
    Returns a string of length "n" with number right-justified in it.

    number: an integer value with "n" or fewer digits
    n: a positive integer value

    return value: a string of length "n" with number right-justified in it.
    """
    return str(number).rjust(n)


def create_list(size):
    """
    Creates a list with "size" elements and stores random values in it.
    However, for the sake of being able to test this program, we
    initialize the random-number generator to dispense the same
    sequence of numbers every time the function is called.

    size: the size of the list to create
    return value: a list with "size" elements and randomly generated values
    """
    seed(19)
    max_rand = 100
    list_of_numbers = []
    for i in range(size):
        list_of_numbers.append(randint(0, max_rand))
    return list_of_numbers

def print_list(numbers):
    for i in range(len(numbers)):
        print( rjust_by_n(numbers[i], 4), end='')
    print()

def main():
    num_elements = 10  # let's create a list with 10 elements
    numbers = create_list(num_elements)
    print('The original list.')
    print()
    print_list(numbers)

    print()
    print('The sum of adjacent values list.')
    print()

    adj_sum = sum_adjacent_elements(numbers, 0)
    for i in range(num_elements):
        # the sum of the elements that are adjacent to "i".

        # print it in SPACES_PER_DIGIT spaces.
        print( rjust_by_n(adj_sum[i], SPACES_PER_DIGIT), end='' )

    print()

main()