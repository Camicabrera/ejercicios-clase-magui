def es_heap(arr):
    n = len(arr)

    for i in range(n // 2 - 1, -1, -1):
        if not es_nodo_heap(arr, i):
            return False
    return True

def es_nodo_heap(arr, i):
    n = len(arr)
    izquierda = 2 * i + 1
    derecha = 2 * i + 2

    if izquierda < n:
        if arr[i] < arr[izquierda]:
            return False

    if derecha < n:
        if arr[i] < arr[derecha]:
            return False

    return True

def test(arr, expected, actual): 
    print("Testing array: ", arr)
    if(expected != actual):
        print('TEST FAILED')
    else: 
        print('TEST PASSED')

arr1 = [90, 15, 10, 7, 12, 2, 7]
test(arr1, True, es_heap(arr1))

arr2 = [9, 15, 10, 7, 12, 2, 7]
test(arr2, False, es_heap(arr2))

arr3 = [90, 15, 10, 7, 120, 2, 7]
test(arr3, False, es_heap(arr3))