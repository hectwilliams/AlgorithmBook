
def interleave_arrays(arr1, arr2):
    pos1 = 0
    pos2 = 0
    array = []

    while arr1 or arr2:

        if arr1:
            array.append(arr1.pop(0))

        if arr2:
            array.append(arr2.pop(0))
    return array 

a = [77,22,11,22] 
b = [2,6,7,2,6,2]

print( 'interleaved {}'.format( interleave_arrays(a, b) ) )

def merge_sorted_arrays(arr1, arr2):
    result = []

    while arr1 and arr2:

        if arr1[0] <= arr2[0]:
            result.append(arr1.pop(0))
        
        elif arr2[0] <= arr1[0]:
            result.append(arr2.pop(0))

    while arr2 and not arr1:
        result.append(arr2.pop(0))
    
    while arr1 and not arr2:
        result.append(arr1.pop(0))

    return result 

a = [1,2,2,2,7] 
b = [2,2,6,6,7]

print( 'merge sorted arrays {}'.format( merge_sorted_arrays (a, b) ) )

def minimal_three_way (arr1, arr2, arr3):
    class sort_node:
        def __init__(self, a = [], b =[] ,c = []):
            self.path = [] 
            self.a = a + [] 
            self.b = b  + []
            self.c = c + [] 
            self.col = 0

    def clone(parent):
        c_node = sort_node()
        c_node.a = parent.a
        c_node.b = parent.b
        c_node.c = parent.c
        c_node.col = parent.col 
        return c_node 
    
    q = [ sort_node(arr1, arr2, arr3)]
    min_ = None 
    max_ = None

    while q:
        
        node = q.pop(0)

        if len(node.path) == 3:
            
            current_min = min(node.path)
            current_max = max(node.path)
            delta = current_max - current_min

            if min_ == None:
                min_ = current_min
            
            if max_ == None:
                max_ = current_max

            if delta < max_ - min_ :
                max_ = current_max 
                min_ = current_min

        else:
            arr_tmp = [
                arr1,
                arr2,
                arr3
            ][node.col]

            for ele in arr_tmp:
                new_node = clone(node)
                new_node.path += node.path  + [ele]
                new_node.col += 1 
                q.append(new_node)
                

    return {'min' : min_, 'max': max_}

a = [1,2,4,15] 
b = [3,10,12] 
c = [5,10,13,17,23]

print('minimal_three_way {}'.format(minimal_three_way(a, b, c)))

def intersect_sort_array(arr1, arr2):
    pos1 = 0
    pos2 = 0
    result = [] 

    while pos1 < len(arr1) and pos2 < len(arr2):
        
        if arr1[pos1] != arr2[pos2]:
            
            if arr1[pos1] < arr2[pos2]:
                pos1 += 1

            elif arr2[pos2] < arr1[pos1]:
                pos2 += 1

        else:
            result += [ arr2 [ pos2] ] 
            pos1 += 1
            pos2 += 1

    return result 

def intersect_sort_array_dedupe(arr1, arr2):
    pos1 = 0
    pos2 = 0
    result = []

    while pos1 < len(arr1) and pos2 < len(arr2):
        
        if arr1[pos1] != arr2[pos2]:
            
            if arr1[pos1] < arr2[pos2]:
                pos1 += 1

            elif arr2[pos2] < arr1[pos1]:
                pos2 += 1

        else:
            if arr2[pos2] not in result:
                result += [ arr2 [ pos2] ] 
            pos1 += 1
            pos2 += 1

    return result 

a  = [ 1, 2 , 2, 2, 7 ]
b =  [ 2, 2 , 6 ,6, 7 ]
print('interesect_sort_array {} '.format(intersect_sort_array_dedupe(a, b)))


def union_sorted_array(arr1, arr2):
    pos1 = 0
    pos2 = 0
    result = []

    while pos1 < len(arr1) and pos2 < len(arr2):
    
        if arr1[pos1] != arr2[pos2]:
        
            if arr1[pos1] < arr2[pos2]:
                result += [ arr1 [ pos1] ] 
                pos1 += 1

            elif arr2[pos2] < arr1[pos1]:
                result += [ arr2 [ pos2] ] 
                pos2 += 1

        else:
            result += [ arr2 [ pos2] ] 
            pos1 += 1
            pos2 += 1

    return result 
print('interesect_sort_array {} '.format(union_sorted_array(a, b)))


def union_sorted_array_dedupe(arr1, arr2):
    pos1 = 0
    pos2 = 0
    result = []

    while pos1 < len(arr1) and pos2 < len(arr2):
    
        if arr1[pos1] != arr2[pos2]:
        
            if arr1[pos1] < arr2[pos2]:
                if arr1[pos1] not in result:
                    result += [ arr1 [ pos1] ] 
                pos1 += 1

            elif arr2[pos2] < arr1[pos1]:
                if arr2[pos2] not in result:
                    result += [ arr2 [ pos2] ] 
                pos2 += 1

        else:
            if arr2[pos2] not in result:
                result += [ arr2 [ pos2] ] 
            pos1 += 1
            pos2 += 1

    return result 
print('interesect_sort_array {} '.format(union_sorted_array_dedupe(a, b)))

def intersection_inplace(arr1, arr2):
    start = 0
    result = []
    for ele in arr2:

        for i in range(start, len(arr1)):
            if arr1[i] == ele:
                arr1[i], arr1[start] = arr1[start], arr1[i]
                result.append(ele)
                start += 1
                break
    return result 

a = [2,7,2,1,2] 
b = [6,7,2,7,6,2]
print('intersection_inplace {} '.format(intersection_inplace(a, b)))

def union_unsorted_array(arr1, arr2 ):
    pass 

a = [2,7,2,1,2] 
b = [6,7,2,7,6,2]
print(''.format(  union_unsorted_array(a, b) ))

class heap:
    
    def __init__(self):
        self.array = []

    def is_empty(self):
        return len(self.array) == 0

    def size(self):
        return len(self.array) 
    
    def top(self):
        if len(self.array) == 0:
            return None 
        return self.array[0]
    
    
    def contains(self, value):
        return value in self.array
    
    def insert(self, value):
        self.array.append(value)

        node_count = len(self.array) // 2

        for i in range(node_count, -1, -1):

            # child left 
            if 2*i + 1 < len(self.array):
                parent = self.array[i]
                child_left = self.array[ 2*i + 1]
                if child_left < parent:
                    self.array[2*i + 1], self.array[i] = self.array[i], self.array[2*i + 1]
            
            # child right 
            if 2*i + 2 < len(self.array):
                parent = self.array[i]
                child_right = self.array[2*i + 2]
                if child_right < parent:
                    self.array[2*i + 2], self.array[i] = self.array[i], self.array[2*i + 2]
            
    # swap and demote 
    def extract(self): 
        value = None 

        # swap first and last value 
        if len(self.array) == 0:
            return value
        
        self.array[0], self.array[ len(self.array) - 1 ] = self.array[ len(self.array) - 1 ], self.array[0]
    
        value = self.array.pop()

        # demote root  value 
        for i in range(len(self.array)):
            child_left_index = 2*i + 1
            child_right_index = 2*i + 2

            if child_left_index < len(self.array):
                if self.array[child_left_index] < self.array[i]:
                    self.array[child_left_index], self.array[i] = self.array[i], self.array[child_left_index]
            
            if child_right_index < len(self.array):
                if self.array[child_right_index] < self.array[i]:
                    self.array[child_right_index], self.array[i] = self.array[i], self.array[child_right_index]

        return value

    def heapify(self, arr):


        node_count = len(arr) // 2
        
        for node_exlcude_length  in range(node_count-1 ):

            for node_index in range(node_count - 1 , -1 + node_exlcude_length, -1): 
                child_left_index = 2*node_index + 1
                child_right_index = 2*node_index + 2


                if child_left_index < len(arr):
                    if arr[child_left_index] < arr[node_index]:
                        arr[child_left_index], arr[node_index] = arr[node_index], arr[child_left_index]
        
                if child_right_index < len(arr):
                    if arr[child_right_index] < arr[node_index]:
                        arr[child_right_index], arr[node_index] = arr[node_index], arr[child_right_index]

        return arr


heap_inst = heap()
heap_inst.insert(44)
heap_inst.insert(100)
heap_inst.insert(2)
heap_inst.insert(0)
print(heap_inst.extract())
print(heap_inst.extract())
print(heap_inst.extract())
print(heap_inst.extract())
print(heap_inst.extract())

print(heap_inst.array)


arr = [77, 15,91,21,6,46]
print(heap_inst.heapify(arr))

arr = [77, 15,91,21,6,46]
print(heap_inst.heapify(arr))



def heap_sort_descending(arr):

    size = len(arr)

    for current_tail_node_index in range(size - 1, 0, -1):

        node_count = current_tail_node_index // 2 

        for i in range(node_count , -1, -1):
            c_left = 2*i  + 1
            c_right= 2*i + 2 

            if c_left <= (current_tail_node_index):
                if arr[c_left] < arr[i]:
                    arr[c_left], arr[i] = arr[i], arr[c_left] 

            if c_right <= (current_tail_node_index):
                if arr[c_right] < arr[i]:
                    arr[c_right], arr[i] = arr[i], arr[c_right] 

        arr[0], arr[current_tail_node_index] = arr[current_tail_node_index], arr[0]

    return arr
        # swap to move mid


def heap_sort_asscending(arr):

    size = len(arr)

    for current_tail_node_index in range(size - 1, 0, -1):

        node_count = current_tail_node_index // 2 

        for i in range(node_count , -1, -1):
            c_left = 2*i  + 1
            c_right= 2*i + 2 

            if c_left <= (current_tail_node_index):
                if arr[c_left] >arr[i]:
                    arr[c_left], arr[i] = arr[i], arr[c_left] 

            if c_right <= (current_tail_node_index):
                if arr[c_right] > arr[i]:
                    arr[c_right], arr[i] = arr[i], arr[c_right] 

        arr[0], arr[current_tail_node_index] = arr[current_tail_node_index], arr[0]

    return arr
        # swap to move mid
arr = [77, 15,91,21,6,46]
print( heap_sort_asscending(arr) )