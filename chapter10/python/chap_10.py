# without built in attire 

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


