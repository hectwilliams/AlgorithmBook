class HashMap:
    
    def __init__(self, capacity = 50):
        self.capacity = capacity
        self.table = [None] * capacity
        print(self.table)   
    
    def add(self, key, val):
        count = 0 
        for c in key:
            count += ord(c)
        
        if self.table [count % self.capacity] == None:
            self.table [count % self.capacity]  = [ [key, val] ]
        else:
            if [key. val] not in self.table [count % self.capacity]:
                self.table [count % self.capacity].append([key, val])

    def is_empty(self):
        count = 0
        for ele in self.table:
            count += ele == None 
        return count ==  self.capacity 

    def find(self, key):
        count = 0
        for c in key:
            count += ord(c)
        
        table_value = self.table[ count % self.capacity ]

        if table_value == None :
            return None
        else:
            for arr_ele in table_value:
                if  arr_ele[0] == key:
                    return arr_ele[1]
            
    def remove(self, key):
        count = 0
        for c in key:
            count += ord(c)
        
        table_value = self.table[ count % self.capacity ]
        if table_value == None:
            return None 
        else:
            idx = 0
            for i in range(len(table_value)):
                if table_value[i][0] == key:
                    idx == i
            key_value = table_value[idx]

            table_value.pop(idx)  #  = table_value[0 : idx] + table_value[idx + 1 : :]

            if not table_value:
                self.table[count % self.capacity]  = None 
                
            return key_value
        
hash = HashMap() 
hash.add('abc', 43)
print(hash.table)
print(hash.find('abc'))
print(hash.remove('abc'))
print(hash.remove('abc'))


        