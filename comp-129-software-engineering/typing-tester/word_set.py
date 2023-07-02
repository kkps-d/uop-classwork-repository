"""
word_set.py
Contains the data structure that will be used to store all the word sets
"""

class WordSet():
    """
    Contains the WordSet class. This class parses the word set in a text file, 
    and then provides an easy to use interface to get the words from it.
    """

    def __init__(self, file_path: str) -> None:
        """Initialize the WordSet class"""
        self.words_buffer = []
        self.name = ""
        self.description = ""
        self.current_index = 0
        self._read_file(file_path)

    def _read_file(self, file_path: str) -> None:
        # Try to open the file
        try:
            file = open(file_path, "r+", encoding="utf-8")
        except FileNotFoundError:
            print(f'Failed to parse {file_path}. File not found.')
            return
        # Read the lines in the file
        lines = file.readlines()
        for line in lines:
            # For each line, remove trailing
            stripped_line = line.strip()

            # If the line starts with 'name=', parse the remaineder of the line and set is as name
            if stripped_line.startswith('name='):
                self.name = stripped_line.removeprefix('name=')
            # If the line starts with 'description=', parse the remaineder of the line and set is as description
            elif stripped_line.startswith('description='):
                self.description = stripped_line.removeprefix('description=')
            # Otherwise, parse as words to be typed
            else:
                # Split the lines by white space
                split_words = stripped_line.split(' ')
                # Add the new words to the class' word buffer
                self.words_buffer += split_words

    def get_words(self, word_count: int) -> list[str]:
        """Returns a list with the specified number of words"""
        temp_buffer = []
        for i in range(word_count):
            temp_buffer.append(self.words_buffer[self.current_index])
            self.current_index = (self.current_index + 1) % len(self.words_buffer)
        return temp_buffer
    
    def reset(self) -> None:
        """Resets the word set so it starts from the start again"""
        self.current_index = 0
