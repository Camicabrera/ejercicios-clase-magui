def es_heap(arr):
    index = 0
    largo = len(arr)


    while(index < (largo-1)//2):
        hijo_izq = index * 2 + 1
        hijo_der = hijo_izq + 1
        if arr[index] < arr[hijo_izq] or arr[index] < arr[hijo_der]:
            return False
        index += 1
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