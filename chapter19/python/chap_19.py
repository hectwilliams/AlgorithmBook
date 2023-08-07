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
        left  = 0 
        right = 0 
        
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

tree = AVL_TREE()
tree.add(40)
tree.add(22)
tree.add(62)