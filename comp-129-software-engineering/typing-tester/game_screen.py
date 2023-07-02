"""
game_screen.py File.
File to maintain GameScreen class.
"""

# TextWrap Resource: https://stackoverflow.com/questions/65785917/can-you-text-wrap-displayed-text-in-pygame
import textwrap
from itertools import cycle
import pygame
import pygame.freetype
from scene_enum import SceneEnum
from base_screen import BaseScreen
from game_statistics import SingleGameStatistics

class GameScreen(BaseScreen):
    """
    GameScreen Class.
    This is the GameScreen class. 
    """

    def __init__(self, screen_id, py_screen, fps_cap):
        super().__init__(screen_id, py_screen, fps_cap)
        self.user_text = ""
        self.lines = None
        self.stats = SingleGameStatistics()

    def init_objects(self):
        """
        GameScreen.init_objects() function.
        Handles initializations of objects for GameScreen.
        """

        test_string = ""
        for i in range(50):
            test_string += "This is a sentence."

        lines = textwrap.wrap(test_string, 50, break_long_words=True)

        #https://stackoverflow.com/questions/64966471/how-to-change-the-color-a-section-of-text-in-pygame
        self.data = cycle(lines)
        self.current = next(self.data)
        self.current_idx = 0 # points to the current letter, as you have already guessed
        
        self.font = pygame.freetype.Font(None, 50)
        # the font in the new freetype module have an origin property.
        # if you set this to True, the render functions take the dest position 
        # to be that of the text origin, as opposed to the top-left corner
        # of the bounding box
        self.font.origin = True
        font_height = self.font.get_sized_height()
        
        # we want to know how much space each letter takes during rendering.
        # the item at index 4 is the 'horizontal_advance_x'
        self.M_ADV_X = 4
        
        # let's calculate how big the entire line of text is
        self.text_surf_rect = self.font.get_rect(self.current)
        # in this rect, the y property is the baseline
        # we use since we use the origin mode
        self.baseline = self.text_surf_rect.y
        # now let's create a surface to render the text on
        # and center it on the screen
        self.text_surf = pygame.Surface(self.text_surf_rect.size)
        self.text_surf_rect.center = self.py_screen.get_rect().center
        # calculate the width (and other stuff) for each letter of the text
        self.metrics = self.font.get_metrics(self.current)


        self.counter, self.text = 10, '10'.rjust(3)
        pygame.time.set_timer(pygame.USEREVENT, 1000)

    def handle_events(self):
        """
        GameScreen.handle_events() function.
        Handles events of GameScreen.
        """

        # TIMER 
        # https://stackoverflow.com/questions/30720665/countdown-timer-in-pygame

        for event in pygame.event.get():
            if event.type == pygame.USEREVENT: 
                self.counter -= 1
                if (self.counter > 0):
                    self.text = str(self.counter).rjust(3)
                else:
                    print(f"Correct: {self.stats._correct_keypresses}, Incorrect: {self.stats._incorrect_keypresses}, Accuracy: {self.stats.get_accuracy_percentage()}")
                    return SceneEnum.SCENE_PROGRESS
            if event.type == pygame.QUIT:
                quit()
            if event.type == pygame.KEYDOWN:
                if event.unicode == self.current[self.current_idx].lower():
                    self.stats.add_correct_input()
                    # if we press the correct letter, move the index
                    self.current_idx += 1
                    if self.current_idx >= len(self.current):
                        # if the sentence is complete, let's prepare the
                        # next surface
                        self.current_idx = 0
                        self.current = next(self.data)
                        self.text_surf_rect = self.font.get_rect(self.current)
                        self.baseline = self.text_surf_rect.y
                        self.text_surf = pygame.Surface(self.text_surf_rect.size)
                        self.text_surf_rect.center = self.py_screen.get_rect().center
                        self.metrics = self.font.get_metrics(self.current)
                else:
                    # User input is incorrect
                    self.stats.add_incorrect_input()
                
                
                                      
        self.py_screen.fill('white')
        self.text_surf.fill('white')

        my_font = pygame.font.SysFont('Comic Sans MS', 30)

        test_surface = my_font.render(self.text, True, (0, 0, 0))
        self.py_screen.blit(test_surface, (32, 48))

        x = 0
        # render each letter of the current sentence one by one
        for (idx, (letter, metric)) in enumerate(zip(self.current, self.metrics)):
            # select the right color
            if idx == self.current_idx:
                color = 'lightblue'
            elif idx < self.current_idx:
                color = 'lightgrey'
            else:
                color = 'black'
            # render the single letter
            self.font.render_to(self.text_surf, (x, self.baseline), letter, color)
            # and move the start position
            x += metric[self.M_ADV_X]
          
        self.py_screen.blit(self.text_surf, self.text_surf_rect)

        pygame.display.flip()

        return self.screen_id
    