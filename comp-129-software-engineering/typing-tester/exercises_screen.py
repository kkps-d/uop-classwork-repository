"""
exercises_screen.py File.
File to maintain ExercisesScreen class.
"""

import pygame
from base_screen import BaseScreen
from scene_enum import SceneEnum

class ExercisesScreen(BaseScreen):
    """
    ExercisesScreen Class.
    This is the ExercisesScreen class. 
    """

    def init_objects(self):
        """
        ExercisesScreen.init_objects() function.
        Handles initializations of objects for ExercisesScreen.
        """
        center_width = self.py_screen.get_width() / 2
        center_height = self.py_screen.get_height() / 2
        self.init_label("SPEED", center_width - 600, center_height)
        self.init_label("ACCURACY", center_width, center_height)
        self.init_label("FUN RUN", center_width + 600, center_height)

    def handle_events(self):
        """
        ExercisesScreen.handle_events() function.
        Handles events of ExercisesScreen.
        """
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                quit()
            elif event.type == pygame.MOUSEBUTTONDOWN:
                if self.get_label_rect("SPEED").collidepoint(event.pos):
                    return SceneEnum.SCENE_SPEED #TODO Change
                elif self.get_label_rect("ACCURACY").collidepoint(event.pos):
                    return SceneEnum.SCENE_ACCURACY #TODO Change
                elif self.get_label_rect("FUN RUN").collidepoint(event.pos):
                    return SceneEnum.SCENE_GAMEMODE_3 #TODO Change
                

        return self.screen_id
