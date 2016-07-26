RED = '\033[91m'
END = '\033[0m'

seq1_values = [5, 40, 180, 13, 30, 20, 25, 24, 29,  31,  54, 46,  42, 50,  67, 17,
               76, 33, 84, 35, 100, 37, 110, 32, 112, 15, 123, 3, 130, 42]

def get_num_values():
    global seq1_values
    return len( seq1_values )

def get_values():
    global seq1_values
    for value in seq1_values:
        yield value
    yield None

def next_value():
    return next( next_value.values )
next_value.values = get_values()

## It is safe to ignore the above code.

def main():
    #********************** THE OUTPUT OF THIS PROGRAM IS NOT THE SAME AS DR. KOOSHESH'S OUTPUT. THE OUTPUT OF THIS PROGRAM GETS TO THE SOLUTION OF 0 INVERSIONS IN FEWER STEPS BY COMBINING STEPS.**********
    # Variables
    value = next_value()
    numbers = []
    input_size = 0
    num_inversions = 0

    while value is not None:
        numbers.append(value)
        input_size = input_size + 1
        value = next_value()

    print()

    inversions_list = []
    num_inversions = 1

    while num_inversions > 0:

        num_inversions = 0
        prev = numbers[0]

        for i in range (len(numbers)):
            if i == 0:
                print("|",end="")
            print(str(i).rjust(4), "|", end = "", sep ="")

        print()

        for i in range (len(numbers)):
            if i == 0:
                print("|",end="")

            cur = numbers[i]
            if cur < prev:
                print(RED + str(cur).rjust(4) + END, "|", end="", sep="")
                num_inversions +=1
                # append the inversions
                inversions_list.append(i)
            else:
                print(str(cur).rjust(4), "|", end="", sep="")

            prev = cur

        print()

        if num_inversions > 0:
            print("There are ", num_inversions, "inversions.")

        if num_inversions == 0:
            print("There are ", num_inversions, "inversions.")

            break

        for i in range (len(inversions_list)):

            idx = inversions_list[i]
            # I included both left and right while loops because it decreases the numbers of inversions quicker and in fewer steps than just the left.
            while (idx - 1) >= 0 and numbers[idx] < numbers[idx-1]:
                numbers[idx], numbers[idx - 1] = numbers[idx - 1], numbers[idx]
                idx -= 1

            while (idx +1) <= len(numbers)-1 and numbers[idx] > numbers[idx + 1]:
                numbers[idx], numbers[idx + 1] = numbers[idx + 1], numbers[idx]
                idx += 1

        print()




main()