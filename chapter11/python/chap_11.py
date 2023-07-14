

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
    

bst = BST() 
bst.add(22)
bst.add(22)
bst.add(18)

print(bst.root.val)   # 22
print(bst.root.right.val)  # 22
print(bst.root.right.right)  # None 
print(bst.root.right.left)  # None 

print('{}'.format(bst.contains(18)))
print('{}'.format(bst.contains(17)))
print('{}'.format(bst.contains(22)))
print('{} {}'.format('max', bst.max()))
print('{} {}'.format('min', bst.min()))

