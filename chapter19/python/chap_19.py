# AVL TREEE 
import random 

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
                    
                    if curr: 

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
        
    def rotate_left(self, target_node):
        
        class search_node:
            def __init__(self, current, prev_list = []):
                self.tree_node = current
                self.tree_node_prev = prev_list
        
        node = None 
        demote_node = None 
        promote_node = None 

        if self.head == None:
            return 
        
        if self.head.right == None:
            return 
        
        queue = [  search_node(self.head)  ]

        while queue:

            node = queue.pop(0)
            
            if node.tree_node == target_node:
                demote_node = node.tree_node
                promote_node = node.tree_node.right 
                grand_child = None 

                if promote_node:
                    grand_child = promote_node.left 
                    demote_node.right = grand_child 
                    promote_node.left = demote_node

                if len(node.tree_node_prev) == 0:
                    self.head = promote_node

                elif node.tree_node_prev[-1].right == demote_node:
                    node.tree_node_prev[-1].right = promote_node

                elif node.tree_node_prev[-1].left == demote_node:
                    node.tree_node_prev[-1].left = promote_node
                
                break 
                    
            if node.tree_node.left:
                queue.append( search_node(node.tree_node.left, node.tree_node_prev +  [node.tree_node]  ) )
            
            if node.tree_node.right:
                queue.append( search_node(node.tree_node.right,     node.tree_node_prev +  [node.tree_node]  ) )

        # update balance 
        if node:
            node.tree_node_prev.extend([demote_node, promote_node])
            while node.tree_node_prev:
                curr = node.tree_node_prev.pop()
                left = curr.left 
                right = curr.right 
                if left:
                    left = left.height() + 1
                else:
                    left = 0 
                if right:
                    right = -right.height() - 1
                else:
                    right = 0 
                curr.balance = left + right 

    def rotate_right (self, target_node):
        class search_node:
            def __init__(self, current, prev_list = []):
                self.tree_node = current 
                self.tree_node_prev = prev_list
        node = None 
        demote_node = None 
        promote_node = None 

        if self.head == None:
            return 
        if self.head.left == None :
            return 
        
        queue = [search_node(self.head)]

        while queue:
            node = queue.pop(0)

            if node.tree_node == target_node:
                demote_node = node.tree_node
                promote_node = node.tree_node.left
                grand_child = None 

                if promote_node:
                    grand_child = promote_node.right
                    demote_node.left = grand_child 
                    promote_node.right = demote_node
                
                if len(node.tree_node_prev) == 0:
                    self.head = promote_node 
                elif node.tree_node_prev[-1].right == demote_node:
                    node.tree_node_prev[-1].right = promote_node 
                elif node.tree_node_prev[-1].left == demote_node:
                    node.tree_node_prev[-1].left = promote_node 
                
                break 

            if node.tree_node.left:
                queue.append(search_node(node.tree_node.left, node.tree_node_prev + [node.tree_node]) )
            
            if node.tree_node.right:
                queue.append(search_node(node.tree_node.right, node.tree_node_prev + [node.tree_node]) )
            # update balance 
        
        if node:
            node.tree_node_prev.extend([demote_node, promote_node])
            while node.tree_node_prev:
                curr = node.tree_node_prev.pop()
                left = curr.left 
                right = curr.right 
                if left:
                    left = left.height() + 1
                else:
                    left = 0 
                if right:
                    right = -right.height() - 1
                else:
                    right = 0 
                curr.balance = left + right 
    
    def balanced_add(self, value):

        self.add(value)

        if self.head.balance > 1 :
            
            if self.head.left.balance > 0 :
                # right rotate 
                self.rotate_right(self.head)
            
            if self.head.left.balance < 0 :
                # left rotoate child 
                self.rotate_left(self.head.left)
                # right rotate paremt 
                self.rotate_right(self.head)
            
        if self.head.balance < -1:

            if self.head.right.balance < 0 :
                # left rottate 
                self.rotate_left(self.head)
            
            if self.head.right.balance > 0:
                #right rotate child 
                self.rotate_right(self.head.left)

                # left rotate parent 
                self.rotate_left(self.head)
        
    def display_tree(self): 
        
        class s_node:
            def __init__(self, parent, depth = 0):
                self.curr = parent
                self.depth = depth 

        if self.head == None:
            return 
        
        queue = [s_node(self.head)]
        arr = []

        while queue:
            
            node = queue.pop(0) 

            if len(arr) == node.depth:
                arr.append([])
            
            arr[node.depth].append(node.curr.val)

            if node.curr.left:
                queue.append( s_node(node.curr.left, node.depth + 1) )

            if node.curr.right:
                queue.append( s_node(node.curr.right, node.depth + 1) )


        for ele in arr:
            print('{}\n'.format(ele))

    def balanced_remove(self, value):

        self.remove(value)

        while abs(self.head.balance) > 1 :
            
            if self.head.balance > 1 :
            
                if self.head.left.balance > 0 :
                    # right rotate 
                    self.rotate_right(self.head)
                
                if self.head.left.balance < 0 :
                    # left rotoate child 
                    self.rotate_left(self.head.left)
                    # right rotate paremt 
                    self.rotate_right(self.head)
            
            if self.head.balance < -1:

                if self.head.right.balance < 0 :
                    # left rottate 
                    self.rotate_left(self.head)
                
                if self.head.right.balance > 0:
                    #right rotate child 
                    self.rotate_right(self.head.left)
                    # left rotate parent 
                    self.rotate_left(self.head)



tree = AVL_TREE()
tree.balanced_add(40)
tree.balanced_add(22)
tree.balanced_add(62)
tree.balanced_add(70)
tree.balanced_add(77)
tree.balanced_add(77)
tree.balanced_add(89)

tree.balanced_remove(40)
tree.balanced_remove(89)
tree.balanced_remove(77)
tree.balanced_remove(77)

tree.display_tree()

class RB_Node:
    def __init__(self, value):
        self.value = value
        self.color = 'red'
        self.left = None 
        self.right = None 

class RB_Tree:

   
    def __init__(self):
        self.root = None 

    def rotate_left(self, target_node):
        
        class search_node:
            def __init__(self, current, prev_list = []):
                self.tree_node = current
                self.tree_node_prev = prev_list
        
        node = None 
        demote_node = None 
        promote_node = None 

        if self.root == None:
            return 
        
        if self.root.right == None:
            return 
        
        queue = [  search_node(self.root)  ]

        while queue:

            node = queue.pop(0)
            
            if node.tree_node == target_node:
                demote_node = node.tree_node
                promote_node = node.tree_node.right 
                grand_child = None 

                if promote_node:
                    grand_child = promote_node.left 
                    demote_node.right = grand_child 
                    promote_node.left = demote_node

                if len(node.tree_node_prev) == 0:
                    self.root = promote_node

                elif node.tree_node_prev[-1].right == demote_node:
                    node.tree_node_prev[-1].right = promote_node

                elif node.tree_node_prev[-1].left == demote_node:
                    node.tree_node_prev[-1].left = promote_node
                
                break 
                    
            if node.tree_node.left:
                queue.append( search_node(node.tree_node.left, node.tree_node_prev +  [node.tree_node]  ) )
            
            if node.tree_node.right:
                queue.append( search_node(node.tree_node.right,     node.tree_node_prev +  [node.tree_node]  ) )

    def rotate_right (self, target_node):
        class search_node:
            def __init__(self, current, prev_list = []):
                self.tree_node = current 
                self.tree_node_prev = prev_list
        node = None 
        demote_node = None 
        promote_node = None 

        if self.root == None:
            return 
        if self.root.left == None :
            return 
        
        queue = [search_node(self.root)]

        while queue:
            node = queue.pop(0)

            if node.tree_node == target_node:
                demote_node = node.tree_node
                promote_node = node.tree_node.left
                grand_child = None 

                if promote_node:
                    grand_child = promote_node.right
                    demote_node.left = grand_child 
                    promote_node.right = demote_node
                
                if len(node.tree_node_prev) == 0:
                    self.root = promote_node 
                elif node.tree_node_prev[-1].right == demote_node:
                    node.tree_node_prev[-1].right = promote_node 
                elif node.tree_node_prev[-1].left == demote_node:
                    node.tree_node_prev[-1].left = promote_node 
                
                break 

            if node.tree_node.left:
                queue.append(search_node(node.tree_node.left, node.tree_node_prev + [node.tree_node]) )
            
            if node.tree_node.right:
                queue.append(search_node(node.tree_node.right, node.tree_node_prev + [node.tree_node]) )
        
    def add(self, value):

        class search_node:
            def __init__(self, parent, path = []):
                self.tree_node = parent
                self.path = path
        
        def black_node_check_valid(parent):
            # path search
            stackA = [search_node(parent.root)]
            stackB = []
            node = None 
            all_paths = [] 
            while stackA or stackB:

                if stackA:
                    node = stackA.pop(0)
                else:
                    node = stackB.pop(0)

                if node.tree_node.left:
                    if node.tree_node.color =='red' and node.tree_node.left.color == 'red':
                        return False
                    stackA.append (search_node(node.tree_node.left, node.path + [node.tree_node] ) )

                if node.tree_node.right:
                    if node.tree_node.color =='red' and node.tree_node.right.color == 'red':
                        return False
                    stackB.append (search_node(node.tree_node.right, node.path + [node.tree_node] ) )
                
                
                if node.tree_node.left == None and node.tree_node.right == None:
                    all_paths.append(node.path + [node.tree_node])


            # map to color --> to black count  per paths
            if all_paths:
                all_paths = list(
                        map( lambda node_list:   
                            list(map(  lambda node_: node_.color , node_list) ).count('black')
                        , all_paths )
                    )
                
            return all(color_count == all_paths[0] for color_count in all_paths ) 



        node_path = []
        
        if self.root == None:
            self.root = RB_Node(value)
            self.root.color = 'black'

        else:

            node = self.root 

            while node:
                
                if value < node.value:

                    node_path.append(node)

                    if node.left:
                        node = node.left 
                    else:
                        node.left = RB_Node(value)
                        # if node_path[-1].color == 'red':
                            # node.left.color = 'black'
                        node_path.append(node.left) # complete the path
                        node  =  None 

                elif value > node.value:

                    node_path.append(node)
                    
                    if node.right:
                        node = node.right 
                    else:                
                        node.right = RB_Node(value)
                        # if node_path[-1].color == 'red':
                            # node.right.color = 'black'
                        node_path.append(node.right) # complete the path
                        node  =  None 
            
            #rebelance block 
            while not black_node_check_valid(self) :

                if len(node_path)   < 3:
                    return

                child = node_path[-1]
                parent = node_path[-2]
                grand_parent = node_path[-3]
                aunt = grand_parent.right if grand_parent.left == parent else grand_parent.left 
                great_grand_parent = None 

                # algorithm provided by  https://www.programiz.com/dsa/red-black-tree
                
                if parent == grand_parent.left:

                    gp_right_node_color = 'black'

                    if aunt: # on right 
                        if aunt.color == 'red':
                            gp_right_node_color = 'red'
                    
                    # case 1.a
                    if gp_right_node_color == 'red':
                        parent.color = 'black' # gp.left
                        aunt.color = 'black' # gp.right
                        grand_parent.color = 'red'

                        # promote gp to new child node by dropping child node and parent node 
                        node_path.pop() # pop child node 
                        node_path.pop() # pop parent node 
                    
                    # case 2
                    elif parent.right == child and parent.color == 'red' and child.color == 'red':
                        self.rotate_left(parent) # child promoted to parent
                        node_path[-1] , node_path[-2] = node_path[-2] , node_path[-1]  # swap parent and child 
                        child = node_path[-1]
                        parent = node_path[-2]

                        if black_node_check_valid(self):
                            break 
                    
                    # case 3
                    elif parent.left == child  and parent.color =='red' and child.color == 'red':
                        parent.color = 'black'
                        grand_parent.color = 'red'
                        self.rotate_right(grand_parent)

                        node_path.pop() # pop child (parent is child node on next loop)
                        node_path.pop() # pop parent node 
                    

                elif parent == grand_parent.right:

                    gp_left_node_color = 'black'

                    if aunt: # on left
                        if aunt.color == 'red':
                            gp_left_node_color = 'red'
                    
                    # case 1
                    if gp_left_node_color == 'red':
                        parent.color = 'black'
                        aunt.color = 'black'
                        grand_parent.color = 'red'
                        
                        # promote gp to new child node by dropping child node and parent node 
                        node_path.pop() # pop child node 
                        node_path.pop() # pop parent node 
                    
                    # case 2
                    elif parent.left == child and parent.color == 'red' and child.color == 'red':
                        self.rotate_right(parent) # child promoted to parent
                        node_path[-1] , node_path[-2] = node_path[-2] , node_path[-1]  # swap parent and child 
                        child = node_path[-1]
                        parent = node_path[-2]

                        if black_node_check_valid(self):
                            break 

                    # case 3
                    elif parent.right == child and parent.color == 'red' and child.color == 'red':

                        parent.color = 'black'
                        grand_parent.color = 'red'
                        self.rotate_left(grand_parent)
                        
                        node_path.pop() # pop child (parent is child node on next loop)
                        node_path.pop() # pop parent node 

            self.root.color = 'black'            
                

    def contains(self, value):
        if self.root == None:
            return None 

        queue = [self.root]

        while queue:
            node = queue.pop(0)

            if node.value == value:
                return True 
        
            if value < node.value:
                if node.left:
                    queue.append(node.left)
            
            if value > node.value:
                if node.right:
                    queue.append(node.right) 

        return False 

    def display_tree(self): 
        
        class s_node:
            def __init__(self, parent, depth = 0):
                self.curr = parent
                self.depth = depth 

        if self.root == None:
            return 
        
        queue = [s_node(self.root)]
        arr = []

        while queue:
            
            node = queue.pop(0) 

            if len(arr) == node.depth:
                arr.append([])
            
            arr[node.depth].append( str(node.curr.value) + ' ' + node.curr.color)

            if node.curr.left:
                queue.append( s_node(node.curr.left, node.depth + 1) )

            if node.curr.right:
                queue.append( s_node(node.curr.right, node.depth + 1) )


        for ele in arr:
            print('{}\n'.format(ele))


    def remove(self, value):
        if self.root == None:
            return None 
        
        queue = [self.root]

tree = RB_Tree()
tree.add(40)
tree.add(22)
tree.add(92)
tree.add(389)
tree.add(491)
tree.add(132)
tree.add(1320)
tree.add(2)

print()
print(tree.display_tree())
