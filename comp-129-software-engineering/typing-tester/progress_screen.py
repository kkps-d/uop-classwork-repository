"""
progress_screen.py File.
File to maintain ProgressScreen class.
"""

import pygame
import pandas as pd
import seaborn as sns
import matplotlib.pyplot as plt
from base_screen import BaseScreen
from scene_enum import SceneEnum

class ProgressScreen(BaseScreen):
    """
    ProgressScreen Class.
    This is the ProgressScreen class. 
    """

    def init_objects(self):
        self.progress_data = pd.read_csv("progress.txt")

        sns.lineplot(data=self.progress_data, x = "count", y = "accuracy", color = 'blue')
        plt.savefig('accuracy_chart.png')
        plt.clf()

        sns.lineplot(data=self.progress_data, x = "count", y = "speed", color = 'orange')
        plt.savefig('speed_chart.png')
        plt.clf()

        self.accuracy_chart = pygame.image.load('accuracy_chart.png')
        self.speed_chart = pygame.image.load('speed_chart.png')

        quarter = self.accuracy_chart.get_size()[0] / 4
        chart_height = self.accuracy_chart.get_size()[1]

        explanation_font = pygame.font.SysFont('Courier New', 64)

        accuracy_surface = explanation_font.render("LAST ACCURACY: " + str(self.progress_data.iloc[-1, 1]), True, (0, 0, 0), (255, 255, 255))
        self.py_screen.blit(accuracy_surface, (quarter, chart_height + 50))
        speed_surface = explanation_font.render("LAST WPM: " + str(self.progress_data.iloc[-1, 2]), True, (0, 0, 0), (255, 255, 255))
        self.py_screen.blit(speed_surface, (1920 - quarter - self.accuracy_chart.get_size()[0], chart_height + 50))
        
        center_width = self.py_screen.get_width() / 2

        self.init_label("MAIN MENU", center_width, 800)

    def handle_events(self):
        """
        ProgressScreen.handle_events() function.
        Handles events of ProgressScreen.
        """
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                quit()
            elif event.type == pygame.MOUSEBUTTONDOWN:
                if self.get_label_rect("MAIN MENU").collidepoint(event.pos):
                    return SceneEnum.SCENE_MENU

        quarter = self.accuracy_chart.get_size()[0] / 4
        self.py_screen.blit(self.accuracy_chart, (quarter, 50))
        self.py_screen.blit(self.speed_chart, (1920 - quarter - self.accuracy_chart.get_size()[0], 50))

        return self.screen_id
