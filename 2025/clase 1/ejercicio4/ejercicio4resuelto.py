def count_word_frequency(sentence):
    """
    Counts the frequency of each word in a given sentence.
    """
    word_frequency = {}
    words = sentence.split()
    for word in words:
        word = word.lower().strip(",.?!")
        if word in word_frequency:
            word_frequency[word] += 1
        else:
            word_frequency[word] = 1
    return word_frequency

# Test Cases
def test_count_word_frequency():
    test_cases = [
        ("hello world hello", {"hello": 2, "world": 1}),
        ("test test test", {"test": 3}),
        ("a quick brown fox", {"a": 1, "quick": 1, "brown": 1, "fox": 1}),
        ("one two one two one", {"one": 3, "two": 2}),
        ("", {}),
        ("same same same same", {"same": 4}),
    ]
    
    for i, (sentence, expected) in enumerate(test_cases):
        result = count_word_frequency(sentence)
        assert result == expected, f"FAILED on case {i + 1}: expected {expected}, but got {result}"
    print("All tests PASSED.")

# Run Tests
if __name__ == "__main__":
    test_count_word_frequency()
