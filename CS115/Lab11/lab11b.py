__author__ = 'Mackenzie Larson'

def read_input_lines(file_handle):
    all_lines = []
    input_line = file_handle.readline()
    all_lines.append(input_line)
    while input_line != "":
        input_line = file_handle.readline()
        if input_line != '':
            all_lines.append(input_line)
    return all_lines

def convert_lines_to_words(lines):
    # "lines" is an arrays of strings each of which consists
    # of zero or more words.

    all_words = []
    for line in lines:
        words = line.split()
        for word in words:
            all_words.append(words)
    # for each "line" in "lines" do:
    #    break up "line" into an array called, "words"
    #    append the words in "words", one at a time, to "all_words"

    return all_words


def print_text_lines(lines):
    print(lines)
    pass

def count_characters(lines):
    total = 0
    for line in lines:
        for character in line:
            total +=1
    return total

def main():
    file_handle = open('krugman.txt', 'r')  # will crash if 'krugman.txt' doesn't exist.
    lines = read_input_lines(file_handle)   # "lines" is an array of input-lines.
    number_of_lines = len(lines)
    #print_text_lines(lines)                 # print each line as a way to see what we have.
    words = convert_lines_to_words(lines)   # "words" contains all the words in "lines";
                                            # all the words in the input-file.
    number_of_words = len(words)
    number_of_character = count_characters(lines)
    print('krugman.txt', number_of_lines, number_of_words, number_of_character)
main()