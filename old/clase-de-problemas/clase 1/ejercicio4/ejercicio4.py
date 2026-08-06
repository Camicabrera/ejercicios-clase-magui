# Count Word Frequency in a Sentence
def count_word_frequency(sentence):
    """
    Counts the frequency of each word in a given sentence.
    
    :param sentence: str - The sentence to analyze
    :return: dict - A dictionary with words as keys and their frequencies as values
    """
    # Implement the algorithm to count word frequencies here
    bandera1 = 0
    dicc = {}
    for num in range(len(sentence)):
        if sentence[num] == " " :
            if sentence[bandera1:num] in dicc:
                dicc[sentence[bandera1:num]] += 1
                bandera1 = num + 1
            else: 
                dicc[sentence[bandera1:num]] = 1
                bandera1 = num + 1
        elif num == len(sentence) - 1:
            if sentence[bandera1:num + 1] in dicc:
                dicc[sentence[bandera1:num + 1]] += 1
            else: 
                dicc[sentence[bandera1:num + 1]] = 1
    return dicc
               
 
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
