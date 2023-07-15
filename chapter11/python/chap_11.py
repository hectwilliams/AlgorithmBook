

class BTNode:
    def __init__(self, val):
        self.val = val
        self.left = None   # less than 
        self.right = None  # greater than or equal 

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
                else:
                    node = node.left 
                    if node == None:
                        prev.left = bt_node

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
                        node.left.right = node.right 
                    prev.left = node.left
                    del(node)
                    break 

                # right delete (left roatate) 
                elif prev.right == node:
                    pass 

            elif val <  node.val and node.left !=  None :
                
                prev = node 
                node = node.left 

            elif val > node.val and  node.right != None :
                prev = node 
                node = node.right 

        

bst = BST() 
bst.add(22)
bst.add(22)
bst.add(18)
bst.add(23)
bst.add(23)

print(bst.root.val)   # 22
print(bst.root.right.val)  # 22
print(bst.root.right.right)  # None 
print(bst.root.right.left)  # None 

print('{}'.format(bst.contains(18)))
print('{}'.format(bst.contains(17)))
print('{}'.format(bst.contains(22)))
print('{} {}'.format('max', bst.max()))
print('{} {}'.format('min', bst.min()))
print('{} {}'.format('size', bst.size()))
print('{} {}'.format('is empty?', bst.is_empty()))
print('{} {}'.format('height?', bst.height()))
print('{} {}'.format('is balaned?', bst.is_balanced()))

#utility function to help review list of values in tree 
def array_to_bst(arr):
    bst = BST() 

    while len(arr):
        mid = len(arr) // 2

        # odd casee 
        if len(arr) % 2 == 1:
            mid + 1
            bst.add(arr[mid])
            arr = arr[0: mid] + arr[mid + 1 : :]
        # even 
        else:
            bst.add(arr[mid - 1])
            bst.add(arr[mid])
            arr = arr[0: mid - 1] + arr[mid + 1 : :]
    return bst 

arr = [1,2,3,4,5,6,6] 
tree_ = array_to_bst(arr)

print('{} {}'.format('root', tree_.root.val))  #3
print('{} {} '.format( 'right' , tree_.root.right.val))  #4
print('{} {} '.format('right right',tree_.root.right.right.val)) # 5
print('{} {} '.format( 'left', tree_.root.left.val)) # 2
print('{} {} '.format('left left', tree_.root.left.left.val)) # 1

print('min_height -  {} jump units'.format( tree_.min_height())) 

def closest_common_ancestor(bst, val_1, val_2):

    def get_path(bst, val, path ):
        node = bst.root 
        while node:
            path.append(node)
            if node.left and val < node.val:
                node = node.left 
            elif node.right and val > node.val:
                node = node.right 
            else:
                node = None 
    
    paths = [
        [],
        []
    ]

    get_path(bst, val_1, paths[0])
    get_path(bst, val_2, paths[1])

    # pop off path_1 until finding a match in path_0 list
    while paths[1]:
        node_1 = paths[1].pop() 
        # search path 0
        for node_0 in paths[0]:
            if node_0 == node_1:
                return node_0.val
    return None 

arr = [0,1,1.2,2,3,4,5] 
tree_ = array_to_bst(arr)
low = 0
high = 1.1
print('{} {}'.format('closest ancestor val', closest_common_ancestor(tree_ , low , high )))

# order the node 
def bst_to_array(bst):
    class search_node :
        def __init__(self, parent = None):
            self.bst_node = parent
            self.has_eval_left = False 
    
    stack = [search_node(bst.root)]
    result = [] 

    while stack:
        s_node = stack.pop() 

        if s_node.bst_node.left and s_node.has_eval_left == False:
            s_node.has_eval_left = True 
            stack.append(s_node)

            new_node = search_node(s_node.bst_node.left)
            stack.append(new_node)
            continue 
        

        result.append(s_node.bst_node.val)


        if s_node.bst_node.right:
            new_node = search_node(s_node.bst_node.right)
            stack.append(new_node)



    return result 

arr = [0,1,1.2,2,3,4,5] 
bst_tree = array_to_bst(arr)
print('{}'.format(bst_to_array(bst_tree))) 

# array return can be used to reproduce tree 
def bst_pre_order(bst):
    class search_node:
        def __init__(self, parent = None ):
            self.bst_node = parent 
    stack = []
    result = []

    if bst.root == None:
        return result 
    
    stack.append(search_node(bst.root))

    while stack:
        node = stack.pop() 

        if node:
            result +=  [node.bst_node.val]

            if node.bst_node.right: 
                new_node = search_node(node.bst_node.right)
                stack.append(new_node)

            if node.bst_node.left:
                new_node = search_node(node.bst_node.left)
                stack.append(new_node)     
    return result 

arr = [0,1,1.2,2,3,4,5] 
bst_tree = array_to_bst(arr)
print('{}'.format(bst_pre_order(bst_tree))) 


def bst_post_order(bst):

    class search_node:
        def __init__(self, parent = None) :
            self.bst_node = parent 
            self.eval_left = False 
            self.eval_right = False 

    stack = []
    result = [] 

    if bst.root == None: 
        return result 
    
    stack.append(search_node(bst.root))

    while stack:
        
        node = stack.pop()

        if node:

            if node.bst_node.left == None:
                node.eval_left = True 

            if node.bst_node.right == None:
                node.eval_right = True 

            if node.bst_node.left and node.eval_left == False :
                node.eval_left = True 
                stack.append(node)
                new_node = search_node(node.bst_node.left)
                stack.append(new_node)
                continue 

            elif node.bst_node.right and node.eval_right == False :
                node.eval_right = True 
                stack.append(node)
                new_node = search_node(node.bst_node.right)
                stack.append(new_node)
                continue 
            
            if (node.bst_node.left  == None and node.bst_node.right == None) or ( node.eval_right == True and node.eval_left == True ) :
                result.append(node.bst_node.val)
                
    return result

arr = [0,1,1.2,2,3,4,5] 
bst_tree = array_to_bst(arr)
print('{}'.format(bst_post_order(bst_tree))) 

# fun using path discovery

# remove root 
arr = [0,1,1.2,2,3,4,5] 
bst_tree = array_to_bst(arr)
bst_tree.remove(2)
print('Removed root value of 2, expect 1.2 ---- Solution = {}'.format(bst_tree.root.val))

# remove root 
arr = [0,1,1.2,2,3,4,5] 
bst_tree = array_to_bst(arr)
bst_tree.remove(1.2)
print('Removed value of 1.2, =  1 value was promoted {}'.format(bst_tree.root.left.val))
