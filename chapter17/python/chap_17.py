# Edge List Implementation 

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
