# Edge List Implementation 

from ctypes import Structure


class ELGraph:
    def __init__(self):
        self.vertices = []
        self.edge_list = []  # [start , end, edge value]

    def add_vertex(self, value):

        # find vacant slot, and add value 

        try:

            index = self.vertices.index(value)
            self.vertices[index] = value 
        
        # add to array
        
        except: 

            index = len(self.vertices)
            self.vertices.append(value)
        
        return index 
    
    def remove_vertex(self, value):
        # remove node 

        try:
            index = self.vertices.index(value)
            self.vertices[index] = None 
            
            walk = 0
            while walk < len(self.edge_list):
                
                if value in self.edge_list[walk][0: 2]:  # [ id1, id2, edge weight]
                    self.edge_list = self.edge_list[0: walk] + self.edge_list[walk + 1 :]
                else:
                    walk += 1
       
            return True 
        
        except:
            return False 

    def get_vertex_value (self, node_id):

        if node_id < len(self.vertices):
            value = self.vertices[node_id]
            return value 
        
    def set_vertex_value (self, node_id, value):
        
        if node_id < len(self.vertices):
            
            value = self.vertices[node_id]
            
            if value == None:
                return False 
            else: 
                self.vertices[node_id] = value 
                return True 
        
        return False 
    
    def add_edge (self, id1, id2, weight):
        
        found_edge_ele = None 
        
        if id1 in self.vertices and id2 in self.vertices:
            
            # check if edge exists 
            
            for i in  range(len(self.edge_list)):
                if self.edge_list[i][0:2] == [id1, id2] :
                    found_edge_ele = self.edge_list[i]
                    break 
            
        # change weight
        if found_edge_ele:
            found_edge_ele[2] = weight
        else: 
            self.edge_list.append([id1, id2, weight])

    
    def remove_edges (self, node_id):
        walk = 0 

        while walk < len(self.edge_list):
            if node_id in self.edge_list[walk][0 : 2]:
                self.edge_list = self.edge_list[0 : walk] +  self.edge_list[walk + 1 : :]
            else:
                walk += 1

    def remove_edge (self, node_id1, node_id2):
        walk = 0 

        while walk < len(self.edge_list):
            if [node_id1, node_id2]  ==  self.edge_list[walk][0 : 2]:
                self.edge_list = self.edge_list[0 : walk] +  self.edge_list[walk + 1 : :]
                return True 
            else:
                walk += 1
        return False 
    
    def get_edge_value (self,node_id1, node_id2):
        walk = 0 

        while walk < len(self.edge_list):
            if [node_id1, node_id2]  ==  self.edge_list[walk][0 : 2]:
                return self.edge_list[walk][2]
            else:
                walk += 1
        return None 
    
    def set_edge_value (self, node1_id, node2_id, weight):
        walk = 0 

        while walk < len(self.edge_list):
            if [node1_id, node2_id]  ==  self.edge_list[walk][0 : 2]:
                self.edge_list[walk][2] = weight
                return True 
            walk += 1
        return False 
    
    def adjacent(self, node_id1, node_id2):
        for edge_info in self.edge_list:
            if edge_info[0:2] == [node_id1, node_id2]:
                return True 
            
        return False 
    
    def neighbors (self, node_id):
        list_of_neighbor_nodes_id = []

        for edge_info in self.edge_list:
            if node_id == edge_info[0] :
                list_of_neighbor_nodes_id.append(node_id)
        
        return list_of_neighbor_nodes_id 
    
el_graph = ELGraph()

node1 = el_graph.add_vertex('a')
node2 = el_graph.add_vertex('b')

el_graph.add_edge(node1, node2, 0.50)
print(el_graph.get_edge_value(node1, node2))    
print(el_graph.set_edge_value(node1, node2, 10))     
print(el_graph.get_edge_value(node1, node2))    


# Adjacency Map 

# map structure


# [
    
#     [
#         [0, 'A'],             # id , value
        
#         [[0, 0], [1, 0]] ,    # [to_id, edge value]
    
#     ], 
        
#     [
#             [1, 'B'], 
            
#             [[0, 0], [1, 0]]
                                      
#     ]
    
# ]

class AMGraph:
    def __init__(self):
        self.map = [] 

    def add_vertex(self, value):
        idx = -1 

        for i in range(len(self.map) - 1):
            current_id = self.map[i][0]
            next_id = self.map[i + 1][0]

            if current_id + 1 != next_id:
                idx = current_id + 1
                break 
        
        if idx == -1:
            idx = len(self.map)    

        self.map.append( [ [idx, value],  [] ] )  

        for i in range(len(self.map)):
            target_node_id = self.map[i][0][0]
            self.map[-1][1].append([target_node_id, 0]) # [  [id1, value], [ [id0, w10], [id1, w11 ]  ] 
            
            # check previous nodes, weight or zero weight value connection to new added node is required 

            for k in range(len(self.map) - 1):
                idx_ = -1 
                for map_info in self.map[k][1]:
                    if map_info[0] == idx:
                        idx_ = idx
                if idx_ == -1:
                    self.map[k][1].append( [ idx, 0] )
        return idx 

    def remove_vertex(self, node_id):
        bool_state = False  
      # remove node 
        for i in range(len(self.map)):
            if self.map[i][0][0] == node_id:
                self.map.pop(i)
                bool_state = True 
                break

     # remove connections on other node 
        
        for i in range(len(self.map)):
            
            arr = self.map[i][1]

            for k in  range(len(arr)):
                if node_id  == arr[k][0]:
                    arr.pop(k)
                    break 
        
        return bool_state 
    
    def get_vertex_value(self, id):
        for node_map_section in self.map:
            if node_map_section[0][0] == id:
                return node_map_section[0][1]
   
        return False 
    
    def set_vertex_value(self, id, value):
        for node_map_section in self.map:
            if node_map_section[0][0] == id:
                node_map_section[0][1] = value
                return True 
        return False 

    def add_edge (self, id1, id2, value):
        for node_map_section in self.map:
            for rx_node in node_map_section[1]:
                if node_map_section[0][0] == id1 and rx_node[0] == id2:
                    rx_node[1] = value 
                    return True 
        return  False 
    
    def remove_edges (self, node_id):
        count_removes = 0 
        for node_map_section in self.map:
            for rx_node in node_map_section[1]:
                if node_map_section[0][0] == node_id or rx_node[0] == node_id:
                    rx_node[1] = 0
                    count_removes += 1
        return count_removes > 0 
    
    def remove_edge(self, node1_id, node2_id):
        for node_map_section in self.map:
            for rx_node in node_map_section[1]:
                if node_map_section[0][0] == node1_id or rx_node[0] == node2_id:
                    rx_node[1] = 0    
    
    def adjacent (self, node1_id, node2_id):
        for node_map_section in self.map:
            for rx_node in node_map_section[1]:
                if node_map_section[0][0] == node1_id or rx_node[0] == node2_id:
                    return True 
        return False 
    
    def neighbors (self, node_id):
        result = [] 
        for node_map_section in self.map:
                if node_map_section[0][0] == node_id:
                    for neighbor_info in node_map_section[1] :
                        if neighbor_info[0] != node_id:
                            result.append(neighbor_info[0])
        return result 
    

am_graph = AMGraph()
node1 = am_graph.add_vertex('A')
node2 = am_graph.add_vertex('B')

# am_graph.remove_vertex(node1)
# am_graph.remove_vertex(node1)
print(  am_graph.get_vertex_value(node1) )
am_graph.set_vertex_value(node1, 'T')
am_graph.add_edge(node1, node2, 22)
print(am_graph.map)
print(am_graph.neighbors(node1))

class ALGraph:
    
    def __init__(self):
        self.list = []
        self.nodes = []

    def add_vertex (self, value):
        idx = -1 

        # search for available slot in list 
        for i in range(len(self.list) ):
            if self.list[i] == None:
                idx = i
                break 
            
        # dynamically grow allocated array 
        if idx == -1:
            idx = len(self.list)
            self.list.append([])
            self.nodes.append(value)

        # use available slot 
        else:
            self.list[idx] = [] 
            self.nodes[idx] = value
        
        return idx 
    
    def remove_vertex(self, node_id):
        if node_id < len(self.list):
            if self.list[node_id] != None :
                self.list[node_id] = None 
                self.nodes[node_id] = None 
                return True
        return False 

    def get_vertex_value (self, node_id):
        if node_id < len(self.list):
            if self.list[node_id] != None:
                return self.nodes[node_id]
        return None 
    
    def set_vertex_value (self, node_id, value):
        if node_id < len(self.list):
            if self.list[node_id] != None:
                self.nodes[node_id] = value
        return None 
    
    def add_edge (self, id1, id2, value = 0):
        if id1 < len(self.list) and id2 < len(self.list):
            if self.list[id1] != None and self.list[id2] != None:
                found_edge = -1
                for edge_info in self.list[id1]:
                    if edge_info[0] == id2:
                        found_edge = 1
                if found_edge == -1:
                    self.list[id1].append([id2,value  ])   # [id, edge_weight]
                    return True 
                
        return False 

    def remove_edges(self, node_id):
        if node_id < len(self.list):
            if self.list[node_id] != None:
                self.list[node_id].clear()
    
    def remove_edge (self, node1_id, node2_id):
        if node1_id < len(self.list) and node2_id < len(self.list):
            if self.list[node1_id] != None  and self.list[node2_id] != None:
                walk = 0
                while walk < len(self.list[node1_id]):              
                    if self.list[node1_id][walk][0] == node2_id: # [id *, edge_weight]
                        self.list[node1_id].pop(walk)
                        return True 
                    else:
                        walk += 1
        return False 
    

    def get_edge_value (self, node1_id, node2_id ) :
        if node1_id < len(self.list) and node2_id < len(self.list):
            if self.list[node1_id] != None  and self.list[node2_id] != None:
                idx = -1
                for i in range(len(self.list[node1_id])):
                    if self.list[node1_id][i][0] == node2_id:
                        return self.list[node1_id][i][1]
        return None  
    
    def set_edge_value (self, node1_id, node2_id, value ) :
        if node1_id < len(self.list) and node2_id < len(self.list):
            if self.list[node1_id] != None  and self.list[node2_id] != None:
                idx = -1
                for i in range(len(self.list[node1_id])):
                    if self.list[node1_id][i][0] == node2_id:
                         self.list[node1_id][i][1] = value
                         return True 
        return None  
    
    def adjacent(self, node1_id, node2_id):
        if node1_id < len(self.list) and node2_id < len(self.list):
            if self.list[node1_id] != None  and self.list[node2_id] != None:
                for edge_info in self.list[node1_id]:
                    if edge_info[0] == node2_id:
                        return True
        return None       

    
    def neighbors(self, node1_id):
        result = [] 
        if node1_id < len(self.list) :
            if self.list[node1_id] != None :
                for edge_info in self.list[node1_id]:
                    result.append(edge_info[0] )
        return result 
    
# al_graph = ALGraph()
# node1 = al_graph.add_vertex('A')
# node2 = al_graph.add_vertex('B')
# print(node1, node2)

# print(al_graph.get_vertex_value(node2))
# print(al_graph.add_edge(node1, node2))
# # print(al_graph.remove_edge(node1, node2))
# print( al_graph.get_edge_value(node1, node2) )
# print( al_graph.neighbors(node1) )
# print(al_graph.list)


# SIMPLE SOCIAL MEDIA 

print('social media')
al_graph = ALGraph() 
graph = ALGraph()
hector_id = graph.add_vertex('Hector')
sam_id = graph.add_vertex('Sam')

# friend hector -> Sam 
graph.add_edge(hector_id, sam_id, 1)
graph.add_edge(sam_id, hector_id, 1)
print('hector id: {}\t sam_id: {} '.format(hector_id, sam_id))
print(graph.list)

# friend sam -> Penny
penny_id = graph.add_vertex('Penny')
graph.add_edge(sam_id, penny_id, 1)
graph.add_edge(penny_id, sam_id, 1)
print('hector id: {}\t sam_id: {} \t penny id: {}'.format(hector_id, sam_id, penny_id))
print(graph.list)

# [
#         [
#             # hector -> sam 1 distance
#             [1, 1]
#         ],   
        
#         [
#             # sam -> hector 1 distance
#             [0, 1], 

#             # sam -> penny 1 distance
#             [2, 1]
#         ],   
        
#         [
#             # penny -> sam distance 
#             [1, 1]
#         ]
# ]

# distance map 
# hector  sam  penny 
#    <------>
#      1
#   <------------->
#         2
#

def someone_on_the_inside(algraph :ALGraph, my_id, employee_ids):
    friends_at_company = []
    # my id's connections 
    my_walk_info_list = graph.list[my_id]

    for my_walk_info in my_walk_info_list:
      
        for employee_id in employee_ids:
            # my connection (friend)   # company id
            if my_walk_info[0] == employee_id:
                friends_at_company.append(employee_id)

    return list(map(lambda node_id : algraph.nodes[node_id] , friends_at_company))

my_id = hector_id 
uber_employee_ids = [sam_id, penny_id]
print('{} -> {}'.format('friends at uber', someone_on_the_inside(graph, my_id, uber_employee_ids )))   # friends at UBER  -> ['Sam'] 


# DEPTH FIRST SEARCH  
def vertex_is_reachable_helper_dfs(algraph: ALGraph, id1, id2):
    class search_node:
        def __init__(self, possible_routes = []):
            self.path = [] 
            self.possible_routes = possible_routes 

    # does id1 and id2 exist in graph?
    if id1 < len(algraph.nodes):
        if algraph.nodes[id1] == None:
            return []
    
    if id2 < len(algraph.nodes):
        if algraph.nodes[id2] == None:
            return []
    
    if id2 < id1 :
        index_range = list(range(id1, id2 - 1, -1))
    else :
        index_range = list(range(id1, id2 + 1, 1))
    
    queue = [ search_node(index_range ) ]
    paths = []

    while queue:

        node = queue.pop(0) 

        if not node.possible_routes:
            if node.path and node.path[-1] == id2:
                paths.append(node.path)

        else :

            # walk to next path 
            curr_id = node.possible_routes.pop(0)
            path = node.path + [curr_id]
            possible_routes = []
            
            ## add visited or prev state with reduced number of possible routes back into queue 
            queue.insert(0, node)
            
            ## does the node exist
            if algraph.nodes[curr_id]:

                for route_info in algraph.list[curr_id] :
                    next_id = route_info[0]
                    if next_id not in node.path:
                        possible_routes.append(next_id)
                    else:
                        # revisited ids  :( 
                        pass 
                
                new_node = search_node(possible_routes)
                new_node.path = path

                #update indices 
                queue.insert(0, new_node)
    
    return paths 

def vertex_is_reachable(algraph: ALGraph, id1, id2):
    paths  = vertex_is_reachable_helper_dfs(algraph, id1, id2)
    
    if paths:
        return len(paths) > 0
    return False 

def all_paths(algraph: ALGraph, id1, id2):
    return vertex_is_reachable_helper_dfs(algraph, id1, id2)  #  SOLUTION [[0, 2], [0, 1, 2]]

print('paths to {} --> {}'.format(penny_id, all_paths(graph, hector_id, penny_id)))

