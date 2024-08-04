def sort_string_array(arr):
    n = len(arr)
    for i in range(n):
        for j in range(0, n-i-1):
            if arr[j] > arr[j+1]:
                # Swap if the element found is greater
                arr[j], arr[j+1] = arr[j+1], arr[j]

# Test Cases
def test_sort_string_array():
    test_cases = [
        (["pear", "apple", "banana"], ["apple", "banana", "pear"]),
        (["fox", "cat", "elephant", "dolphin"], ["cat", "dolphin", "elephant", "fox"]),
        (["python", "java", "c++", "ruby"], ["c++", "java", "python", "ruby"]),
        (["sun", "moon", "star"], ["moon", "star", "sun"]),
        (["a", "b", "c"], ["a", "b", "c"]),
        ([], []),
        (["one"], ["one"]),
        (["ccc", "aaa", "bbb"], ["aaa", "bbb", "ccc"]),
    ]
    
    for i, (input_array, expected) in enumerate(test_cases):
        sort_string_array(input_array)
        assert input_array == expected, f"FAILED on case {i + 1}: expected {expected}, but got {input_array}"
    print("All tests PASSED.")

# Run Tests
if __name__ == "__main__":
    test_sort_string_array()
