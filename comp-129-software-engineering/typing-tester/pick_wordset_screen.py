"""
pick_wordset_screen.py File.
File to maintain PickWordsetScreen class.
"""

import pygame
from base_screen import BaseScreen
from word_set import WordSet
from scene_enum import SceneEnum
import os

class PickWordsetScreen(BaseScreen):
    """
    PickWordsetScreen Class.
    This is the PickWordsetScreen class. 
    """
    def __init__(self, screen_id, py_screen, fps_cap):
        super().__init__(screen_id, py_screen, fps_cap)
        self._ws_list = []
        self.center_x = self.py_screen.get_width() / 2
        self.center_y = self.py_screen.get_height() / 2

    def init_objects(self):
        self.init_label("Select a wordset", self.center_x, self.center_y - 400, bg_color=(255,255,255))
        self.parse_wordsets()
        self.render_available_wordsets()

    def handle_events(self):
        """
        PickWordsetScreen.handle_events() function.
        Handles events of PickWordsetScreen.
        """
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                quit()
            elif event.type == pygame.MOUSEBUTTONDOWN:
                for ws in self._ws_list:
                    if self.get_label_rect(ws.name).collidepoint(event.pos):
                        return (SceneEnum.SCENE_MENU, ws)
                        # print(ws.name)

        return (self.screen_id, None)
    
    def display(self):
        """
        BaseScreen.display() function. Overrided to return multiple variables
        """
        self.py_screen.fill((255, 255, 255))
        self.init_objects()
        while True:
            self.clock.tick(self.fps_cap)
            new_screen, new_wordset = self.handle_events()
            if new_screen != self.screen_id:
                return (new_screen, new_wordset)
            pygame.display.update()
    
    def parse_wordsets(self):
        """Parse the wordsets in the 'wordsets' folder"""
        files = os.listdir('wordsets/')
        for file in files:
            ws = WordSet('wordsets/' + file)
            print(ws.name)
            print(ws.description)
            print(ws.get_words(10))
            self._ws_list.append(ws)

    def render_available_wordsets(self):
        max_cols = 3
        curr_row = 0
        curr_col = 0
        available_width = 1000 # Change this to change how close buttons are
        font_size = 48
        start_x = (self.py_screen.get_width() - available_width) / 2
        start_y = 300
        x_offset = available_width / (max_cols - 1)
        print(x_offset)
        y_offset = 100
        print(y_offset)
        for ws in self._ws_list:
            x = start_x + x_offset * curr_col
            y = start_y + y_offset * curr_row

            print(x, y, curr_row, curr_col, curr_col < max_cols)
            self.init_label(ws.name, x, y, font_size=font_size)

            if curr_col < max_cols - 1:
                curr_col += 1
            else:
                curr_col = 0
                curr_row += 1
