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
        #all_words.append(words)
        for word in words:
            all_words.append(word)
    # for each "line" in "lines" do:
    #    break up "line" into an array called, "words"
    #    append the words in "words", one at a time, to "all_words"

    return all_words


def print_text_lines(lines):
    print(lines)


def count_characters(lines):
    total = 0
    for line in lines:
        for character in line:
            total +=1
    return total

def to_lower(list_of_strings):
    # "list_of_strings" is an array of strings. This
    # function creates a new array each of whose elements
    # is identical to that of "list_of_strings" except for
    # the case of the letters are all lower-case. The
    # function returns this new array.
    lower_case_string = []
    for line in list_of_strings:
        line = line.lower()
        lower_case_string.append(line)
    return (lower_case_string)

def count_frequency(word, words):
    # This function counts and returns the number of times
    # that the string "word" occurs in the array of strings, "words"
    total = 0
    for i in range (len(words)):
        if word == words[i]:
            total += 1
    return total

def is_member(word, words):
    # The function returns true if the string in "word" is
    # in the list of strings, "words". Otherwise, the function
    # should return false.
   for i in range (len(words)):
       if word == words[i]:
           return True
   return False

def create_frequency_list(words):
    # "words" is a list of strings. This function creates two new lists:
    # "unique_words" and "frequency". "unique_words" has only one copy of
    # each of the words in "words" and "frequency[i]" contains the number of
    # times that "unique_words[i]" has occurred in "words". This function
    # returns both lists.
    frequency_list = []
    unique_list = []

    for i in range (len(words)):
        if is_member(words[i], unique_list) == False:
            unique_list.append(words[i])

    for j in range (len(unique_list)):
        frequency_list.append(count_frequency(unique_list[j], words))

    return frequency_list, unique_list

def main():
    file_handle = open('krugman.txt', 'r')  # will crash if 'krugman.txt' doesn't exist.

    lines = read_input_lines(file_handle)   # "lines" is an array of input-lines.
    lines = to_lower(lines)

    number_of_lines = len(lines)
    #print_text_lines(lines)                 # print each line as a way to see what we have.
    words = convert_lines_to_words(lines)   # "words" contains all the words in "lines";
                                            # all the words in the input-file.
    number_of_words = len(words)
    number_of_character = count_characters(lines)

    words_freq, words_uniqued = create_frequency_list(words)

    for i in range( len(words_uniqued) ):
        print( str(words_freq[i]).rjust(4), words_uniqued[i] )

    #print('krugman.txt', number_of_lines, number_of_words, number_of_character)
main()