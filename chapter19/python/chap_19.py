# AVL TREEE 

class AVL_NODE:
    def __init__(self, value):
        self.val = value 
        self.balance = 0 
        self.left = None 
        self.right = None

    def height(self):

        class search_node:
            def __init__(self, node, depth = 0):
                self.depth = depth
                self.tree_node = node 
        
        result_height = 0 

        if self == None:
             return 0 
        
        queue = [ search_node(self) ]

        while queue:
            node = queue.pop(0)
            print(node.tree_node.val, 'search', node.tree_node.left)
            if node.depth > result_height:
                 result_height = node.depth 

            if node.tree_node.left:
                tmp_node = search_node(node.tree_node.left, node.depth + 1)
                queue.append(tmp_node)
            
            if node.tree_node.right:
                tmp_node = search_node(node.tree_node.right, node.depth + 1)
                queue.append(tmp_node)
        
        return result_height 
    
    def is_balanced(self):
        return abs(self.balance) <= 1
        
class AVL_TREE:
    def __init__(self):
        self.head = None 

    def height(self):
        return self.head.height 
    
    def is_balanced(self):
        return abs(self.head.balance) <= 1
    
    def add(self, value):
        node = self.head
        path = []
        
        if node == None:
            self.head = AVL_NODE(value)
            return None 
        
        while node :

            path.append(node)
            
            if value < node.val:
                
                if node.left:
                    node = node.left 
                else: 
                    node = None 
                    path[-1].left = AVL_NODE(value)
                    balance_update = 1
            
            elif value >= node.val:

                if node.right:
                    node = node.right 
                else:
                    node = None 
                    path[-1].right = AVL_NODE(value)
                    balance_update = -1

        
        # balance update (back propagation)
        if path:
            while path:
                node = path.pop() 
                node.balance += balance_update 

    def remove(self, value):
        nodes = [] 
        node = None 

        if self.head == None:
            return 
        
        node = self.head 

        while node:
            
            if value == node.val:

                if len(nodes) == 0:
                    grand_child = None 
                    child_r = node.right 
                    child_l = node.left 

                    if child_r:
                        grand_child = child_r.left 
                        child_r.left = child_l or grand_child

                    if child_l:
                        curr_node = child_l
                        while curr_node.right:
                            curr_node = curr_node.right 
                        curr_node.right = grand_child 

                    self.head = child_r 
                
                elif nodes[-1].right == node : 
                    grand_child = None 
                    child_r = node.right 
                    child_l = node.left 

                    if child_r :
                        grand_child = child_r.left 
                        child_r.left = child_l or grand_child
                    
                    if child_l:
                        curr_node = child_l
                        while curr_node.right:
                            curr_node = curr_node.right 
                        curr_node.right = grand_child 
                    
                    nodes[-1].right = child_r 

                elif nodes[-1].left == node:
                    grand_child = None 
                    child_r = node.right 
                    child_l = node.left 

                    if child_l:
                        grand_child = child_l.right 
                        child_l.right = child_r or grand_child

                    if child_r:
                        curr_node = child_r 
                        while curr_node.left:
                            curr_node = curr_node.left 
                        curr_node.left = grand_child
                    
                    nodes[-1].left = child_l 
            

                # update balance
                nodes.extend( [child_l, child_r] ) 

                while nodes:

                    curr = nodes.pop() 
                    
                    left = curr.left 
                    if left:
                        left = left.height()  + 1
                    else:
                        left = 0 
                         
                    right = curr.right
                    if right:
                        right = -right.height()  -1
                    else: 
                        right = 0 

                    curr.balance = left + right  
                    
                break 

            
            nodes.append(node)
            
            if value < node.val:
                node = node.left 
            
            elif value > node.val :
                node = node.right 
            
            else :
                node = None  
        


tree = AVL_TREE()
tree.add(40)
tree.add(22)
tree.add(62)
tree.add(70)
tree.add(32)
tree.add(21)

tree.remove(40)
print(tree.head.val, tree.head.balance)
print(tree.head.left.val, tree.head.left.balance)
print(tree.head.left.left.val, tree.head.left.left.balance)