"""
screen_label.py File.
"""

class ScreenLabel():
    """
    ScreenLabel Class.
    This is the ScreenLabel class. 
    """
    def __init__(self, name, text, rect):
        self.name = name
        self.text = text
        self.rect = rect

    def get_name(self):
        """
        ScreenLabel.get_name() function.
        Gets name of ScreenLabel.
        """
        return self.name
    def get_text(self):
        """
        ScreenLabel.get_text() function.
        Gets text of ScreenLabel.
        """
        return self.text
    def get_rect(self):
        """
        ScreenLabel.get_rect() function.
        Gets rect of ScreenLabel.
        """
        return self.rect
    