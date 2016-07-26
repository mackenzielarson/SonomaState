"""

Program: CS 115 Lab 05 part F 
Author: Mackenzie Larson 
Description: This program uses two functions to provide access to a
sequence of points.
"""
seq1_points =[[9132013, 464], [9122013,   472], [9112013,   467], [9102013,   494], [9092013,   506], [9062013,   498],
[9052013,   495], [9042013,   498], [9032013,   488], [8302013,   487], [8292013,   491], [8282013,   490],
[8272013,   488], [8262013,   502], [8232013,   501], [8212013,   502], [8202013,   501], [8192013,   507],
[8162013,   502], [8152013,   497], [8142013,   498], [8132013,   489], [8122013,   467], [8092013,   454],
[8082013,   461], [8072013,   464], [8062013,   465], [8052013,   469], [8022013,   462], [8012013,   456],
[7312013,   452], [7302013,   453], [7292013,   447], [7262013,   440], [7252013,   438], [7242013,   440],
[7232013,   418], [7222013,   426], [7192013,   424], [7182013,   431], [7162013,   430], [7152013,   427],
[7122013,   426], [7112013,   427], [7102013,   420], [7092013,   422], [7082013,   415], [7052013,   417],
[7032013,   420], [7022013,   418], [7012013,   409], [6282013,   396], [6272013,   393], [6262013,   398],
[6242013,   402], [6212013,   413], [6202013,   416], [6192013,   423], [6182013,   431], [6172013,   432],
[6142013,   430], [6132013,   435]]


def get_num_points():
    global seq1_points
    return len( seq1_points )

def get_point(seq_number):
    global seq1_points
    if seq_number < 0 or seq_number >= len(seq1_points):
        return None, None
    return seq1_points[seq_number][0], seq1_points[seq_number][1]

def main():

    # Get the number of points                                                                                                                    
    num_points = get_num_points()

    # Read the first point, call it prev_x, prev_y
    prev_x, prev_y = get_point(0)

    # Read the second point, call it cur_x, cur_y
    cur_x, cur_y = get_point(1)

    peak_min = None
    peak_max = None
    valley_min = None
    valley_max = None
    
    # Establish if the two points are increasing or decreasing

    if prev_y > cur_y:
        increasing = False
        if peak_min is None or prev_y < peak_min:
            peak_min = prev_y
        if peak_max is None or prev_y > peak_max:
            peak_max = prev_y
    else:
        increasing = True
        if valley_min is None or prev_y < valley_min:
            valley_min = prev_y
        if valley_max is None or valley_y > valley_max:
            valley_max = prev_y
            
    prev_x, prev_y = get_point(1) 

    for i in range(2, num_points):
        # Read the next point and call it cur_x and cur_y
        cur_x, cur_y = get_point(i)
    
        # If the sequence has been increasing:
        if increasing == True:
            if prev_y > cur_y:
                increasing = False
                if peak_min is None or prev_y < peak_min:
                    peak_min = prev_y
                if peak_max is None or prev_y > peak_max:
                    peak_max = prev_y
        else:
            if prev_y < cur_y:
                increasing = True
                if valley_min is None or prev_y < valley_min:
                    valley_min = prev_y
                if valley_max is None or prev_y > valley_max:
                    valley_max = prev_y
                

        prev_x, prev_y = get_point(i)


    prev_x = cur_x
    prev_y = cur_y
    cur_x, cur_y = get_point(i)
    if prev_y > cur_y:
        if valley_min is None or prev_y < valley_min:
            valley_min = prev_y
        if valley_max is None or valley_y > valley_max:
            valley_max = prev_y
        
    else:
        if peak_min is None or prev_y < peak_min:
                    peak_min = prev_y
        if peak_max is None or prev_y > peak_max:
                    peak_max = prev_y

    print("Min peak value is", peak_min)
    print("Max peak value is", peak_max)
    print("Min valley value is", valley_min)
    print("Max valley value is", valley_max)
                    
        
    

main()

