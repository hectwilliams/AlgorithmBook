
from typing import List
# Write any import statements here
import sys 

def getSecondsRequired(R: int, C: int, G: List[List[str]]) -> int:
   # Write your code here
  
    q = []
    portal_table = {}
    lowest_distance = sys.maxsize # system dependant 

    for r in range(len(G)):
        for c in range(len(G[r])):

            character = G[r][c][0]            
            
            if character == "S":
                q.append ( { 'curr_cell' : (r,c), 'seconds': 0, 'previous_cells': [], 'prev_character': '' } )
            
            if ord(character) >= 97 and ord(character) <= 122:

                if character not in portal_table:
                    portal_table[character] = []
                
                portal_table[character].append((r,c))
    

    while q:
        
        record = q.pop(0)
        curr_cell = record['curr_cell']
        seconds = record['seconds']
        previous_cells = record['previous_cells']
        prev_character = record['prev_character']

        r = curr_cell[0]
        c = curr_cell[1]
        


        if curr_cell not in previous_cells and (r >= 0 and r  < R) and (c >= 0 and c  < C)  and prev_character != "#" :
            
            character = G[r][c][0]

            # exit found 
            if character == "E":
                lowest_distance = seconds if seconds < lowest_distance else lowest_distance
            
            # jump portal 
            if character in portal_table:
                
                for r_c_tuple in portal_table[character]:
                    q.append({ 'curr_cell' : r_c_tuple, 'seconds': seconds + 1, 'previous_cells': previous_cells + [curr_cell], 'prev_character': character })
            
            # adjacent move 
            
            # move up 
            q.append({ 'curr_cell' : (r + 1, c) , 'seconds': seconds + 1, 'previous_cells': previous_cells + [curr_cell] , 'prev_character': character})

            # move down
            q.append({ 'curr_cell' : (r - 1, c), 'seconds': seconds + 1, 'previous_cells': previous_cells + [curr_cell], 'prev_character': character })

            # move left
            q.append({ 'curr_cell' : (r, c - 1), 'seconds': seconds + 1, 'previous_cells': previous_cells + [curr_cell] , 'prev_character': character})

            # move right 
            q.append({ 'curr_cell' : (r, c + 1), 'seconds': seconds + 1, 'previous_cells': previous_cells + [curr_cell] , 'prev_character': character})

    return -1 if lowest_distance == sys.maxsize else lowest_distance