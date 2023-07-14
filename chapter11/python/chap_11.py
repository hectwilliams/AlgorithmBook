

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

arr = [1,2,3,4,5] 
tree_ = array_to_bst(arr)

print('{}'.format(tree_.root.val))  #3
print('{}'.format(tree_.root.right.val))  #4
print('{}'.format(tree_.root.right.right.val)) # 5
print('{}'.format(tree_.root.left.val)) # 2
print('{}'.format(tree_.root.left.left.val)) # 1

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