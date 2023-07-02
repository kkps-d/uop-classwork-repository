from word_set import WordSet

ws = WordSet('wordsets/test_wordset.txt')

def test_getting_first_50_words():
    words = ws.get_words(50)
    assert len(words) == 50

def test_50_words_are_expected():
    expected_words = ['a', 'very', 'extensible', 'system,', 'easy', 'to', 'write', 'plugins', 'and', 'there', 'are', 'a', 'lot', 'of', 'plugins', 'present', 'in', 'the', 'pytest', 'that', 'are', 'used', 'for', 'various', 'purposes.', 'Testing', 'is', 'very', 'important', 'before', 'delivering', 'the', 'code', 'in', 'production.', 'It', 'is', 'a', 'mature', 'full-featured', 'Python', 'tool', 'that', 'helps', 'to', 'write', 'better', 'programs.', 'pytest', 'is']
    words = ws.get_words(50)
    assert expected_words == words

def test_get_1000_words_and_not_crash():
    words = ws.get_words(1000)
    assert len(words) == 1000
