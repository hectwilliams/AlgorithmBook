def selection_sort(arr):
    min_index = 0
    walk = 0

    for col in range(len(arr)):
        min_index = col
        for k in range(col, len(arr)):
            if arr[k] < arr[min_index]:
                min_index = k 
        
        if min_index !=  col:
            arr[col], arr[min_index] = arr[min_index], arr[col] 

arr = [9, 2, 5, 1, 8]
print('{} {}'.format( selection_sort(arr) , arr) )

class multi_key_obj:
    def __init__(self, a, b):
        self.firstname = a
        self.lastname = b 

def multikey_sort(arr_obj):
    def bubble_sort(arr):
        
        for level in range(2):

            if level == 1:
                for i in range( len(arr_obj) - 1 ):
                    for j in range( 1, len(arr_obj) ):
                        
                        if level == 1:
                            if arr[i].firstname > arr[j].firstname:
                                arr[i].firstname , arr[j].firstname = arr[j].firstname, arr[i].firstname

                        if level == 2:
                            if arr[i].lastname > arr[j].lastname:
                                arr[i].lastname , arr[j].lastname = arr[j].lastname, arr[i].lastname
    bubble_sort(arr)

arr = [
    multi_key_obj('Giorgio', 'Carnevale'),
    multi_key_obj('Aaron', 'Carnevale'),
    multi_key_obj('Hector', 'Carnevale'),
    multi_key_obj('Aector', 'Caanevale')

]
print('multikey_sort {}'.format(multikey_sort(arr)))
print(  list(map( lambda node: (node.firstname, node.lastname),  arr))  )


def insertion_sort(arr):
    for i in range( 1, len(arr) ):
        for k in range( 0, i ):
            if ( arr[i] < arr[k] ):
                arr[i], arr[k] = arr[k] , arr[i]

arr = [9, 2, 5, 1, 8]
print('insertion_sort {}  {}'.format(insertion_sort(arr), arr ) )


def combineArrs(arr1, arr2):
    pos2 = 0
    pos1 = 0

    arr1 = arr1 + [] 
    arr2 = arr2 + []

    # 
    while pos1 < len(arr1) and pos2 < len(arr2):
        if arr2[pos2] < arr1[pos1]:
            arr2[pos2] , arr1[pos1] = arr1[pos1], arr2[pos2]
            pos2 += 1
        elif arr2[pos2] >= arr1[pos1]:
            pos1 += 1

    # dump aar2
    while arr2 :
        arr1.append(arr2.pop(0))

    return arr1
    
arr1 = [2, 5, 6] 
arr2 = [4, 5, 9]
print( 'combineArrs {} '.format(combineArrs(arr1, arr2)) )

def partition(arr):
    value_mid = arr[0]
    step = 1 # increment only if swap occurs 

    for k in range(1, len(arr)):   
        if arr[k] < value_mid:
            arr[k], arr[step] = arr[step], arr[k]
            step += 1
    
    if step > 0: 
        arr[0], arr[step - 1] = arr[step - 1], arr[0]
        
    return step - 1

arr = [27, 38, 12, 39,27,16]
arr = [5,4,9,2,5,3]
print( 'partition {}  {} '.format(partition(arr) , arr)  )

def merge_sort (arr):

    # divide 
    if len(arr) < 2:
        return arr
    else:
        if len(arr) % 2 == 1:
            half = (len(arr) // 2 ) + 1
        else :
            half = len(arr) // 2

        left = arr[ 0 : half ]
        right = arr[ half  : : ]
 
        left_ret = merge_sort(left) + [] 
        right_ret = merge_sort(right) + []
        
        print('Array', left_ret, right_ret)
        # order matters here 
        if  left_ret[0] <= right_ret[0]:
            return combineArrs(left_ret, right_ret)
        else :
            print('Array', right_ret, left_ret)
            return combineArrs(right_ret, left_ret)

arr = [15,4,9,2,5,3]
print( 'merge_sort {} '.format(merge_sort(arr)) )

def quick_sort(arr):

    if len(arr)  < 2:
        return arr
    
    i = partition(arr)
    
    return quick_sort(arr[0 :i])  + [arr[i]] + quick_sort(arr[i + 1 : : ])

arr = [15,4,9,2,5,3]
print( 'quick sort {} '.format(quick_sort(arr)) )
