# Octal System

def dec2_to_oct_str(value):
    res_string = ""
    RADIX = 8 
    is_negative = value < 0

    value = abs(value)
    octals_count = 0

    # find exponent count ( highest power required )
    while RADIX ** octals_count < value:
        octals_count += 1
    
    if octals_count == 0:
         return ""
    
    while value:
        
        octals_count -= 1

        factor = value  //  RADIX ** octals_count

        value  = value - (factor * RADIX ** octals_count)    # i.e. -> factor * 8**Exponent 

        res_string  = res_string  + str(factor) 

    return '{}0o{}'.format( '-' if is_negative else '',  res_string)  

num = 31 
print(' {} '.format( dec2_to_oct_str(num) ))


def oct_str_to_value(str_number : str):
    value = 0
    index = 0
    RADIX = 8
    
    if str_number.find('0o') == 0:
        str_number = str_number[2 : :]

    str_size = len(str_number)

    for exp in range( str_size - 1, -1 , -1):
        value += int(str_number[index]) * RADIX ** exp
        index += 1
    return value 

octal_str = '0o4213' 
print(' {} '.format( oct_str_to_value(octal_str) ))

def dec2_hex_str(value):
    res_string = ""
    RADIX = 16
    is_negative = value < 0

    value = abs(value)
    octals_count = 0

    # find exponent count ( highest power required )
    while RADIX ** octals_count < value:
        octals_count += 1
    
    if octals_count == 0:
         return ""
    
    while value:
        
        octals_count -= 1

        factor = value  //  RADIX ** octals_count

        value  = value - (factor * RADIX ** octals_count)    # i.e. -> factor * 8**Exponent 

        res_string  = res_string  + str(factor) 

    return '{}Ox{}'.format( '-' if is_negative else '',  res_string) 

num = 0x47 
print(' {} '.format( dec2_hex_str(num) ))


def hex_str_to_value(str_number : str):
    value = 0
    ch_index = 0
    RADIX = 16
    
    if str_number.find('0x') == 0:
        str_number = str_number[2 : :]

    str_size = len(str_number)

    for exp in range( str_size - 1, -1 , -1):
        c = str_number[ch_index]

        if c == 'A':
            c = '10'
        if c == 'B':
            c = '11'
        if c == 'C':
            c = '12'
        if c == 'D':
            c = '13'
        if c == 'E':
            c = '14'
        if c == 'F':
            c = '15'

        value += int(c) * RADIX ** exp
        ch_index += 1

    return value 

octal_str = '0x1D2' 
print(' {} '.format( hex_str_to_value(octal_str) ) )


def dec2_bin_str(value):
    res_string = ""
    RADIX = 2
    is_negative = value < 0

    value = abs(value)
    octals_count = 0

    # find exponent count ( highest power required )
    while RADIX ** octals_count < value:
        octals_count += 1
    
    if octals_count == 0:
         return ""
    
    while value:
        
        octals_count -= 1

        factor = value  //  RADIX ** octals_count

        value  = value - (factor * RADIX ** octals_count)    # i.e. -> factor * 8**Exponent 

        res_string  = res_string  + str(factor) 

    return '{}0b{}'.format( '-' if is_negative else '',  res_string) 

num = 35
print(' {} '.format( dec2_bin_str(num) ))


def bin_str_to_value(str_number : str):
    value = 0
    ch_index = 0
    RADIX = 2
    
    if str_number.find('0b') == 0:
        str_number = str_number[2 : :]

    str_size = len(str_number)

    for exp in range( str_size - 1, -1 , -1):
        c = str_number[ch_index]
        value += int(c) * RADIX ** exp
        ch_index += 1

    return value 

binary_str = '0b1010101' 
print(' {} '.format( bin_str_to_value(binary_str) ) )


def reorder_word_fragnents (arr) :
    class word_node:
        def __init__(self, data, arr_index = 0, word_index = 0 , ordered = False  ):
            self.ordered = ordered 
            self.index = word_index
            self.list = []
            self.CHARS = []
            self.arr_index = arr_index
            self.kill = False 

            # A-Z 
            for num in range(65, 90):
                self.CHARS.append(  chr(num) )
            
            
            if type(data[0]) == str  :
                
                for i in range(len(data)):
                    self.list.append(   []  )
                    self.list[i].append( data[i]  )
                    self.list[i].append( self.CHARS + []  )

            else:

                for i in range(len( data)):
                    self.list.append(  [  data[i][0]  , data[i][1] + [] ]  )

    queue = [ word_node(arr + []) ]

    while queue:
        
        node = queue.pop(0)

        # step to next array element
        if node.arr_index == len(node.list) :
            node.arr_index = 0
            # step to next work element 
            node.index += 1
            # print('DEBUG: NEW POS', node.index, node.arr_index)
        

        # clone node 
        new_node = word_node( node.list,  node.arr_index, node.index, node.ordered)

        if node.index == len( node.list[0][0]) :
            return list ( map( lambda arr_ele: arr_ele[0] , node.list ) )
        
        else:
            
       
                    
            wild_card_char = None 

                
            c = node.list[ node.arr_index ][0][node.index] # 0 index is string

            if c == '?':

                wild_card_char = node.list[node.arr_index][1].pop(0) # 1 index is array of possible characters 

                # insert current node back to stack 
                queue.append(node)
                
                new_node.list[new_node.arr_index][0] = new_node.list[node.arr_index][0][0: new_node.index] + wild_card_char + new_node.list[new_node.arr_index][0][new_node.index + 1 : :] 
                

            valid_chars = True 

            for arr_ele in new_node.list:
                test_word = arr_ele[0]
                test_char  = test_word[new_node.index] # 0 index is string
                valid_chars = valid_chars and ( test_char != '?'  )

            if valid_chars :
                    
                # more than one sort is an invalid construct or path 

                    # unsorted_arr 
                    unsorted_arr = ""
                    for arr_ele in new_node.list:
                        unsorted_arr += arr_ele[0]

                    new_node.list.sort( key= lambda arr_ele: arr_ele[0][new_node.index] ) # 0 index is string

                    # sorted_arr  
                    sorted_arr = ""
                    for arr_ele in new_node.list:
                        sorted_arr += arr_ele[0]

                    if sorted_arr == unsorted_arr:
                        new_node.ordered = True 
                        # print('SORTED HERE', new_node.list,  'col', new_node.index, 'arr', new_node.arr_index,)

                    if sorted_arr != unsorted_arr:
                        if new_node.ordered == False:
                            new_node.ordered = True 
                            # print('SORTED HERE', new_node.list,  'col', new_node.index, 'arr', new_node.arr_index,)
                        else :
                            # sorted 
                            new_node.kill = True 
                            # print('JUMP OR PATH ERROR')

            if new_node.kill:
                continue



            new_node.arr_index = node.arr_index + 1
            
            queue.insert(0, new_node)

print('** REORDER FRAGMENTS SOL')           
            
arr1 = ["XD?E","BDE?","?A?E"]
arr2 = ["BQX?","XD?E"]
print(reorder_word_fragnents (arr1) )
print(reorder_word_fragnents (arr2) )
print('** REORDER FRAGMENTS SOL END ')           


