from game_statistics import *
import time

a = SingleGameStatistics()
a.add_correct_input('x')
time.sleep(1)
a.add_incorrect_input('z')

b = a.get_typed_letters()
name = a.save_to_file()

reopened = SingleGameStatistics()
reopened.load_from_file(name)

def test_saved_and_parsed_class_matches_original():
    assert reopened.get_wpm() == a.get_wpm()
    assert reopened.get_raw_wpm() == a.get_raw_wpm()
    assert reopened.get_accuracy_percentage() == a.get_accuracy_percentage()
    assert reopened.get_number_of_words() == a.get_number_of_words()

    original_letters = a.get_typed_letters()
    reopened_letters = reopened.get_typed_letters()

    typed_letters_match = True

    for i in range(0, len(a.get_typed_letters())):
        if str(original_letters[i]) != str(reopened_letters[i]):
            typed_letters_match = False
            break
    
    assert typed_letters_match is True