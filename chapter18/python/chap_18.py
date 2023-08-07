# Octal System

def dec2_to_oct_str(value):
    res_string = ""
    RADIX = 8 
    is_negative = value < 0

    value = abs(value)
    
    while value :
        
        factor = value % RADIX

        value =  value // RADIX

        res_string  = str(factor)  +  res_string  

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

octal_str = '0o4210' 
print(' oct to string  {} '.format( oct_str_to_value(octal_str) ))

def dec2_hex_str(value):
    res_string = ""
    RADIX = 16
    is_negative = value < 0

    value = abs(value)
    
    while value :
        
        factor = value % RADIX

        if factor == 15:
            factor = 'F'
        
        elif factor == 14:
            factor = 'E'
        
        elif factor == 13:
            factor = 'D'
        
        elif factor == 12:
            factor = 'C'
        
        elif factor == 11:
            factor = 'B'
        
        elif factor == 10:
            factor = 'A'


        value =  value // RADIX

        res_string  = str(factor)  +  res_string  

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

    while value :
        
        factor = value % RADIX

        value =  value // RADIX

        res_string  = str(factor)  +  res_string  

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


def count_in_binary(number):
    count = 0

    while number:

        count += 1

        number = number >> 1

    return count 

num = 100
print(' {} {} '.format( count_in_binary(100) , 1 ))

def count_set_bits (number):
    count = 0
    
    while number :

        count += int (number % 2 ==1)

        number = number >> 1
    return count 

num = 1023
print('count_set bits {}'.format( count_set_bits(num) ))   

def count_set_bits_opt(number):

    map_to_4_bit = [
        0,  #0b_0000
        1,  #0b_0001
        1,
        2,
        1,
        2,
        2,
        3,
        1,
        2,
        2,
        3,
        2,
        3,
        3,
        4, # 0b_1111
    ]

    count = 0 

    stride = 0XF

    while number:
        count += map_to_4_bit [stride & number ]
        number = number >> 4
    
    return count 

num = 1023
print(' {} '.format(count_set_bits_opt(num)))

def reverse_bits (number, bit_width = 32):
    result = 0 

    for i in range(bit_width - 1, -1, -1):
        result += pow(2, i) * int (number % 2 == 1) 
        number = number  >> 1 # right shift 
    return result 

input_  = 0b01100110011001101111000011110000
expect = 0b00001111000011110110011001100110
result = reverse_bits(input_)
print(' input {}  -- output == expect {} '.format( input_, result == expect  ) )

def encode_bytes_to_32 (array):
    result = 0
    byte_size = 8 

    for i in range(len(array)):
        value = array[i] 
        byte_index = len(array) - 1  - i 
        result  =  result | (value <<  byte_index * byte_size )  # | (or)
    return result 

expect = 0xF0C39659
arr =  [0xF0, 0xC3, 0x96, 0x59]
res = encode_bytes_to_32(arr)
print(' {}   {}'.format(  res, expect == res ) )

def decode_32_to_bytes (hex_number):
    byte_index = 3 
    arr = [] 
    byte_size = 8 

    while byte_index >= 0:
        byte_data = hex_number & ( 0xFF << byte_index * byte_size ) 
        byte_data = byte_data >> byte_index * byte_size    # shift down 
        arr.append( byte_data  )
        byte_index -= 1 
    return arr 

data = 306542763 # 0x124578AB
test = decode_32_to_bytes (data)

print(' {}  '.format(  test) )

# solution 
# Ox12
# Ox45
# Ox78
# OxAB
#  [18, 69, 120, 171]  

def encode_bit_num (bit_val, bit_number, val_32_bit) :

    curr_bit = (val_32_bit & (1 << bit_number)) >> bit_number

    if bit_val != curr_bit:
        if bit_val == 0 :
            bits = ~ ( 1 << bit_number )  # 11101111111
            val_32_bit &= bits   
        else :
            val_32_bit |= ( 1 << bit_number )

    return val_32_bit

print( ' {} '.format( encode_bit_num(1, 22, 1) ) )
print( ' {} '.format( encode_bit_num(0, 3 , 0x18) ) )

def decode_bit_num(bit_number, val_32_bit):
    curr_bit =   ( val_32_bit & ( 1 << bit_number) ) >> bit_number 
    return curr_bit 

def radix_sort_2 (arr):
    class radix_node:
        def __init__(self, num):
            self.power_index = 0
            self.number = num

    table  = []

    for i in range(32):
        table.append([])
    
    for arr_ele in arr:
        table[0].insert( 0, arr_ele )

    for bit_num in range(32):

        buffer_head = []  # new entries to array index 

        for k in range(31,  -1 , -1) :
            
            values_arr = table[k]
            
            walk = 0
            
            while walk < len(values_arr):
                if ((values_arr[walk] & ( 1 << bit_num )) >> bit_num ) == 1:
                    buffer_head.insert(0, values_arr.pop(walk))
                else:
                    walk += 1 

        table[bit_num] = buffer_head +  table[bit_num]
    
    # reduce block 
    walk = 0
    for _ in range(1,32):
        table[0] += table.pop(1)
    
    return table[0]

arr = [2,1,3,4, 66, 12029, 100]
print(' {}  '.format(radix_sort_2(arr)))
print()

# TODO
def sprinklers():
    rcvd = input("{}\n{}\n\{}\n{}\n{}".format('RAIN_SENS- [1]', 'SENS_OVERRIDE- [2]', 'SYS_TEST- [3]', 'SYS_DISABLE- [4]', 'Enter id or ids space delimited you want enabled to alter system behavior  (ex. 1 2 ): '))
    rcvd = (''.join(rcvd)).split(' ')
    rcvd = list ( map( lambda ele: int(ele), rcvd) )
sprinklers()

