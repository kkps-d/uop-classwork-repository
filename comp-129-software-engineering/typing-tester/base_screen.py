"""
base_screen.py File.
File to maintain BaseScreen class.
"""

import pygame
from screen_label import ScreenLabel

class BaseScreen:
    """
    BaseScreen Class.
    This will be utilized for the different menus of the game.
    """

    def __init__(self, screen_id, py_screen, fps_cap):
        self.screen_id = screen_id
        self.py_screen = py_screen
        self.fps_cap = fps_cap # Consider FPS option in game settings?
        self.clock = pygame.time.Clock()
        self.labels = []

    def init_objects(self):
        """
        BaseScreen.init_objects() function.
        Handles initializations of objects. Should be overridden by child classes.
        """

    def handle_events(self):
        """
        BaseScreen.handle_events() function.
        Handles events of screen. Should be overridden by child classes.
        """
        return self.screen_id

    def display(self):
        """
        BaseScreen.display() function.
        Displays the screen. 
        """
        self.py_screen.fill((255, 255, 255))
        self.init_objects()
        while True:
            self.clock.tick(self.fps_cap)
            new_screen = self.handle_events()
            if new_screen != self.screen_id:
                return new_screen
            pygame.display.update()

    def init_label(self, text_string, x_pos, y_pos, font_family='Courier New', font_size=64, bg_color=(0, 255, 255)):
        """
        BaseScreen.init_label(text_string, x_pos, y_pos) function.
        Initializes a label for current screen.
        Used as button or label.
        """
        font = pygame.font.SysFont(font_family, font_size)
        text = font.render(text_string, True, (0, 0, 0))
        rect = text.get_rect(center=(x_pos,y_pos))

        pygame.draw.rect(self.py_screen, bg_color, rect, 0)

        self.py_screen.blit(text, rect)

        screen_label = ScreenLabel(text_string, text, rect)
        self.labels.append(screen_label)

    def get_label_rect(self, label_name):
        """
        BaseScreen.get_label_rect(label_name) function.
        Gets the label rect of label name.
        Used for event checks.
        """
        for label in self.labels:
            if label.get_name() == label_name:
                return label.get_rect()
        return None
    