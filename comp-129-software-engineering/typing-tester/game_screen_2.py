import pygame
import pygame.font
from scene_enum import SceneEnum
from base_screen import BaseScreen
from word_set import WordSet
from game_statistics import SingleGameStatistics

class GameScreen2(BaseScreen):
    def __init__(self, screen_id, py_screen, fps_cap, is_timer_enabled = True, word_set=None, timer=60):
        super().__init__(screen_id, py_screen, fps_cap)
        self.is_timer_enabled = is_timer_enabled
        self.stats = SingleGameStatistics()
        # Load provided word set
        if word_set is None:
            raise Exception('Provided word set is invalid!')
        else:
            self.word_set = word_set

        # Initialize timer variables
        if self.is_timer_enabled:
            self.timer_counter, self.timer_text = timer, str(timer).rjust(3)
            pygame.time.set_timer(pygame.USEREVENT, 1000)

    def init_objects(self):
        # Set dimensions and theme
        self.rect_border_color = (255, 108, 76)
        self.font_size = 40
        self.font = pygame.freetype.SysFont('Courier New', size=self.font_size)
        # Use origin of text for coordinates instead of top left corner of bounding box (self.text_surface)
        # https://stackoverflow.com/questions/64966471/how-to-change-the-color-a-section-of-text-in-pygame
        self.font.origin = True
        self.text_box_width = 1000
        self.text_box_height = 350
        self.text_box_border_width = 5
        self.text_box_horizontal_padding = 20
        self.text_box_fill_color = 'black'
        self.text_color = 'lightgrey'
        self.text_correct_color = 'green'
        self.text_wrong_color = 'red'
        self.line_count = 3

        # Set the variables for the typing game
        self.typing_current_line_index = 0
        self.typing_current_letter_index = 0
        self.cursor_rect = pygame.Rect(0,0,0,0)
        self.cursor_color = 'aqua'

        # Create the necessary components
        # Get center of screen
        screen_center_x, screen_center_y = self.py_screen.get_rect().center
        # Create the text surface
        self.text_surface = pygame.Surface((self.text_box_width, self.text_box_height))

        # Get a Rect with the same dimensions of the surface before and center it
        self.text_surface_rect = self.text_surface.get_rect()
        # Apply 100 vertical offset upwards from center
        self.text_surface_rect.center = (screen_center_x, screen_center_y - 100)

        # Get the space width for the current font
        self.space_width = self.font.get_metrics(" ")[0][4]

        # Calculate each line heigiht
        text_box_avail_height = self.text_box_height - self.text_box_border_width * 2
        each_line_height = text_box_avail_height / self.line_count
        self.line_height = each_line_height

        # All words that are taken from word_set is stored here. Each word will be processed
        # and fitted to the text Surface
        self.word_buffer = []

        # There will be multiple lines on the screen
        # Each line will have a buffer of letter metrics, and the following
        # list contains all buffers for those lines
        # Initialize a fixed list for those lines
        self.letter_buffer_lines = [None] * self.line_count
        for i in range(self.line_count):
            self.letter_buffer_lines[i] = []

        self.fit_word_buffer_to_line(0)
        self.fit_word_buffer_to_line(1)
        self.fit_word_buffer_to_line(2)

        self.render_to_text()

        # Update the entire display
        pygame.display.flip()

        

    def set_word_set(self, w_s: WordSet) -> None:
        """Set the word set for this game screen"""
        #! untested
        self.word_set = w_s
        self.word_buffer = []


    def string_pop(self, string) -> tuple[str,str]:
        """Removes and returns the first letter of provided string"""
        first_letter = string[:1]
        new_string = string[1:]
        return (first_letter, new_string)        

    def fit_word_buffer_to_line(self, line_index):
        """Fits words from word_buffer and fit it into the specified line.
        If word_buffer is empty, get new lines from word_set"""
        if (line_index > self.line_count - 1):
            print("Out of bounds for letter_buffer_lines")
            return
        
        # Calculate the maximum allowed width for each line on the text surface
        max_line_width = self.text_box_width\
        - (self.text_box_border_width * 2)\
        - (self.text_box_horizontal_padding * 2)

        current_line_width = 0

        while True: # Until the line is not full
            # If the word_buffer is empty, get more words
            if len(self.word_buffer) < 1:
                self.word_buffer += self.word_set.get_words(50)

            # Get the next word in the word_buffer
            word = self.word_buffer[0]
            # print(f"Next word in line: {word}")

            temp_letter_buffer = []
            word_width = 0
            # For each letter in the word, calculate the word width and store in temporaray buffer
            for letter in word:
                # Get the metric of the letter
                metric = self.font.get_metrics(letter)[0]

                # Create a dict with all the letter details
                letter_metrics = {
                    "letter": letter,
                    "width": metric[4],
                    "type_status": 0 # 0 - Untyped, 1 - Correct, 2 - Incorrect
                }

                # Add the letters' width to the word width
                word_width += letter_metrics["width"]

                # Add the new dict to a temporary buffer
                temp_letter_buffer.append(letter_metrics)

            # Check if the current line width + word width is within max width
            if current_line_width + word_width <= max_line_width:
                # print(f"line width: {current_line_width + word_width}, max width: {max_line_width}")
                # If so, add the word to the line and a space
                self.letter_buffer_lines[line_index] += temp_letter_buffer
                self.letter_buffer_lines[line_index].append({
                    "letter": " ",
                    "width": self.space_width,
                    "type_status": 0 # 0 - Untyped, 1 - Correct, 2 - Incorrect
                })
                # Increase the current line width with word and one space width
                current_line_width = current_line_width + word_width + self.space_width

                # Remove the processed word
                self.word_buffer.pop(0)
            else:
                # If not, remove the trailing space
                # self.letter_buffer_lines[line_index] = self.letter_buffer_lines[line_index][:-1]
                break

    def fit_word_buffer_to_lines(self):
        """Turns a string into a list of letters and its metrics, and use that information to fit
        the big screen into the three lines"""

        # Calculate the maximum allowed width for each line on the text surface
        max_line_width = self.text_box_width\
        - (self.text_box_border_width * 2)\
        - (self.text_box_horizontal_padding * 2)

        # For each line displayed on screen
        for line_number in range(self.line_count):
            current_line_width = 0

            while True: # Until the line is not full
                # If the word_buffer is empty, get more words
                if len(self.word_buffer) < 1:
                    self.word_buffer += self.word_set.get_words(50)

                # Get the next word in the word_buffer
                word = self.word_buffer[0]
                # print(f"Next word in line: {word}")

                temp_letter_buffer = []
                word_width = 0
                # For each letter in the word, calculate the word width and store in temporaray buffer
                for letter in word:
                    # Get the metric of the letter
                    metric = self.font.get_metrics(letter)[0]

                    # Create a dict with all the letter details
                    letter_metrics = {
                        "letter": letter,
                        "width": metric[4],
                        "type_status": 0 # 0 - Untyped, 1 - Correct, 2 - Incorrect
                    }

                    # Add the letters' width to the word width
                    word_width += letter_metrics["width"]

                    # Add the new dict to a temporary buffer
                    temp_letter_buffer.append(letter_metrics)

                # Check if the current line width + word width is within max width
                if current_line_width + word_width <= max_line_width:
                    # print(f"line width: {current_line_width + word_width}, max width: {max_line_width}")
                    # If so, add the word to the line and a space
                    self.letter_buffer_lines[line_number] += temp_letter_buffer
                    self.letter_buffer_lines[line_number].append({
                        "letter": " ",
                        "width": self.space_width,
                        "type_status": 0 # 0 - Untyped, 1 - Correct, 2 - Incorrect
                    })
                    # Increase the current line width with word and one space width
                    current_line_width = current_line_width + word_width + self.space_width

                    # Remove the processed word
                    self.word_buffer.pop(0)
                else:
                    # If not, go to the next line
                    break

    def render_to_text(self):
        """Render the letter_buffer_lines onto the screen"""
        current_y = self.line_height + self.text_box_border_width
        for line_index, line in enumerate(self.letter_buffer_lines):
            current_x = self.text_box_border_width + self.text_box_horizontal_padding

            # Render letter by letter
            for letter_index, letter_metric in enumerate(line):
                # Determine the color of the letter
                if letter_metric["type_status"] == 1:
                    font_color = self.text_correct_color
                elif letter_metric["type_status"] == 2:
                    font_color = self.text_wrong_color
                else:
                    font_color = self.text_color

                ## Special case for mistyped white spaces (" ")
                if letter_metric["type_status"] == 2 and letter_metric["letter"] == " ":
                    self.font.render_to(
                        self.text_surface,
                        (current_x, current_y - (self.line_height / 2) + (self.font_size / 2)),
                        "_", font_color
                    )
                else:
                    self.font.render_to(
                        self.text_surface,
                        (current_x, current_y - (self.line_height / 2) + (self.font_size / 2)),
                        letter_metric["letter"], font_color
                    )

                # Determine cursor location
                if line_index == self.typing_current_line_index and \
                letter_index == self.typing_current_letter_index:
                    # x and y coordinates relative to the window
                    absolute_x = current_x + self.text_surface_rect.left
                    absolute_y = (current_y - (self.line_height / 2) + (self.font_size / 2)) + self.text_surface_rect.top + 10
                    
                    # Create a new Rect for the cursor at the defined location
                    self.cursor_rect = pygame.Rect(absolute_x, absolute_y, letter_metric["width"], 5)

                current_x += letter_metric["width"]

            current_y += self.line_height


        # Blit (copy) contents of surface to rect
        self.py_screen.blit(self.text_surface, self.text_surface_rect)

        # Draw the border of the rect on top
        pygame.draw.rect(self.py_screen, self.rect_border_color, self.text_surface_rect, 5)

        # Draw the cursor
        pygame.draw.rect(self.py_screen, self.cursor_color, self.cursor_rect)

        self.text_surface.fill(self.text_box_fill_color)

    def handle_events(self):
        for event in pygame.event.get():
            if event.type == pygame.USEREVENT: 
                self.timer_counter -= 1
                if (self.timer_counter > 0):
                    self.timer_text = str(self.timer_counter).rjust(3)
                else:
                    print(f"Correct: {self.stats._correct_keypresses}, Incorrect: {self.stats._incorrect_keypresses}, Accuracy: {self.stats.get_accuracy_percentage()}, Words typed: {self.stats.get_number_of_words()}, WPM: {self.stats.get_wpm()}, RWPM: {self.stats.get_raw_wpm()}")
                    self.save_progress(self.stats.get_accuracy_percentage(), self.stats.get_wpm())
                    self.stats.save_to_file()
                    return SceneEnum.SCENE_PROGRESS
            if event.type == pygame.QUIT:
                quit()

            if event.type == pygame.KEYDOWN:
                # Ignore shifts
                if event.key == pygame.K_LSHIFT or event.key == pygame.K_RSHIFT:
                    continue

                # Check for backspace
                if event.key == pygame.K_BACKSPACE:
                    if self.typing_current_letter_index > 0:
                        self.typing_current_letter_index -= 1
                        self.letter_buffer_lines[self.typing_current_line_index][self.typing_current_letter_index]["type_status"] = 0
                else:
                    # Check if input is correct
                    current_letter = self.letter_buffer_lines[self.typing_current_line_index][self.typing_current_letter_index]["letter"]
                    print(f"Unicode: {event.unicode}, Current: {current_letter}, Match: {current_letter == event.unicode}")
                    if current_letter == event.unicode:
                        self.stats.add_correct_input(current_letter)
                        self.letter_buffer_lines[self.typing_current_line_index][self.typing_current_letter_index]["type_status"] = 1
                    else:
                        self.stats.add_incorrect_input(current_letter)
                        self.letter_buffer_lines[self.typing_current_line_index][self.typing_current_letter_index]["type_status"] = 2
                        if self.is_timer_enabled == False:
                            print(f"Correct: {self.stats._correct_keypresses}, Incorrect: {self.stats._incorrect_keypresses}, Accuracy: {self.stats.get_accuracy_percentage()}, Words typed: {self.stats.get_number_of_words()}, WPM: {self.stats.get_wpm()}, RWPM: {self.stats.get_raw_wpm()}")
                            self.save_progress(self.stats.get_accuracy_percentage(), self.stats.get_wpm())
                            self.stats.save_to_file()
                            return SceneEnum.SCENE_PROGRESS
                    self.typing_current_letter_index += 1

                    # Go to next line if end of line is reached
                    if self.typing_current_letter_index > len(self.letter_buffer_lines[self.typing_current_line_index]) - 1:
                        # If you are on the second line, remove first line, replace with second, and add another line
                        self.typing_current_letter_index = 0
                        if self.typing_current_line_index == 1:
                            self.letter_buffer_lines = self.letter_buffer_lines[1:]
                            self.letter_buffer_lines.append([])
                            self.fit_word_buffer_to_line(2)
                        else:
                            self.typing_current_line_index += 1
                self.render_to_text()

        if self.is_timer_enabled:
            timer_font = pygame.font.SysFont('Courier New', 64)
            timer_surface = timer_font.render(self.timer_text, True, (0, 0, 0), (255, 255, 255))
            self.py_screen.blit(timer_surface, (0, 900))

            pygame.display.flip()

        return self.screen_id
    
    def save_progress(self, accuracy, speed):
        fileOpen = open("progress.txt")
        fileAppend = open("progress.txt", "a")

        if not fileOpen.read(1):
            fileAppend.write("count,accuracy,speed\n")
        fileOpen.close()
        
        count = sum(1 for line in open("progress.txt"))

        accuracy_str = str(round(accuracy, 1))
        speed_str = str(round(speed, 1))

        fileAppend.write("\n" + str(count) + "," + accuracy_str + "," + speed_str)
        fileAppend.close()