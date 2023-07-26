class TrieNode:
    def __init__(self, s= ""):
        self.s = s
        self.children = []

class Trie:
    def __init__(self):
        self.root = TrieNode("")
    
    def add(self, string):
        
        node = self.root 
        depth = 1
        
        while depth <= len(string): 

            match__child_node = None 

            # test parent 

            if node.s == string:
                return False 
            
            # evaluate children 

            for child_node in node.children:
                if child_node.s[0 : depth ] == string[0 : depth]:
                    match__child_node = child_node 

            # subtring match found 
            
            if match__child_node != None:
                
                node = match__child_node 
                
            # insert new string
            
            else:

                new_string = string[0: depth ]
               
                # print(new_string)
                new_node = TrieNode(  new_string)
                node.children.append(new_node)

                #sort array 
                node.children.sort(key= lambda node_: node_.s )
                node = new_node 
                
            depth += 1

    def contains(self, string):
        node = self.root 
        depth = 0

        while depth <= len(string):
            
            if node.s == string:
                return True 
        
            for child_node in node.children:
                if child_node.s[0 : depth] == string[0 : depth]:
                    node = child_node
                    break 
            
            depth += 1 

        return False 
    
    
    def first(self):
        
        class s_node:

            def __init__(self, trie_node_):
                self.depth = 0
                self.trie = trie_node_ 
        
        q = [s_node(self.root)]
        
        table = [] 
        
        while q:

            node = q.pop(0) 
            
            if len(table) == node.depth:
                table.append([])
            table[node.depth].append(node.trie.s)

            for c_node in node.trie.children:
                new_node = s_node(c_node)
                new_node.depth = node.depth + 1
                q.append( new_node )

        print(table[-1][0] )


    def last(self):
        
        class s_node:

            def __init__(self, trie_node_):
                self.depth = 0
                self.trie = trie_node_ 
        
        q = [s_node(self.root)]
        
        table = [] 
        
        while q:

            node = q.pop(0) 
            
            if len(table) == node.depth:
                table.append([])
            table[node.depth].append(node.trie.s)

            for c_node in node.trie.children:
                new_node = s_node(c_node)
                new_node.depth = node.depth + 1
                q.append( new_node )


        print(table[-1][-1] )
        print(table)


    def remove(self, target):
        class s_node:
            def __init__(self, parent):
                self.trie_node = parent 
                self.prev = [] 
                self.depth = 0
                self.child_removable_index = None 

        if self.root == None:
            return False 
        
        q = [s_node(self.root)]

        while q:

            node = q.pop(0)

            if node.trie_node.s == target:
                # clear queue 
                q = []  

                # pop off stack and remove element from array 
                while node.prev:

                    parent_node = node.prev.pop(0) 
                    
                    if len(parent_node.trie_node.children) == 1:
                        parent_node.children = []
                    else:
                        parent_node.trie_node.children.pop( parent_node.child_removable_index )

            else:
                # find matching substring 
                for i in range( len(node.trie_node.children) )  :
                    child_node = node.trie_node.children[i] 
                    child_str = child_node.s
                    if child_str == target[0 : node.depth + 1]:
                        new_node = s_node(child_node)
                        new_node.depth = node.depth + 1
                        node.child_removable_index = i 
                        new_node.prev +=  node.prev + [node]
                        q.append(new_node)
                        break 

    def size(self):
        count = 0 
        
        if self.root == None:
            return None 

        q = [self.root]
        
        while q:
            node = q.pop(0)
            count += bool(node)

            for c in node.children:
                q.append(c)

        return count 
    
    def next(self, target_s):
        class s_node:
            def __init__(self, parent):
                self.depth = 0
                self.trie_node = parent 

        if self.root == None:
            return None 

        q = [s_node(self.root)]

        while q:
            node = q.pop(0)

            if node.trie_node.s == target_s:
                return target_s
            else:
                
                match_child_trie_found = None 

                for child_trie_node in node.trie_node.children:
                    if target_s[0: node.depth + 1] == child_trie_node.s[0 : node.depth + 1]:
                        match_child_trie_found = child_trie_node
                
                if match_child_trie_found:
                    new_node = s_node(match_child_trie_found)
                    new_node.depth = node.depth + 1
                    q.append(new_node)
                else:
                    # no match found when comparing substrings
                    if node.trie_node.children:
                        return node.trie_node.children[0].s
                    else:
                        return node.trie_node.s 
        
    def auto_complete(self, target_s):

        class s_node:
            def __init__(self, parent):
                self.depth = 0
                self.trie_node = parent 
        
        def get_child_strings(arr_children):
            result = [] 

            q  = arr_children + [] 

            while q:
                trie_node = q.pop(0)
                result.append(trie_node.s)

                for child_trie_node in trie_node.children:
                    q.append(child_trie_node)

            return result 
        
        if self.root == None:
            return None 
        
        q= [s_node(self.root)]

        while q:
            node = q.pop(0) 

            print(node.trie_node.s)

            if node.trie_node.s == target_s:
                
                # print remaining strings
                return get_child_strings (node.trie_node.children)
            
            else:

                match_child_trie_found = None 

                for child_trie_node in node.trie_node.children:
                    if child_trie_node.s[0 : node.depth + 1] == target_s[0 : node.depth + 1]:
                        match_child_trie_found = child_trie_node 
                
                if match_child_trie_found:
                    new_node = s_node(match_child_trie_found)
                    new_node.depth = node.depth + 1
                    q.append(new_node)
                else:
                    return get_child_strings (node.trie_node.children)




trie_inst = Trie()
trie_inst.add('a')
trie_inst.add('as')
trie_inst.add('at')
trie_inst.add('ato')
trie_inst.add('atom')
trie_inst.add('atop')
trie_inst.add('are')
trie_inst.add('arf')
trie_inst.add('ARF')
print(trie_inst.contains('b'))
trie_inst.last()

print(trie_inst.root.children[0].s)

trie_inst.remove('ARF')
trie_inst.last()
print(trie_inst.size())
print(trie_inst.next('arz'))
print(trie_inst.auto_complete('ar'))