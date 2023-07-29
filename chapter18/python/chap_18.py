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
        def __init__(self, words, possible_words = []):
            self.ordered = False 
            self.index = 0
            self.data_bucket = []
            self.list = []

            if not possible_words:

                # A-Z 
                chars = [] 
                for num in range(65, 90):
                    chars.append(  chr(num) )
                
                # possible chars
                for i in range(len(arr)):
                    self.data_bucket.append( chars + [] )

            else :
                 
                 for possible_word in possible_words:
                     self.data_bucket.append( possible_word + [] )

            for word in words:
                self.list.append( word + [] )


    queue = [word_node(arr + [])]

    while queue:
        
        node = queue.pop(0)

        for i in range( len(node.list) ):
            
            word = node.list[i]

            c = node.list[i][node.index]

            if c == '?':
                
                node.list[i] = node.list[i][0: node.index] + node.data_bucket[i].pop(0) + node.list[i][node.index + 1 : :] 
                # insert current node back to stack
                queue.insert(0, node)

                # new node
                new_node = word_node( node.list, node.data_bucket )
                new_node.index = node.index + 1 
                if not new_node.ordered:

                    pass
                queue.insert(0, new_node)

                return 

            
arr = ["XD?E","BDE?","?A?E"]
reorder_word_fragnents (arr)


