
class Item () :
    def __init__(self, v, w):
        self.v = v
        self.w = w

items = [Item(1,5),Item(2,3), Item(4,5), Item(2,3), Item(5,2)]

def max_value(items, weight_accum = 5, value_accum = 0):
    elements = []
    if(weight_accum == 0):
        return value_accum
    if(weight_accum < 0):
        return 0

    for item in range (len(items)): 
        items_copy = items.copy()
        element = items_copy.pop(item)
        elements.append(max_value(items_copy, weight_accum - element.w, value_accum + element.v))
    
    return max (elements) 

print(max_value(items))