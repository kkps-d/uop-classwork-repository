"""
menu_screen.py File.
File to maintain MenuScreen class.
"""

import pygame
from base_screen import BaseScreen
from scene_enum import SceneEnum

class MenuScreen(BaseScreen):
    """
    MenuScreen Class.
    This is the MenuScreen class. 
    """
    def __init__(self, screen_id, py_screen, fps_cap, word_set, current_timer):
        super().__init__(screen_id, py_screen, fps_cap)
        self._ws_name = word_set.name
        self.current_timer = current_timer

    def init_objects(self):
        """
        MenuScreen.init_objects() function.
        Handles initializations of objects for MenuScreen.
        """
        center_width = self.py_screen.get_width() / 2
        center_height = self.py_screen.get_height() / 2
        self.init_label("PLAY", center_width - 600, center_height)
        # self.init_label("CUSTOM", center_width + 600, center_height)
        self.init_label("PROGRESS", center_width, center_height + 300)
        self.init_label("CHANGE TOPIC", center_width, center_height)
        self.init_label('Current topic: ' + self._ws_name, center_width, center_height + 60, font_size=28, bg_color=(255,255,255))
        self.init_label("TIMING OPTIONS", center_width-600, center_height+300)
        self.init_label(f'Time (seconds): {self.current_timer}', center_width - 600, center_height + 360, font_size=28, bg_color=(255,255,255))

    def handle_events(self):
        """
        MenuScreen.handle_events() function.
        Handles events of MenuScreen.
        """
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                quit()
            elif event.type == pygame.MOUSEBUTTONDOWN:
                if self.get_label_rect("PLAY").collidepoint(event.pos):
                    return SceneEnum.SCENE_EXERCISES
                elif self.get_label_rect("PROGRESS").collidepoint(event.pos):
                    return SceneEnum.SCENE_PROGRESS
                elif self.get_label_rect("CHANGE TOPIC").collidepoint(event.pos):
                    return SceneEnum.SCENE_PICK_WORDSET
                elif self.get_label_rect("TIMING OPTIONS").collidepoint(event.pos):
                    return SceneEnum.SCENE_PICK_TIMER

        return self.screen_id
