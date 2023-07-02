"""
Main Class
"""

import pygame

from menu_screen import MenuScreen
from exercises_screen import ExercisesScreen
from game_screen import GameScreen
from progress_screen import ProgressScreen
from game_screen_2 import GameScreen2
from game_screen_3 import GameScreen3
from pick_wordset_screen import PickWordsetScreen
from word_set import WordSet
from timer import Timer

from scene_enum import SceneEnum

def main():
    """
    Main Function
    """
    pygame.font.init()
    pygame.freetype.init()
    screen = pygame.display.set_mode((1920, 1000))
    scene = SceneEnum.SCENE_MENU
    current_word_set = WordSet('wordsets/scrum.txt')
    current_timer_option = 60
    while True:
        if scene == SceneEnum.SCENE_MENU:
            scene = MenuScreen(SceneEnum.SCENE_MENU, screen, 30, current_word_set, current_timer_option).display()
        elif scene == SceneEnum.SCENE_EXERCISES:
            scene = ExercisesScreen(SceneEnum.SCENE_EXERCISES, screen, 60).display()
        elif scene == SceneEnum.SCENE_SPEED:
            scene = GameScreen2(SceneEnum.SCENE_SPEED, screen, 60, word_set=current_word_set, timer=current_timer_option).display()
        elif scene == SceneEnum.SCENE_ACCURACY:
            scene = GameScreen2(SceneEnum.SCENE_ACCURACY, screen, 60, False, word_set=current_word_set, timer=current_timer_option).display()
        elif scene == SceneEnum.SCENE_PROGRESS:
            scene = ProgressScreen(SceneEnum.SCENE_PROGRESS, screen, 60).display()
        elif scene == SceneEnum.SCENE_GAMEMODE_3:
            scene = GameScreen3(SceneEnum.SCENE_PROGRESS, screen, 60, word_set=current_word_set).display()
        elif scene == SceneEnum.SCENE_PICK_WORDSET:
            scene, new_word_set = PickWordsetScreen(SceneEnum.SCENE_PICK_WORDSET, screen, 60).display()
            current_word_set = new_word_set
        elif scene == SceneEnum.SCENE_PICK_TIMER:
            scene, new_timer_option = Timer(SceneEnum.SCENE_PICK_TIMER,screen, 60).display()
            current_timer_option = new_timer_option
        #elif scene == SceneEnum.SCENE_PICK_TIMER:
        #    scene, new_timer_option = TODOPickTimerScreen(SceneEnum.TODOSCENE_PICK_TIMER, screen, 60).display()
        #    current_timer_option = new_timer_option

if __name__ == "__main__":
    main()
