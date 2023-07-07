def sigma(number):
    if number == 1:
        return 1 
    else:
        if number <= 0:
            return number +  sigma(number + 1)    
        else:
            return number + sigma(number - 1)
num = 5
print('{}'.format(sigma(num)))

def factorial(number):
    if number == 0:
        return 1 
    return factorial(number - 1) * number 
print('{}'.format(factorial(3)))

def flood_fill(canvas2D, startxy, newcolor, table = None):
    if table == None:
        table = {}
        table['old_color'] = canvas2D [startxy[0]] [startxy[1]] 
        table['x_size'] = len(canvas2D[0]) # how many columns 
        table['y_size'] = len(canvas2D) # how many rows 

    canvas2D[startxy[0]] [startxy[1]] = newcolor

    print(startxy, 'hello')
    
    # up y 
    if startxy[0] + 1 < table['y_size']:
        if canvas2D [startxy[0] + 1 ][startxy[1]] == table['old_color']:
            flood_fill(canvas2D, [startxy[0] + 1,  startxy[1] ], newcolor, table)
    # down y
    if startxy[0] - 1 >= 0: 
        if canvas2D [startxy[0] - 1 ][startxy[1]] == table['old_color']:
            flood_fill(canvas2D, [startxy[0] - 1,  startxy[1]], newcolor, table)

#  right x 
    if startxy[1] + 1 < table['x_size'] :
        if canvas2D[startxy[0]] [startxy[1] + 1] == table['old_color']:
            flood_fill(canvas2D, [startxy[0], startxy[1] + 1], newcolor, table)
    
    if startxy[1] - 1 >= 0: 
        if canvas2D[startxy[0]] [startxy[1] - 1]  == table['old_color']:
            flood_fill(canvas2D, [startxy[0], startxy[1] - 1 ], newcolor, table)


canvas2D = [ 
 [3,2,3,4,3], 
 [2,3,3,4,0],
 [7,3,3,5,3],  
 [6,5,3,4,1],
 [1,2,3,3,3] 
]

startXY = [2,2]
print('{}'.format(flood_fill(canvas2D, startXY, 1)))
for _ in canvas2D:
    print(_)

def binary_search(numbers, target):
    mid = len(numbers) // 2 

    if len(numbers) ==0:
        return False 

    if len(numbers) % 2 ==1:
        mid + 1
    
    if numbers[mid] == target:
        return True
    elif target > mid :
        return binary_search(numbers[mid + 1: len(numbers)], target)
    else: 
        return binary_search(numbers[0: mid -1], target)

numbers = [1,3,5,6]
target = 4

print('{}'.format(binary_search(numbers, target)))

def gcf(num1, num2):

    if num1 % num2 == 0:
        return  min([num1, num2])
    if num1 > num2:
        return gcf(num1 - num2, num2)
    elif num2 > num1:
        return gcf (num1, num2 - num1)
    else:
        return num1, num2 

a = 123456
b = 987654
print('{}'.format(gcf(a,b)))

def str_subsets(str, table = []):

    if str not in  table:
        table += [str]

    if len(str) == 0:
        return 
    
    for i in range(len(str)):
        str_subsets(str[0: i] + str[i + 1: len(str)] , table)

    return  table 
string = "abc"
print('{}'.format(str_subsets(string)))

def telephone_words(str_number, data = []):
    table = { '2':'ABC', '3':'DEF', '4':'GHI', '5':'JKL', '6':'MNO', '7':'PQRS', '8':'TUV', '9':'WXYZ', '1': 'I', '0': 'O'}

    if len(str_number) == 0:
        return data
    
    current_digit = str_number[0]

    if current_digit != '-':
        
        table_value = table[current_digit]

        # for each element string in data list 
        
        #  initialize list 
        if len(data) == 0:
            for ch in table_value:
                data.append(ch)
        else:
            # pop incomplete encoded string from list 
            scan_length = len(data)
            while scan_length != 0:
                encoded_str = data.pop(0)
                scan_length -= 1
                # generate new string with char + encoded str and add to list 
                for new_encoded_char in table_value:
                    data.append(encoded_str + new_encoded_char)

    return  telephone_words( str_number[1 : len(str_number)], data)

str_number = '818-2612'
print('{}'.format(telephone_words(str_number)))

def rising_squares(number, level = 0):
    l = [] 
    r = [] 

    if number <= 0:
        return []
    
    if number == 1:
        return  [1]
    
    if level == 0 :

        if number % 2 == 0:
            r = rising_squares(number, level + 1)
            l = rising_squares(number - 1, level + 1)
        else:
            l = rising_squares(number, level + 1)
            r = rising_squares(number - 1, level + 1)     

    else :
            if number % 2 == 0:
                return  [pow(number, 2)] + rising_squares(number - 2, level + 1) 
            if number % 2 == 1:
                return  rising_squares(number - 2, level + 1) +  [pow(number, 2)]

    if level == 0:
        return l + r

number = 5
print('{}'.format(rising_squares(number)))

def anagram(string, swap_index = 0):
    data = []

    if swap_index + 1 == len(string):
        return [string]
    else:
        for i in range(swap_index, len(string)):
            split_string = list(string)
            split_string[i], split_string[swap_index]  = split_string[swap_index], split_string[i]
            new_string = ''.join(split_string)
            data += anagram(new_string, swap_index + 1)
    return data 

string = "lim"
print('{}'.format(anagram(string)))


class node:
    def __init__(self, row, col):
        self.row = row  
        self.col = col
        self.path_list = []

def google_interview(grid):
   
    def parent_node_found_invalid_path(queue_collection, row_col_tuple):
        for parent_node in queue_collection:
            # hit a parent node :( 
            if (parent_node.row, parent_node.col) == row_col_tuple:
                return True 
        return False 
    
    def new_step_is_old(current_node, row_col_tuple):
        row_col_tuple_collection = current_node.path_list 
        for row_col_tuple_via_paths in row_col_tuple_collection:
            if row_col_tuple == row_col_tuple_via_paths:
                return True 
        if (current_node.row, current_node.col) == row_col_tuple:
            return True 
        return False 
    
    def parse_paths_for_new_elec_install(grid, collection):
        table = {}

        for coord_list in collection:
            for row_col_tuple in coord_list:
                row = row_col_tuple[0]
                col = row_col_tuple[1]

                if grid[row][col] == -1:
                    table[str(row) + '_' + str(col) ] = 1
                    
        return  list(map( lambda string : string.split('_'), (table.keys() )  ))
    
    queue = []
    possible_paths = []
    max_x = len(grid[0])
    max_y = len(grid)

    # find all possible start paths ( starting paths )
    for row in range(len(grid)):
        for col in range( len(grid[0]) ):
            if grid[row][col] == 1:
                queue.append( node(row, col) )

    # queue depth first search 
    while queue:
        current_node = queue.pop(0)
        current_step_row = current_node.row
        current_step_col = current_node.col 
        new_step_node = None

        # end of path found lands on zero 
        if len(current_node.path_list) != 0:    
            tail_of_path = current_node.path_list[-1]
            current_step_row = tail_of_path[0]
            current_step_col = tail_of_path[1]
 
        # end path is invalid 
        if grid[current_step_row][current_step_col] == 0:
            # remove 0 step, went past dead end :( 
            current_node.path_list.pop() 
            # include parent path to front 
            current_node.path_list.insert( 0, (current_node.row, current_node.col) )
            possible_paths.append( current_node.path_list )
            continue
            
        # up
        if current_step_row + 1 < max_y:
            r_ = current_step_row + 1
            c_  = current_step_col
            new_row_col_tuple = (r_ ,c_ )

            if not  parent_node_found_invalid_path(queue, new_row_col_tuple ):
                # update path
                new_step_node = node(current_node.row, current_node.col)
                if not new_step_is_old(current_node , new_row_col_tuple):
                    new_step_node.path_list =  current_node.path_list + [ new_row_col_tuple ] 
                    queue.append(new_step_node)

        # down 
        if current_step_row - 1 >= 0:
            r_ = current_step_row - 1
            c_  = current_step_col
            new_row_col_tuple = (r_ ,c_ )

            if not  parent_node_found_invalid_path(queue, new_row_col_tuple ):
                # update path
                new_step_node = node(current_node.row, current_node.col)
                if not new_step_is_old(current_node , new_row_col_tuple):
                    new_step_node.path_list =  current_node.path_list + [ new_row_col_tuple ] 
                    queue.append(new_step_node)

            # left 
        if current_step_col - 1 >= 0:
            r_ = current_step_row 
            c_  = current_step_col - 1
            new_row_col_tuple = (r_ ,c_ )

            if not  parent_node_found_invalid_path(queue, new_row_col_tuple ):
                # update path
                new_step_node = node(current_node.row, current_node.col)
                if not new_step_is_old(current_node , new_row_col_tuple):
                    new_step_node.path_list =  current_node.path_list + [ new_row_col_tuple ] 
                    queue.append(new_step_node)
         # right 
        if current_step_col + 1 < max_x:
            r_ = current_step_row 
            c_  = current_step_col + 1
            new_row_col_tuple = (r_ ,c_ )

            if not  parent_node_found_invalid_path(queue, new_row_col_tuple ):
                # update path
                new_step_node = node(current_node.row, current_node.col)
                if not new_step_is_old(current_node , new_row_col_tuple):
                    new_step_node.path_list =  current_node.path_list + [ new_row_col_tuple ] 
                    queue.append(new_step_node)

    
    return parse_paths_for_new_elec_install(grid , possible_paths)
   
grid = [
    [1 , 1 ,1 , 1 , 1 , -1],
    [1 , 0 ,0 , 0 , 0 , -1],
    [1 , 0 ,-1, 0 , 0 , -1],
    [1 , 0 ,1 , 1 , 1 ,  1] ,
    [1 , 0 ,1 , 0 , 0 ,  1],
    [1 , 1 ,1 , 1 , 1 , -1]

]
print('{}'.format(google_interview(grid)))

# SOLUTION: [['2', '2'], ['2', '5'], ['0', '5'], ['1', '5'], ['5', '5']]

# '''
#                 ()
#             /        \
#          q-(           q-)        - layer 1
#         /      \        /    \
#     q-((       q-()    q-)(  q-))    - layer 2 
#       first breadth approach 
# '''


def valid_n_pair_of_parens(number):
    def valid_pairs(string):
        queue = [] 
        for c in string:
            if c == '(':
                queue.append(c)
            if c == ')':
                if len(queue) == 0:
                    return False 
                else:
                    queue.pop(0)
        return len(queue) == 0
                
    
    parens = "()"
    queue = []
    valid_list = [] 

    # initialize queue with first layer of graph 
    for c in parens:
        queue.append(c)

    while queue:    
        paren_msg_node = queue.pop(0)
    
        # new possible paths (i.e. layer) in graph
        for c in parens:
            updated_paren_msg_node = paren_msg_node + c 
            
            if len(updated_paren_msg_node) == number * 2 :
                if valid_pairs(updated_paren_msg_node):
                    valid_list.append(updated_paren_msg_node)

            if len(updated_paren_msg_node) < number * 2:
                queue.append(updated_paren_msg_node)
    return valid_list

number = 2
print('{}'.format(valid_n_pair_of_parens(number)))

class tower_node:
    def __init__(self, A = [], B = [], C =[]):
        self.count = 0
        self.A = A 
        self.B = B 
        self.C = C 
        self.count = 0
        self.prev = []   #[ [A', B', C'] , [A'', B'', C''] ]

def towers_of_hanoi():
    def valid_move(current_node, new_node):
        # check is new_node(i.e. move or event) has already occuered
        for prev_node in (current_node.prev):
            if prev_node.A == new_node.A and prev_node.B == new_node.B and prev_node.C == new_node.C:
                print('hector')
                return False 
            
        # check pole size and  disks order 
        for pole in [new_node.A, new_node.B, new_node.C]:

            if len(pole) > 6:
                return False 
            
            for i in range(len(pole) - 1):
                if pole[i] <= pole[i + 1]:
                    return False 
        
        return True 
    
    def copy_node(curr_node):
        c_node = tower_node()
        c_node.A = curr_node.A  + []
        c_node.C = curr_node.C  + []
        c_node.B = curr_node.B  + []
        c_node.prev = curr_node.prev + [] 
        c_node.count = curr_node.count 
        return c_node 
    
    # init queue 
    queue = []
    queue.append(tower_node([6,5,4,3,2,1], [], []))

    while len(queue):
        node = queue.pop(0)
        if (len(node.C)) == 6:
            print(node.count,  [node.A, node.B, node.C])
        
        # A move    
        if len(node.A):
            
            # A -> B
            c_node = copy_node(node)
            c_node.B.append(c_node.A.pop())
            if (valid_move(node, c_node)):
                c_node.count += 1
                c_node.prev.append(node)
                queue.append(c_node) 
                continue

            # A -> C 
            c_node = copy_node(node)
            c_node.C.append(c_node.A.pop())
            if (valid_move(node, c_node)):
                c_node.count += 1
                c_node.prev.append(node)
                queue.append(c_node) 
                continue

        # B move
        if len(node.B):
            # B - > C
            c_node = copy_node(node)
            c_node.C.append(c_node.B.pop())
            if (valid_move(node, c_node)):
                c_node.count += 1
                c_node.prev.append(node)
                queue.append(c_node) 
                continue

            #  B - > A 
            c_node = copy_node(node)
            c_node.A.append(c_node.B.pop())
            if (valid_move(node, c_node)):
                c_node.count += 1
                c_node.prev.append(node)
                queue.append(c_node) 
                continue

        # Cmove 
        if len(node.C):
            # C - > B
            c_node = copy_node(node)
            c_node.B.append(c_node.C.pop())
            if (valid_move(node, c_node)):
                c_node.count += 1
                c_node.prev.append(node)
                queue.append(c_node) 
                continue

            #  C - > A 
            c_node = copy_node(node)
            c_node.A.append(c_node.C.pop())
            if (valid_move(node, c_node)):
                c_node.count += 1
                c_node.prev.append(node)
                queue.append(c_node) 
                continue

print('{}'.format(towers_of_hanoi()))