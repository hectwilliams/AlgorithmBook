# without built in attire 
import math 

import string 

def string_to_word_array(msg):

    def next_word(space_index):
        word = ''
        walk_index = None 

        while msg[space_index] == ' ':
            space_index += 1
        
        walk_index = space_index 

        while  msg[walk_index] != ' ' :
                word += msg[walk_index]
                walk_index += 1
                if walk_index == len(msg):
                     return word 

        return word 
    
    space_positions = [0]
    for i, c in enumerate(msg):
        if c == ' ':
            space_positions += [i] 
    return list(map(next_word, space_positions))
    

    

msg = "Life is not a drill!"
print('{}'.format(string_to_word_array(msg)))

def longest_word(msg):
    class word_node:
        def __init__(self, index = 0):
            self.word = ''
            self.start_pos = index
            self.prev = [] 
            self.pos = index
            self.char_found = False

    def valid_step(new_node):
        if new_node.pos >= len(msg):
            return False 
        
        if msg[new_node.pos] != ' ':
            new_node.char_found = True 

                
        return True 
    
    def copy_node(parent):
        c_node = word_node()
        c_node.pos = parent.pos 
        c_node.start_pos = parent.start_pos 
        c_node.word = parent.word 
        c_node.prev  = parent.prev + [] 
        c_node.char_found = parent.char_found
        return c_node 
    
    def valid_node (node):
        
        print(node.word, 'DEBUG') # graph of words 

        if node.char_found :
            if node.pos == len(msg) : 
                return True  
            if msg[node.pos] == ' ' :
                return True 
        return False 
    
    word = ""
    queue = [word_node(0)]
    for i, c in enumerate(msg):
        if c == ' ':
            queue.append(word_node(i))
    
    while queue:
        node = queue.pop(0)

        if valid_node(node):
            if len(node.word) > len(word):
                word = node.word 
            continue 
        
        new_node = copy_node(node)
        if valid_step(new_node):
            new_node.word += msg[new_node.pos]
            new_node.pos += 1
            queue.append(new_node)
    return word 

msg = "Snap crackle pop makes the world go round!"
print('{}'.format(longest_word(msg)))


# Depfth first used to find values (i.e. modeled stack)
def reverse_word_order(msg):
    class word_node:
        def __init__(self, index = 0):
            self.word = ''
            self.start_pos = index
            self.prev = [] 
            self.pos = index
            self.char_found = False

    def valid_step(new_node):
        if new_node.pos >= len(msg):
            return False 
        
        if msg[new_node.pos] != ' ':
            new_node.char_found = True 

                
        return True 
    
    def copy_node(parent):
        c_node = word_node()
        c_node.pos = parent.pos 
        c_node.start_pos = parent.start_pos 
        c_node.word = parent.word 
        c_node.prev  = parent.prev + [] 
        c_node.char_found = parent.char_found
        return c_node 
    
    def valid_node (node):
        
        print(node.word, 'DEBUG') # graph of words 

        if node.char_found :
            if node.pos == len(msg) : 
                return True  
            if msg[node.pos] == ' ' :
                return True 
        return False 
    
    words = []
    stack = [word_node(0)]
    for i, c in enumerate(msg):
        if c == ' ':
            stack.append(word_node(i))
    
    while stack:
        node = stack.pop()

        if valid_node(node):
            words.append(node.word)
            continue 
        
        new_node = copy_node(node)
        if valid_step(new_node):
            new_node.word += msg[new_node.pos]
            new_node.pos += 1
            stack.append(new_node)

    return ' '.join(words )

msg = "This is a test"
print('{}'.format(reverse_word_order(msg)))







def unique_words(msg):
    class word_node:
        def __init__(self, index = 0):
            self.word = ''
            self.start_pos = index
            self.prev = [] 
            self.pos = index
            self.char_found = False

    def valid_step(new_node):
        if new_node.pos >= len(msg):
            return False 
        
        if msg[new_node.pos] != ' ':
            new_node.char_found = True 

                
        return True 
    
    def copy_node(parent):
        c_node = word_node()
        c_node.pos = parent.pos 
        c_node.start_pos = parent.start_pos 
        c_node.word = parent.word 
        c_node.prev  = parent.prev + [] 
        c_node.char_found = parent.char_found
        return c_node 
    
    def valid_node (node):
        
        if node.char_found :
            if node.pos == len(msg) : 
                return True  
            if msg[node.pos] == ' ' :
                return True 
        return False 
    
    def is_unique_node(nodes, test_node):
        for node in nodes:
            if test_node.word == node.word:
                return False 
        return True 
    
    def bubble_sort (node_words):
        for i in range(0, len(node_words) - 1):
            for j in range ( i + 1,  len(node_words) ):
                if node_words[j].start_pos < node_words[i].start_pos :
                    node_words[i], node_words[j] = node_words[j], node_words[i]
        return node_words



    node_words = []
    queue = [word_node(0)]

    walk = 0
    while walk < len(msg):
        walk += 1
        if msg[walk - 1] == ' ':
            queue.append(word_node(walk))
    
    while queue:
        node = queue.pop(0)

        if valid_node(node): # valid word found 
            if is_unique_node(node_words, node ): # must be unique word 
                node_words.append(node)
            continue 
        
        new_node = copy_node(node)
        if valid_step(new_node) : 
            new_node.word += msg[new_node.pos]
            new_node.pos += 1
            queue.append(new_node)
    
    return ' '.join(
                list
                    (
                        map( lambda node_: node_.word,  bubble_sort(node_words))
                    )
                )
    

msg = "Sing! Sing a song; sing out loud; sing out strong."
print('{}'.format(unique_words(msg)))

def string_rotate(string, count):
    res = string 
    for _ in range(count):
        res = ""
        for k in range(len(string) -1 ):
            res += string[k]
        res = string[-1] + res 
        string = res 
    return res 

print('{}'.format(string_rotate("Boris Godunov",5)))

def ionis_rotat(str1,str2):
    for i in range(len(str2)):
        if str1 == string_rotate(str2, i):
            return True 
    return False 

str1 = "hello"
str2 = "llohe"
print('{}'.format(ionis_rotat(str1, str2)))


def genetic_marker(string_list, string):
    class string_node:
        def __init__(self):
            self.word = "" 
            self.pos = 0

    def copy_node(parent):
        c_copy = string_node()
        c_copy.word = parent.word 
        c_copy.pos = parent.pos 
        return c_copy
    
    def valid_step(node):
        if node.pos >= len(node.word):
            return False 
        return True 

    for test_string in string_list:

        queue = []
        queue.append(string_node()) 

        while queue:

            node = queue.pop(0) 
            
            if node.word == string:
                return True 

            if len(node.word) == len(test_string):
                continue 
            
            if test_string[node.pos] == '?':
                for c in ( chr(i) for i in range(32, 127)):
                    new_node = copy_node(node)
                    new_node.word += c
                    new_node.pos += 1
                    if valid_step(new_node):
                        queue.append(new_node)
            else:
                node.word += test_string[node.pos]
                node.pos += 1 
                queue.append(node)

    return False 


list_ = [
    "time",
    "el?",
    "yey"
]

word_in_list = 'y2y'
print('{}'.format(genetic_marker(list_, word_in_list )))







def perm_arr(array):
    class perm_node:
        def __init__(self, data):
            self.arr = []
            self.array_ = data + []
    
    def clone_node(parent):
        node = perm_node(parent.array_)
        node.arr = parent.arr + [] 
        node.array_ = parent.array_ + []
        return node 
    
    queue = [perm_node(array)]
    buffer = [] 

    while queue:
        node = queue.pop(0)

        if len(node.array_) == 0:
            buffer.append(node.arr)

        for index, element in enumerate(node.array_):
            new_node = clone_node(node)
            new_node.arr += [element]
            new_node.array_ = new_node.array_[0 : index] + new_node.array_[index + 1 : : ] 
            queue.append(new_node)
    return buffer 

def optimal_sequence(arr):
    class seq_node:
        def __init__(self, arr= []): 
            self.arr = []
            self.col = 0
            self.pos = 0
            self.chars = []
            self.chars_pos = []
            self.arr_copy = []
            self.prev = [] 
            self.thrs = []

            for s in arr:
                self.arr += [""]
                self.chars_pos += [0]
                self.arr_copy += [s]

            for c in (chr(i) for i in range(65, 91) ):
                self.chars += c 

    def copy_node(parent):
        c_node = seq_node()
        c_node.col = parent.col 
        c_node.pos = parent.pos 
        c_node.arr = []
        c_node.arr_copy = []
        c_node.chars = parent.chars + []
        c_node.chars_pos = parent.chars_pos + []
        c_node.prev = parent.prev + [] 
        c_node.thrs = parent.thrs + []
        
        for arr_ele in parent.arr:
            c_node.arr += [arr_ele] 

        for arr_ele in parent.arr_copy:
            c_node.arr_copy += [arr_ele] 
        
        return c_node 
    
    def valid_char_threshold(node):
        # check char threshold 
        for c_idx in range(len(node.arr)): # col
            for i in range (len(node.arr[c_idx])): # word index
                if node.arr_copy[c_idx][i] == '?':
                    if node.arr[c_idx][i] > node.thrs[i]:
                        return False
        return True      
    
    def valid_sequence(node):
        boolean_state = None 
        for i in range(len(node.arr_copy)):
            if boolean_state == None :
                boolean_state = len(node.arr_copy[i]) == len(node.arr[i])
            boolean_state = boolean_state and (len(arr[i]) == len(node.arr[i]))
        return boolean_state
    
    def valid_update(node):
        # word boundary check 
        if len(node.arr[node.col]) > len(node.arr_copy[node.col]):
            return False 
        return True  

    def bubble_sort_seq(node):
        word_len = len(node.arr[0] ) 
        columns_count = len(node.arr)

        for word_i in range(0, word_len):
        
            for col_i in range(0, columns_count - 1 ):

                for col_j in range(1, columns_count ):

                    if node.arr[col_i][word_i] > node.arr[col_j][word_i]:

                        #swap words 
                        tmp = node.arr[col_i]
                        node.arr[col_i] = node.arr[col_j] 
                        node.arr[col_j] = tmp 

    def valid_sequence(node):
        boolean_state = None 
        for i in range(len(node.arr_copy)):
            if boolean_state == None :
                boolean_state = len(node.arr_copy[i]) == len(node.arr[i])
            boolean_state = boolean_state and (len(arr[i]) == len(node.arr[i]))
        return boolean_state
    
    def is_ordered(node):
        for word_index in range(len(node.arr[0]) ):
            for col_index in range( len(node.arr) - 1) : 
                if  node.arr[col_index + 1][word_index] < node.arr[col_index][word_index]  :
                    return False 
        return True 

    def set_threshold_init(node):
        thresholds = []

        for i in range(len(node.arr_copy[0])):
            current_threshold = None
            count_non_wildcard = 0

            for col_index in range(len(node.arr_copy) ):
                current_char = node.arr_copy[col_index][i]
                if current_threshold == None  and current_char != '?':
                    current_threshold = current_char
                
                if node.arr_copy[col_index][i] != '?':
                    if current_threshold == None :
                        current_threshold = current_char
                    if current_threshold < current_char:
                        current_threshold = current_char
                
                count_non_wildcard = count_non_wildcard + int(current_char != '?')
            
            # VERY IMPORTANT BLOCK 

            if count_non_wildcard == 1 and i == 0:    
                thresholds.append('A')
            # else:
            thresholds.append(current_threshold)

        return thresholds
        
    # find thresholds if any 
    queue = [seq_node(arr)]
    
    thrholds = set_threshold_init(queue[0])
    queue[0].thrs = thrholds

    while queue:
        
        node = queue.pop(0)

        if valid_sequence(node):
            
            if not valid_char_threshold(node):    # THIS IS VBERY IMPORTANT LINE OF LINE :) 
                continue 
                
            bubble_sort_seq(node)
            
            if is_ordered(node):
                return node.arr
            else:
                # dump previous nodes (move up the graph per say)
                while  node.prev:
                    queue.append(node.prev.pop(0))  # node.prev functions like a stack 
        else: 

            new_node = copy_node(node)

            if new_node.arr_copy[node.col][new_node.pos] == '?' :
                new_node.arr[new_node.col] +=   new_node.chars[ new_node.chars_pos[new_node.col]  ]
                
                # previous node states with updated character position
                if node.chars_pos[node.col] < len(node.chars) - 1:
                    node.chars_pos[node.col] += 1 
                    new_node.prev += [node ]
            else: 
                new_node.arr[new_node.col]  += new_node.arr_copy[new_node.col][new_node.pos]
            
            if  valid_update(new_node):
                new_node.col += 1 
                if new_node.col == len(new_node.arr_copy):
                    new_node.col = 0
                    new_node.pos += 1
                queue.append( new_node )



collection = ["EA?K","?RX?","GAG?"] 
# print('{}'.format(optimal_sequence(collection))) 
collection = ["?UD","FI?","A?E"] 
# print('{}'.format(optimal_sequence(collection)))   
# collection = ["?F??","W??S","??X?"]  # TBD
# print('{}'.format(optimal_sequence(collection))) '

def dedupe(ss):
    histo = {}
    res = ""
    
    for i in range( len(ss) - 1, -1, -1):
        c = ss[i]
        if  c not in histo :
            res = c + res 
            histo[c] = 1
    return res 
        

ss = "Snaps! crackles! pops!"
print('{}'.format(dedupe(ss)))


def index_of_first_unqiue_letter(ss):
    histo = {} 

    for i in range(len(ss)):
        c = ss[i]

        if c not in histo:
            histo[c] = [c, 1, i]
        else:
            histo[c][1] += 1
    
    for key in histo.keys():
        if histo[key][1] == 1:
            return key 
        
    return None 

ss = "empathetic monarch meets primo stinker"
print('{}'.format(index_of_first_unqiue_letter(ss)))

def unique_letters(ss):
    histo = {}
    res = ""

    for i in range(len(ss)):
        s = ss[i]
        if s not in histo:
            histo[s] = 1
        else:
            histo[s] += 1

    for i in range(len(ss)):
        s = ss[i]
        if histo[s] == 1:
            res += s

    return res     

ss = "Snap! Crackle! Poop!"
print('{}'.format(unique_letters(ss)))


def to_string(number):

    def to_str(digit):
        table = {
            0: '0',
            1: '1',
            2: '2', 
            3: '3',
            4: '4',
            5: '5', 
            6: '6',
            7: '7',
            8: '8',
            9: '9'
        }
        return table[digit]
    
    whole_number = 0
    origin_num = number 
    string = ""
    count = 0
    
    # whole number
    while number:
        digit = int(number) % 10
        print(digit)
        whole_number += digit * 10**count
        count += 1
        number //= 10
        string = to_str(digit) + string

    number = origin_num - whole_number
    
    # decimal
    if number != 0:
        string += '.'
        count = 1

        while number != 0:
            number *= 10**count
            digit = int(number % 10)
            number -= digit 
            string = string + to_str(digit)
        
    return string

num = 1234.2
print('{}'.format(to_string(num)))

'''
 621 6 hundred twenty one 

 trillion| billion| |million| tounsand| |
'''
def num_to_text(num):
    
    def decode_matrix_helper(arr, index):

        prefix_table = {
            0: "",
            1: " thousand",
            2: " million",
            3 : " trillion"
        }

        ones_table = {
            '9': 'nine',
            '8': 'eight',
            '7': 'seven',
            '6': 'six',
            '5': 'five',
            '4': 'four',
            '3': 'three',
            '2': 'two',
            '1': 'one',
            '0': 'zero'
        }

        hundredth_table = {
            '9': 'ninety',
            '8': 'eighty',
            '7': 'seventy',
            '6': 'sixety',
            '5': 'fifty',
            '4': 'fourty', 
            '3': 'thirty',
            '2': 'twenty',
            '1': {
                # 
                'zero': 'ten',
                'one': 'eleven',
                'two': 'twelve',
                'three': 'thirteen',
                'four': 'fourteen',
                'five': 'fifteen',
                'six': 'sixteen',
                'seven': 'seventeen',
                'eight': 'eighteen',
                'nine': 'nineteen',
            },

            '0': ""
        }
        
        current_string = ""

        for i in range(len(arr) - 1, -1 , -1):

            value = arr[i]

            if i == 2:
                current_string =  ones_table[value]
        
            if i == 1:
            
                if value != None:
                    table_value = hundredth_table[value]

                    if type (table_value) == str :
                        current_string = '{} {}'.format(table_value, current_string).strip()
                    elif type(table_value) == dict :
                        current_string = '{}'.format(table_value [current_string] )
            
            if i == 0:
                if value == None:
                    current_string += "" 
                table_value = ones_table[value]

                if table_value == 'zero':
                    current_string += ""
                else :
                    current_string = '{} {} {}'.format( table_value,"hundred", current_string)
        
        return    current_string  + prefix_table[index ] 
    
    whole_str = str(num)
    decimal_str = ""
    if whole_str.find('.') != -1 :
       whole_str, decimal_str = whole_str.split('.')

    table = [] 
    row_count = 0
    col_count = 0
    index = len(whole_str) - 1
    l = math.floor(len(whole_str) / 3)  # .  |hundreths  | tenths| ones|

    # allocate table memory 
    for _ in range(l):
        table.append( [] )
    print(table, len(table))

    # load table 
    while index > -1 :

        table[row_count].append( whole_str[index]   )
        
        col_count += 1
        index -= 1
        if col_count == 3:
            col_count == 0
            row_count = ( row_count + 1)  %3

    s_whole = ""
    
    for i, row_data  in enumerate(table):
        s_whole = decode_matrix_helper(row_data, i) + " " + s_whole

    s_dec = "point "
    for c in decimal_str:
        s_dec  += decode_matrix_helper( ['0','0',c], 0) + " "
    
    return s_whole + "" + s_dec


number = 222111.2051
print('{}'.format( num_to_text(number)) )