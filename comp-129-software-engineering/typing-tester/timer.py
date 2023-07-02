# import pygame
# import enum
# import sys
# from base_screen import BaseScreen
# from scene_enum import SceneEnum


# window_width = 1920
# window_height = 1000

# white = (255, 255, 255)
# black = (0, 0, 0)


# class TimeOption(enum.Enum):
#     ONE_MINUTE = {"label": "1 minute", "time": 60, "offset": -100}
#     TWO_MINUTES = {"label": "2 minutes", "time": 120, "offset": -50}
#     FIVE_MINUTES = {"label": "5 minutes", "time": 300, "offset": 0}
#     TEN_MINUTES = {"label": "10 minutes", "time": 600, "offset": 50}


# pygame.init()
# pygame.font.init()

# window = pygame.display.set_mode((window_width, window_height))
# pygame.display.set_caption("Timer")
# clock = pygame.time.Clock()

# font_small = pygame.font.Font(None, 24)
# font_large = pygame.font.Font(None, 48)


# selected_time_option = None
# timer_running = False
# elapsed_time = 0

# while True:
#     for event in pygame.event.get():
#         if event.type == pygame.QUIT:
#             pygame.quit()
#             sys.exit()
#         if event.type == pygame.MOUSEBUTTONUP:
#             pos = pygame.mouse.get_pos()
#             for time_option in TimeOption:
#                 if time_option.value["rect"].collidepoint(pos):
#                     selected_time_option = time_option
#                     elapsed_time = 0
#                     timer_running = True


#     dt = clock.tick(60) / 1000.0 


#     if timer_running:
#         elapsed_time += dt
#         remaining_time = selected_time_option.value["time"] - elapsed_time
#         if remaining_time <= 0:
#             timer_running = False

#     window.fill(white)
#     for time_option in TimeOption:
#         label = font_small.render(time_option.value["label"], True, black)
#         rect = label.get_rect()
#         rect.center = (window_width // 2, window_height // 2 + time_option.value["offset"])
#         time_option.value["rect"] = rect
#         window.blit(label, rect)
#     if timer_running:
#         timer_label = font_large.render("{:.1f}".format(remaining_time), True, black)
#         timer_rect = timer_label.get_rect()
#         timer_rect.center = (window_width // 2, window_height // 4)
#         window.blit(timer_label, timer_rect)
#     pygame.display.flip()



import pygame
import sys
import enum
from base_screen import BaseScreen
from scene_enum import SceneEnum


class TimeOption(enum.Enum):
    FIFTEEN_SECONDS = {"label": "15 seconds", "time": 15, "offset": -200}
    THIRTY_SECONDS = {"label": "30 seconds", "time": 30, "offset": -150}
    ONE_MINUTE = {"label": "1 minute", "time": 60, "offset": -100}
    TWO_MINUTES = {"label": "2 minutes", "time": 120, "offset": -50}
    FIVE_MINUTES = {"label": "5 minutes", "time": 300, "offset": 0}
    TEN_MINUTES = {"label": "10 minutes", "time": 600, "offset": 50}


class Timer(BaseScreen):
    def __init__(self, screen_id, py_screen, fps_cap):
        super().__init__(screen_id, py_screen, fps_cap)
        self.selected_time_option = None
        self.timer_running = False
        self.elapsed_time = 0
        self.white = (255, 255, 255)
        self.black = (0, 0, 0)
        self.font_small = pygame.font.Font(None, 24)
        self.font_large = pygame.font.Font(None, 48)

    def init_objects(self):
        self.timer_options_array = []
        for time_option in TimeOption:
            label = self.font_small.render(time_option.value["label"], True, self.black)
            rect = label.get_rect()
            rect.center = (self.py_screen.get_width() // 2, self.py_screen.get_height() // 2 + time_option.value["offset"])
            self.timer_options_array.append([time_option.value["time"], rect])

            self.py_screen.blit(label, rect)
        print("One")
        print(self.timer_options_array)

    def handle_events(self):
        print("Handling events")
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                pygame.quit()
                quit()
            if event.type == pygame.MOUSEBUTTONUP:
                print("Pushed up")
                pos = pygame.mouse.get_pos()
                for time_option in self.timer_options_array:
                    if time_option[1].collidepoint(pos):
                        self.selected_time_option = time_option[0]
                        print("Should print")
                        print(self.selected_time_option)
                        self.elapsed_time = 0
                        self.timer_running = True
                        return (SceneEnum.SCENE_MENU,self.selected_time_option)
                    
                #for time_option in TimeOption:
                #    if time_option.value["rect"].collidepoint(pos):
                #        self.selected_time_option = time_option
                ##        self.elapsed_time = 0
                #        self.timer_running = True
                #        return (SceneEnum.SCENE_MENU,self.selected_time_option)
        return (self.screen_id, None)

    def display(self):
        self.init_objects()
        while True:
            #new_screen = super().display()
            new_screen, new_selected_time = self.handle_events()
            if new_screen != self.screen_id:
                return (new_screen, new_selected_time)
            dt = self.clock.tick(self.fps_cap) / 1000.0 

            if self.timer_running:
                self.elapsed_time += dt
                remaining_time = self.selected_time_option.value["time"] - self.elapsed_time
                if remaining_time <= 0:
                    self.timer_running = False

            self.py_screen.fill(self.white)
            for time_option in TimeOption:
                label = self.font_small.render(time_option.value["label"], True, self.black)
                rect = label.get_rect()
                rect.center = (self.py_screen.get_width() // 2, self.py_screen.get_height() // 2 + time_option.value["offset"])
                self.py_screen.blit(label, rect)
            if self.timer_running:
                timer_label = self.font_large.render("{:.1f}".format(remaining_time), True, self.black)
                timer_rect = timer_label.get_rect()
                timer_rect.center = (self.py_screen.get_width() // 2, self.py_screen.get_height() // 4)
                self.py_screen.blit(timer_label, timer_rect)
            pygame.display.flip()
    