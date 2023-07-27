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

    def add_edge (self, id1, id2, weight):
        
        if id1 in self.vertices and id2 in self.vertices:
            found_edge_ele = None 
            
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