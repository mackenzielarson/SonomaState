from graphics import *
import random
import sys

# Pre-existing variables that must be assigned before functions (size of win/ spaces between circles/ palette colors ... ect)
g_window_width = 360
g_window_height = 700
leftmost_x = 50
palette_y = g_window_height - 50
circle_radius = 20
circle_diameter = 2 * circle_radius
h_circle_spacing = 5
v_circle_spacing = 10
exit_x = 10 + circle_radius
exit_y = 30
state_x = g_window_width - circle_radius
state_y = exit_y
circle_width = 1
secret_code_x = exit_x
secret_code_y = exit_y
guess_y = palette_y - 100
guess_x = leftmost_x + circle_radius + h_circle_spacing
feedback_circle_radius = 5
feedback_x = leftmost_x + 5 * circle_radius * 2 + 4 * h_circle_spacing + feedback_circle_radius
feedback_y = guess_y + circle_radius - feedback_circle_radius
feedback_h_spacing = 20
feedback_v_spacing = 20
secret_code_x = guess_x
secret_code_y = 150
palette_colors = ['green', 'orange', 'darkblue', 'yellow', 'darkred', 'lightblue']
num_palette_colors = len(palette_colors)
final_x = 180
final_y = state_y
dy = circle_diameter + h_circle_spacing



# Create Window
win = GraphWin('Project 1 Phase 2', g_window_width, g_window_height)

# Exit circle (red circle) in top left of window so when clicked the system exits
def create_exit_circle(win):
    exit_circle_center = Point(exit_x, exit_y)
    exit_circle = Circle(exit_circle_center, circle_radius)
    exit_circle.setFill('red')
    exit_circle.draw(win)
    return exit_circle

# State circle (empty circle top right of window). Will fill with color when a color is selected to show user what color they chose
def create_state_circle(win):
    state_circle_center = Point(state_x, state_y)
    state_circle = Circle(state_circle_center, circle_radius)
    state_circle.draw(win)
    return state_circle

# Palette circles are a row of circles at the bottom of window with set colors. They are where the user selects a color.
def create_palette_circle(palette_colors):
    leftmost_x = 50
    palette_circles = []
    for i in range (len(palette_colors)):
        palette_circles_center = Point(leftmost_x, palette_y)
        palette_circle = Circle(palette_circles_center, circle_radius)
        palette_circles.append(palette_circle)
        palette_circle.setFill(palette_colors[i])
        palette_circle.draw(win)
        leftmost_x = leftmost_x + circle_diameter + h_circle_spacing
    return palette_circles

#Empty circles
def create_skel_circle():
    guess_x = leftmost_x + circle_radius + h_circle_spacing
    skel_circles = []
    for i in range(4):
        skel_circles_center = Point(guess_x, guess_y)
        skel_circle = Circle(skel_circles_center, circle_radius)
        skel_circle.draw(win)
        skel_circles.append(skel_circle)
        guess_x = guess_x + circle_diameter + h_circle_spacing
    return skel_circles

# Random colors change every time game is played and is the goal of the player to match them
def create_secret_code_colors(palette_colors):
    secret_code_colors = []
    for i in range(4):
        idx = int(round(random.random() * (num_palette_colors - 1)))
        secret_code_colors.append(palette_colors[idx])
    return secret_code_colors

# Circles where the random colors are assigned to fill so the user can see what colors to match
def create_secret_code_circles(secret_code_colors):
    secret_code_circles = []
    secret_code_x = guess_x
    for i in range(4):
        secret_code_circles_center = Point(secret_code_x, secret_code_y)
        secret_code_circle = Circle(secret_code_circles_center, circle_radius)
        secret_code_circle.setFill(secret_code_colors[i])
        secret_code_circles.append(secret_code_circle)
        secret_code_circle.draw(win)
        secret_code_x = secret_code_x + circle_diameter + h_circle_spacing
    return secret_code_circles

#PHASE 2
# Final text if the player loses the game
def create_and_display_final_text(win):
    center_of_text = Point(final_x, final_y)
    text_to_display = Text(center_of_text, "You Lost!")
    text_to_display.setSize(30)  # font size
    text_to_display.setTextColor('orange')
    text_to_display.draw( win )

# Final text to display if the player wins the game
def create_and_display_final_text_winner(win):
    center_of_text = Point(final_x, final_y)
    winner_text_to_display = Text(center_of_text, "You Win!")
    winner_text_to_display.setSize(30)  # font size
    winner_text_to_display.setTextColor('orange')
    winner_text_to_display.draw( win )

# Find which circle the user clicked on from the list and returns it. If they did not click in a valid space nothing will happen.
def find_clicked_circle(click_point, list_of_circles):
    for i in range(len(list_of_circles)):
        if is_click_in_circle(click_point, list_of_circles[i]):
            return i
    return None

# Is the click in a circle by seeing if the click point was anywhere in the area of a circle
def is_click_in_circle(click_point, circle):
    c_center = circle.getCenter()
    dist = (c_center.getX() - click_point.getX())**2 + (c_center.getY() - click_point.getY())**2
    return dist < circle_radius * circle_radius

# Move the feedback circles and empty circles up if the player does not select all four correct colors
def move_circles_up( circles, feedback_skel_circles ):
    for i in range (len(circles)):
        circles[i].move(0, -dy)
        feedback_skel_circles[i].move(0, -dy)
        win.update()
    return

# Does the players selection of color match the secret color?
def guess_is_right(secret_code_colors, guess_colors):
    for i in range (len(secret_code_colors)):
        if secret_code_colors[i] != guess_colors[i]:
            return False
    return True

# Feedback skels are used to determine if the user picked the right color or position of that color
def create_feedback_skel():

    feedback_circle_radius = 5
    feedback_x = leftmost_x + 5 * circle_radius * 2 + 4 * h_circle_spacing + feedback_circle_radius
    feedback_y = guess_y + circle_radius - feedback_circle_radius
    feedback_h_spacing = 20
    feedback_v_spacing = 20

    feedback_skel_circles = []
    for i in range (2):

        feedback_skel_center = Point(feedback_x, feedback_y)
        feedback_skel_circle = Circle(feedback_skel_center, feedback_circle_radius)
        feedback_skel_circles.append(feedback_skel_circle)
        #feedback_skel_circle.draw(win)
        feedback_x = feedback_x + feedback_h_spacing

    feedback_x = leftmost_x + 5 * circle_radius * 2 + 4 * h_circle_spacing + feedback_circle_radius
    feedback_y = feedback_y - feedback_h_spacing
    for i in range (2):
        feedback_skel_center = Point(feedback_x, feedback_y)
        feedback_skel_circle = Circle(feedback_skel_center, feedback_circle_radius)
        feedback_skel_circles.append(feedback_skel_circle)
        #feedback_skel_circle.draw(win)
        feedback_x = feedback_x + feedback_h_spacing



    return feedback_skel_circles


# Feedback circles are created and filled if appropriate colors are selected
def create_feedback_circles(secret_code_colors, guess_code_colors, feedback_skel_circles):
    feedback_circles = []
    guess_color_used = [False, False, False, False]
    secret_color_used = [False, False, False, False]
    feedback_idx = 0
    for i in range(4):
        if secret_code_colors[i] == guess_code_colors[i]:
            guess_color_used[i] = secret_color_used[i] = True
            c = feedback_skel_circles[feedback_idx].clone()
            feedback_idx += 1
            c.setFill('red')
            feedback_circles.append(c)
    for i in range(4):
        if not guess_color_used[i]:
            for j in range(4):
                if not secret_color_used[j] and secret_code_colors[j] == guess_code_colors[i]:
                    c = feedback_skel_circles[feedback_idx].clone()
                    c.setFill('white')
                    feedback_circles.append(c)
                    feedback_idx += 1
                    secret_color_used[j] = True
                    break
    return feedback_circles

# If player wants to change the color they have selected they can do so here
def move_colors(palette_circles, skel_circles, state_circle, exit_circle, win):
    skel_count = 0
    selected_idx = []
    guess_code_colors = ['white', 'white', 'white', 'white']
    while skel_count < 4:
        palette_click = win.getMouse()
        palette_idx = find_clicked_circle(palette_click, palette_circles)

        if is_click_in_circle( palette_click, exit_circle):
            win.close()
            sys.exit()

        if palette_idx is not None:
            state_circle.setFill(palette_colors[palette_idx])
            selected_skel_click = win.getMouse()
            skel_circle_idx = find_clicked_circle(selected_skel_click, skel_circles)
            if is_click_in_circle( selected_skel_click, exit_circle):
                win.close()
                sys.exit()
            if skel_circle_idx is not None:
                if skel_circle_idx in selected_idx:
                    hit_circle = skel_circles[skel_circle_idx]
                    another_circle = hit_circle.clone()
                    another_circle.setFill(palette_colors[palette_idx])
                    another_circle.draw(win)
                    state_circle.setFill('white')
                    guess_code_colors[skel_circle_idx]=palette_colors[palette_idx]
                else:
                    hit_circle = skel_circles[skel_circle_idx]
                    another_circle = hit_circle.clone()
                    another_circle.setFill(palette_colors[palette_idx])
                    another_circle.draw(win)
                    state_circle.setFill('white')
                    selected_idx.append(skel_circle_idx)
                    win.update()
                    skel_count += 1
                    guess_code_colors[skel_circle_idx]=palette_colors[palette_idx]
    return guess_code_colors

def main():
    exit_circle = create_exit_circle(win)
    state_circle = create_state_circle(win)
    palette_circles = create_palette_circle(palette_colors)
    skel_circles = create_skel_circle()
    secret_code_colors = create_secret_code_colors(palette_colors)
    secret_code_circles = create_secret_code_circles(secret_code_colors)
    feedback_skels = create_feedback_skel()
    win.update()

    for i in range (8):
        guess_colors = move_colors(palette_circles, skel_circles, state_circle, exit_circle, win)
        correct_guess = guess_is_right(secret_code_colors, guess_colors)
        feedback_circles = create_feedback_circles(secret_code_colors, guess_colors, feedback_skels)

        if correct_guess:
            break

        if i < 7:
            move_circles_up(skel_circles, feedback_skels)

        if i == 7:
            create_and_display_final_text(win)

        for i in range(len(feedback_circles)):
            feedback_circles[i].draw(win)

    if correct_guess:
        create_and_display_final_text_winner(win)
        for i in range(len(secret_code_circles)):
            feedback_circles[i].draw(win)





    win.getMouse()
    win.close()
main()




