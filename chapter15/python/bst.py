import re
class BTNode:
    def __init__(self, val):
        self.val = val
        self.left = None   # less than 
        self.right = None  # greater than or equal 
        self.parent = None 

class BST:
    def __init__(self):
        self.root = None 
        
    def add(self, val):
        bt_node = BTNode(val)    

        if self.root == None:
            self.root = bt_node
        else: 
            node = self.root 
            prev = None 

            while node:
                prev = node 
                if val >= node.val:
                    node = node.right 
                    if node == None:
                        
                        prev.right = bt_node  
                        prev.right.parent = prev
                else:
                    node = node.left 
                    if node == None:
                        prev.left = bt_node
                        prev.left.parent = prev

    def contains(self, val):
        node = self.root 
        while node:
            if val == node.val:
                return True 
            elif val > node.val :
                node = node.right 
            else: 
                node = node.left 
        return False 

    def min(self):
        node = self.root 
        
        while node.left:
            node = node.left 
        return node.val
    
    def max (self):
        node = self.root 

        while node.right:
            node = node.right 
        return node.val 
    
    def size(self): 
        q = [self.root]
        count = 0 

        while q:
            node = q.pop(0)

            if node:
                count += 1
                q.append(node.left)
                q.append(node.right)
            
        return count 
    
    def is_empty(self):
        return self.size() == 0

    def height(self):
        class height_node:
            def __init__(self, root = None):
                self.height = 0
                self.bst_node = root 
        
        def clone(parent):
            c_node = height_node()
            c_node.height = parent.height 
            c_node.bst_node = parent.bst_node 
            return c_node 
        
        q = [height_node(self.root)]
        
        height_out = 0 

        while q:
            node = q.pop() 

            if node.bst_node:
                node.height += 1
                
                if node.height > height_out:
                    height_out = node.height

                #left 
                new_node = clone(node)    
                new_node.bst_node = new_node.bst_node.left 
                q.append(new_node)
                
                # right 
                new_node = clone(node)
                new_node.bst_node = new_node.bst_node.right 
                q.append(new_node)

        return height_out

    def is_balanced(self):
        # use height method above 
        root = self.root 
        left = None 
        right = None 

        self.root = root.left 
        left = self.height()

        self.root = root.right 
        right = self.height() 
        right = self.height()
        
        print(right, left)
        # set root back to original
        self.root = root 
        
        return abs( left - right) <= 1

    def min_height(self):
        class h_node:
            def __init__(self, parent = None):
                self.bst_node = parent 
                self.height = 0
        
        if self.root == None:
            return 0
        
        queue = [h_node(self.root)]
        
        min_height = None 

        while queue:
            node = queue.pop()

            if node.bst_node.left == None and node.bst_node.right == None:
                if min_height == None:
                    min_height = node.height
                if node.height < min_height:
                    min_height = node.height 

            if node.bst_node.left:
                new_node  = h_node(node.bst_node.left)
                new_node.height = node.height + 1
                queue.append(new_node)

            if node.bst_node.right:
                new_node = h_node(node.bst_node.right)
                new_node.height = node.height + 1
                queue.append(new_node)

        return min_height

    def remove(self, val):
        node = self.root 
        prev = None 
        
        if node == None:
            return node
        
        while node:

            if node.val == val:
                
                # leaf
                if node.left  == None and node.right == None:
                    
                    if self.root == node:
                        self.root = None 
                    elif prev.left == node:
                        prev.left = None 
                    elif prev.right == node:
                        prev.right = None 
                    del(node)
                    break

                # delete root 
                if prev == None:
                    if node.right == None:
                        self.right = node.left
                    elif node.left == None:
                        self.root = node.right 
                    else:
                        left_root_node = node.left 
                        right_root_node = node.right 
                        left_right_detached_node = node.left.right 
                        right_left_deep_node = self.root 
                        right_left_deep_node = right_left_deep_node.right 
                        while right_left_deep_node.left :
                            right_left_deep_node = right_left_deep_node.left 
                        left_root_node.right = right_root_node
                        right_left_deep_node.left = left_right_detached_node
                        self.root = left_root_node 
                        del(node)
                        break 

                # left delete ( right rotate)
                elif prev.left == node:         

                    left_right_detached_node = node.left.right
                    
                    if node.right == None:
                        node.right = left_right_detached_node 
                    else:
                        right_left_deep_node = node.right
                        while right_left_deep_node.left:
                            right_left_deep_node = right_left_deep_node.left 
                        right_left_deep_node.left = left_right_detached_node 
                    prev.left = node.left
                    del(node)
                    break 

                # right delete (left roatate) 
                elif prev.right == node:
                    right_left_detach_node = node.right.left
                    prev.right = node.right

                    if node.left == None:
                        node.left = right_left_detach_node
                    else:
                        left_right_deep_node = node.left
                        while left_right_deep_node.right:
                            left_right_deep_node = left_right_deep_node.right 
                        left_right_deep_node.right = right_left_detach_node 
                    prev.right = node.right 
                    del(node)
                    break

            elif val <  node.val and node.left !=  None :
                
                prev = node 
                node = node.left 

            elif val > node.val and  node.right != None :
                prev = node 
                node = node.right 

            # value not found 
            else:
                node = node.left 


    def remove_all(self):

        if self.root == None:
            return None 
        
        stackA = [self.root]
        stackB = []
        
        while  stackA or stackB:
            
            # stack A has priority 
            if stackA:
                node = stackA.pop()
            elif stackB:
                node = stackB.pop() 

            if node:
                if node.left :
                    stackA.append(node.left) 
                if node.right:
                    stackB.append(node.right)
            
            print('delete ', node.val, end=' ')
            node.left = None
            node.right = None 
            del(node)


        print('delete ', self.root.val, )
        del(self.root)

        self.root = None 
        self.right = None 
        self.left = None 
    
    def is_valid(self):
        histo = {}

        if self.root == None:
            return None 
        
        q = [self.root]

        while q:

            node = q.pop(0)
            res = re.compile(r'0x.+[^\>]').search(str(node))  # match character class 
            key = 'addr_' + str(node)[res.span()[0] + 2 : res.span()[1]]

            if key not in  histo :
                histo[key] = 0
                
            histo[key] += 1

            if histo[key] > 1:
                return False 

            if node.left:
                if not (node.left.val < node.val):
                    return False 
                q.append(node.left)  
            
            if node.right:
                if not (node.right.val >= node.val ):
                    return False 
                q.append(node.right)
        
        return True 

    
    def add_without_dupes(self, val):
        prev = None 
        node = self.root 

        if node == None:
            self.root = BTNode(val)
        else:
            while node:

                if node.val == val:
                    return False 

                if node.left:
                    if val < node.val: 
                        node = node.left 
                        continue
                if node.right :
                    if val > node.val:
                        node = node.right 
                        continue 
                if node == None:
                    if val < prev.val:
                        prev.left = BTNode(val)
                        prev.left.parent = prev
                    if val > prev.val:
                        prev.right = BTNode(val)
                        prev.right.parent = prev 
                    break 
        return True 


    def val_before(self, val):
        node = self.root 

        if node == None:
            return None 
        
        while node:

            if node.val == val:
                if node.parent:
                    return node.parent.val 
                else:
                    return None 
            
            if node.right == None and node.left == None:
                if node.parent:
                    return node.parent.val 
                else:
                    return node.val 
            
            if node.parent:
                if val > node.val and val < node.parent.val:
                    return None 
            
            if node.parent:
                if val > node.parent.val and val < node.val:
                    return None
            
            
            
            if node.left:
                if val < node.val:
                    node = node.left 
                    continue
            
            if node.right:
                if val > node.val:
                    node = node.right 
                    continue
                
        return None 
        
    def val_after(self, val):
        node = self.root

        if node == None:
            return None 
        
        while node:

            if node.val == val:
                
                if node.right:
                    return node.right.val 
                else:
                    return None 
            
            if node.right == None and node.left == None:
                return None 
            
            if node.left:
                if val > node.left.val and val < node.val:
                    return node.val
                
                if val < node.val:
                    node = node.left 
                    continue 

            if node.right:
                if val < node.right.val and val > node.val:
                    return node.right.val
                
                if val > node.val:
                    node = node.right 
                    continue 

    def closest_value(self, val):
        class closest_node:
            def __init__(self, node):
                self.bst_node = node 
                self.path = []
        
        def clone(parent):
            c_node = closest_node(parent)
            c_node.bst_node = parent.bst_node
            c_node.path = parent.path + []
            return c_node 
        
        if self.root == None:
            return None 
        
        queue = [closest_node(self.root)]
        
        delta = None 

        while queue:
            
            node = queue.pop(0) 

            if node.bst_node.val == val:
                return node.bst_node.val
            
            if delta == None:
                delta = abs(val - node.bst_node.val)
            elif abs(val - node.bst_node.val) < delta:
                delta = abs(val - node.bst_node.val)
                
            if node.bst_node.right:
                
                if val > node.bst_node.val :
                    new_node = clone(node)
                    new_node.path += [node]
                    new_node.bst_node = new_node.bst_node.right 

                    if abs(val - node.bst_node.right.val) < delta:
                        queue.append(new_node)
            
            if node.bst_node.left:
                if val < node.bst_node.val:
                    new_node = clone(node)
                    new_node.path += [node]
                    new_node.bst_node = new_node.bst_node.left 
                    if abs(val - new_node.bst_node.left.val) < delta:
                        queue.append(new_node)  
        
        return node.bst_node.val

    def tree_path_sums (self):
        class sum_node:
            def __init__(self, node):
                self.path = [] 
                self.bst_node = node
                self.at_leaf = False 
        
        def clone(parent):
            c_node = sum_node(parent)
            c_node.path = parent.path +  []
            c_node.bst_node = parent.bst_node 
            return c_node 

        if self.root ==  None:
            return None 
        
        q = [ sum_node(self.root) ]

        paths = []
        
        while q:

            node = q.pop(0)

            if node:    

                if node.at_leaf:
                    paths.append( list(map( lambda node_: node_.bst_node.val ,  node.path) ))
                    continue

                if node.bst_node.left:
                    new_node = clone (node)
                    new_node.path += [node]
                    new_node.bst_node = new_node.bst_node.left
                    q.append(new_node)
                                    
                if node.bst_node.right:
                    new_node = clone (node)
                    new_node.path += [node]
                    new_node.bst_node = new_node.bst_node.right
                    q.append(new_node)

                # left node  or non full nodes 
                if node.bst_node.right == None and node.bst_node.left == None   or node.bst_node.right == None and node.bst_node.left or node.bst_node.right and node.bst_node.left == None :
                    new_node = clone(node) 
                    new_node.path += [node]
                    new_node.at_leaf = True 
                    q.append(new_node)

        return paths 
    

    def is_complete(self):
        class s_node:
            def __init__(self, node):
                self.prev = []
                self.current = node

        
        if self.root == None: 
            return False 
        
        if self.root.left == None and self.root.right == None:
            return False  
        
        q = [s_node(self.root)]


        while q:

            node = q.pop(0)
            
            if node:

                if node.current.left == None and node.current.right == None :
                    if ( node.prev[-1].current.left  and node.prev[-1].current.right ) :
                        return False 
                else:
                    if node.current.left:
                        new_node = s_node(node.current.left)
                        new_node.prev += [node]
                        q.append(new_node)
                    
                    if node.current.right:
                        new_node = s_node(node.current.right)
                        new_node.prev += [node]
                        q.append(new_node)      

        return True 

    
    def repair(self):

        class s_node:
            def __init__(self, node):
                self.prev = []
                self.curr = node
                
        if self.root == None:
            return False 
        
        q = [s_node(self.root)]

        while q:
            
            node = q.pop(0) 

            if node.curr.left:
                
                if node.curr.left.val >= node.curr.val:
                
                    #swap 

                        old_root = node.curr
                        new_root = node.curr.left  
                        old_root.right = node.curr.left.right
                        old_root.left =  node.curr.left.left 
                        new_root.left = old_root
                        new_root.right = node.right
                        
                        if self.root == node.curr:
                            self.root = new_root 
                        else:
                            prev = node.prev[-1]
                            if prev.curr.right == node.curr:
                                prev.curr.right = new_root 
                            else: 
                                prev.curr.left = new_root 

                        q = [s_node(self.root)]
                        continue

            if node.curr.right:
                
                if node.curr.rght.val < node.curr.val:
                    
                    old_root = node.curr 
                    new_root = node.curr.right 
                    old_root.right  = node.curr.right.right
                    old_root.left = node.curr.right.left
                    new_root.right = old_root 
                    new_root.left = node.left 

                    if self.root == node.curr :
                        self.root = new_root
                    else:
                        prev = node.prev[-1]
                        if prev.curr.right == node.curr:
                            prev.curr.right = new_root 
                        else:
                            prev.curr.left = new_root 
                    pass 

                    #swap  TBD 

                    q = [s_node(self.root)]
                    continue

    def smallest_distance(self):
        class s_node:
            def __init__(self, node ):
                self.path = []
                self.curr = node 
                self.leaf = False 
        
        paths = [] 
        
        # find paths
        if self.root == None: 
            return None 
        
        stackA = [s_node(self.root)]
        stackB = [] 

        while stackA or stackB:

            if stackA:
                node = stackA.pop()
            elif stackB:
                node = stackB.pop() 
            
            if node.leaf:
                paths.append(node.path)
                continue

            if node.curr.left == None and node.curr.right == None:
                new_node = s_node(None)
                new_node.path  +=  node.path + [node]
                new_node.leaf = True 
                stackA.append(new_node)
            else :

                if node.curr.left :
                    new_node = s_node(node.curr.left)
                    new_node.path +=  node.path   + [node]
                    stackA.append(new_node)

                if node.curr.right:
                    new_node = s_node(node.curr.right)
                    new_node.path +=  node.path   + [node]
                    stackB.append(new_node)

        smallest = None 
        smallest_node = None 

        for arr in paths:
            for i in range(len(arr)):
                for k in range(i + 1 , len(arr) ):
                    delta = abs(arr[i].curr.val - arr[k].curr.val)
                    if smallest == None:
                        smallest = delta
                        smallest_node = (arr[i].curr.val  , arr[k].curr.val )
                    if smallest > delta:
                        smallest = delta
                        smallest_node = (arr[i].curr.val  , arr[k].curr.val )


        return smallest_node


    def reverse(self):

        class s_node:
            def __init__(self, node):
                self.curr = node
                self.depth = 0

        table = []

        if self.root == None:
            return None 
        
        q = [s_node(self.root)]

        while q:

            node = q.pop(0)
            
            print(node.depth)

            if node.depth  == len(table):
                table.append( [] )
            
            table[node.depth].append(node)

            if node:

                if node.curr.left:
                    new_node = s_node(node.curr.left)
                    new_node.depth = node.depth + 1
                    q.append(new_node)
                
                if node.curr.right:
                    new_node = s_node(node.curr.right)
                    new_node.depth += node.depth  + 1
                    q.append(new_node)
        

        # reverse all arrays in table
        for arr in table:
            half = len(arr) // 2
            for i in range(half):
                arr[i], arr[len(arr) - i - 1] = arr[ len(arr) - i - 1 ] , arr[i] 

        ## serialize 
        table_serial = []
        for arr in table:
            table_serial += arr


        ## create new bst 

        for i in range( len(table_serial) // 2):
            root = None 
            current = None 

            # set to BT Node 
            table_serial[i] = table_serial[i].curr
            
            child_left_index = 2*i + 1
            child_right_index = 2*i + 2

            if child_left_index < len(table_serial):
                table_serial[i].left = table_serial[child_left_index].curr 
            
            if child_right_index < len(table_serial):
                table_serial[i].right = table_serial[child_right_index].curr

        root = table_serial[0]    


    def partition(self, value):
        
        arr = []

        if self.root == None:
            return None 
        
        q = [self.root]

        while q:
            
            node = q.pop(0)

            arr.append(node)

            if node.left :
                q.append(node.left)

            if node.right:
                q.append(node.right)


        def sortbyNodeVal(node):
            return node.val 
        
        arr.sort(key=sortbyNodeVal)
        split_index = 0
        
        for i in range(len(arr)):
            if arr[i].val  <=  value:
                split_index = i
        
        left  = arr[0 : split_index]
        left_root = None 
        right  = arr[split_index : :]
        right_root = None 
        prev = None 
        
        # print( list(map( lambda n: n.val , left)) )
        # print( list(map( lambda n: n.val , right)) )



        while left:
          
            target = left.pop() 
            
            if left_root == None:
                left_root = target 
            else:
                runner = left_root
                val = target.val

                while runner:
                
                    if val < runner.val:
                        prev = runner
                        runner = runner.left 
                        if runner == None:
                            prev.left = target

                    elif val >= runner.val:
                        prev = runner 
                        runner = runner.right
                        if runner ==None:
                            prev.right = target


        while right:
          
            target = right.pop(0) 

            if right_root == None:
                right_root = target 
            else:
                runner = right_root
                val = target.val

                while runner:
                
                    if val < runner.val:
                        prev = runner
                        runner = runner.left 
                        if runner == None:
                            prev.left = target
                    elif val >= runner.val:
                        prev = runner 
                        runner = runner.right
                        if runner ==None:
                            prev.right = target

        return {
            'left_root' : left_root,
            'right_root' : right_root
        }