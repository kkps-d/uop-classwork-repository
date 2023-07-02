"""This file contains the classes that deal with the statistics of the user"""

from datetime import datetime
import json

class LetterMetadata:
    """Stores the information of a typed letter for more advanced statistics"""
    def __init__(self, is_correct: bool, letter: str, time_stamp: datetime) -> None:
        """Initialize the class"""
        self.is_correct = is_correct
        self.letter = letter
        self.time_stamp = time_stamp

    def __str__(self) -> str:
        """Returns the string representation of the class"""
        return f"{self.is_correct},{self.letter},{self.time_stamp.timestamp()}"

    @staticmethod
    def from_string(string) -> 'LetterMetadata':
        """Creates LetterMetadata object from string representation provided by self.to_string()"""
        split = string.split(',')
        temp = LetterMetadata(
            eval(split[0]),
            split[1],
            datetime.fromtimestamp(float(split[2]))
        )
        return temp

class SingleGameStatistics:
    """Stores the statistics for a single game session"""
    def __init__(self) -> None:
        """Initialize the class"""
        self._correct_keypresses = 0
        self._incorrect_keypresses = 0
        self._accuracy_percentage = 0
        self._typed_letters = []
        self._word_count = 0
        self._start_time = None
        self._latest_time = 0

    def add_correct_input(self, letter: str) -> None:
        """Add a correct keypress"""
        now_time = datetime.now()
        self._correct_keypresses += 1
        self._typed_letters.append(
            LetterMetadata(True, letter, now_time)
        )
        if self._start_time is None:
            self._start_time = now_time
        else:
            self._latest_time = now_time

    def add_incorrect_input(self, letter: str) -> None:
        """Add an incorrect keypress"""
        # Prevent incorrect keypresses from increasing at the start of the game,
        # determined by having 0 correct keypresses, to prevent very large negative numbers
        if self._correct_keypresses > 0:
            now_time = datetime.now()
            self._incorrect_keypresses += 1
            self._typed_letters.append(
                LetterMetadata(False, letter, now_time)
            )
            self._latest_time = now_time

    def get_accuracy_percentage(self) -> float:
        """Return the accuracy as a percentage"""
        if (self._correct_keypresses + self._incorrect_keypresses) == 0:
            # Prevents divison by 0 at the start of the game
            return 0
        else:
            # Accuracy = (correct keypresses / total keypresses) * 100
            return (self._correct_keypresses / \
                (self._correct_keypresses + self._incorrect_keypresses)) * 100

    def get_number_of_words(self) -> int:
        """Get the number of words typed"""
        return self._correct_keypresses / 5

    def get_typed_letters(self) -> list[LetterMetadata]:
        """Get the typed letters and its metadata"""
        return self._typed_letters

    def get_wpm(self) -> int:
        """Get the words per minute"""
        # Prevents edge case where user gets the first input wrong on accuracy mode
        if self._start_time is None:
            return 0
        time_difference_secs = (self._latest_time - self._start_time).seconds
        # Prevents division by zero
        if time_difference_secs < 1:
            return 0

        # Assume words to be 5 characters, symbols and whitespace included
        # https://support.sunburst.com/hc/en-us/articles/229335208-Type-to-Learn-How-are-Words-Per-Minute-and-Accuracy-Calculated
        word_count = self._correct_keypresses / 5
        words_per_second = word_count / time_difference_secs
        projected_wpm = words_per_second * 60
        return projected_wpm

    def get_raw_wpm(self) -> int:
        """Get the raw words per minute, which includes wrong words too"""
        # Prevents edge case where user gets the first input wrong on accuracy mode
        if self._start_time is None:
            return 0
        time_difference_secs = (self._latest_time - self._start_time).seconds
        # Prevents division by zero
        if time_difference_secs < 1:
            return 0

        # Assume words to be 5 characters, symbols and whitespace included
        # https://support.sunburst.com/hc/en-us/articles/229335208-Type-to-Learn-How-are-Words-Per-Minute-and-Accuracy-Calculated
        word_count = (self._correct_keypresses + self._incorrect_keypresses) / 5
        words_per_second = word_count / time_difference_secs
        projected_wpm = words_per_second * 60
        return projected_wpm

    def save_to_file(self) -> str:
        """Save the game statistics to file, and returns filename"""
        
        saved_time = datetime.now()
        time_string = saved_time.strftime("%Y%m%d-%H%M%S")
        filename = f'statistics-history/statistics-{time_string}.json'

        # Get timestamp of _start_time
        if self._start_time is None:
            start_time_timestamp = None
        else:
            start_time_timestamp = self._start_time.timestamp()

        # Convert list of LetterMetadata to list of string representations
        typed_letters_string_list = []
        for let_met in self._typed_letters:
            typed_letters_string_list.append(str(let_met))

        result_dict = {
            'save_timestamp': saved_time.timestamp(),
            'correct_keypresses': self._correct_keypresses,
            'incorrect_keypresses': self._incorrect_keypresses,
            'accuracy_percentage': self._accuracy_percentage,
            'word_count': self._word_count,
            'start_time_timestamp': start_time_timestamp,
            'latest_time_timestamp': self._latest_time.timestamp(),
            'typed_letters': typed_letters_string_list
        }
        
        file = open(filename, "w")
        file.write(json.dumps(result_dict, indent=4))
        file.close()

        return filename

    def load_from_file(self, file_path) -> None:
        """Load the game statistics from a given filepath"""
        try:
            file = open(file_path, "r+", encoding="utf-8")
        except FileNotFoundError:
            print(f'Failed to parse {file_path}. File not found.')
            return

        contents = file.read()
        loaded_dict = json.loads(contents)

        self._correct_keypresses = loaded_dict['correct_keypresses']
        self._incorrect_keypresses = loaded_dict['incorrect_keypresses']
        self._accuracy_percentage = loaded_dict['accuracy_percentage']
        self._word_count = loaded_dict['word_count']

        start_time = loaded_dict['start_time_timestamp']
        if start_time is None:
            self._start_time = None
        else:
            self._start_time = datetime.fromtimestamp(start_time)

        self._latest_time = datetime.fromtimestamp(loaded_dict['latest_time_timestamp'])

        for str_rep in loaded_dict['typed_letters']:
            self._typed_letters.append(LetterMetadata.from_string(str_rep))
