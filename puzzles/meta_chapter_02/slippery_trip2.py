from typing import List
# Write any import statements here

def row_check(grid, pos, R, C, dir) :

    '''
        Test row for certain markers

        1) >v ( right search)

        2) v< (left search)

        3) * 

        measure number of circle in between marker 

        measure max number of circle found consecutively

    '''
    
    row = pos[0]
    col = pos[1]

    store = { 
        'max_path_to_tunnel': 0,
        'has_tunnel': False, 
        'has_empty_cell': False, 
        'has_circle': False, 
        'right' : { 'balanced': {'count': 0}, 'arrow': {}, 'stack': []}, 
        'left' : { 'balanced': {'count': 0},  'arrow': {}, 'stack': []}, 
        'infinite': {'left': 0, 'right': 0}
    }

    new_dir = ''
    
    circles_in_row = 0

    # loop twice around a row in both directions ( search for balanced string)
    for k in range(0, C*2 ):

        # walk start positions
        walk_r_ = (row, 1 )
        walk_l_ = (row , C)

        walk_l_ = (  row , walk_l_[1]  - k )
        if  walk_l_[1]  < 1:
            val = C - (abs ( walk_l_[1]  ) % C)
            walk_l_ = (row, val)        

        walk_r_ = (  row , walk_r_[1]  + k )
        if walk_r_[1] > C:
            val = (walk_r_[1] % C) 
            if val == 0:
                val = C
            walk_r_ = (row, val)

        row_r = walk_r_[0]
        col_r = walk_r_[1]
        row_l = walk_l_[0]
        col_l = walk_l_[1]

        # get cell character 
        walk_r_ch = grid[ row_r - 1][ col_r - 1]
        walk_l_ch = grid[row_l - 1][col_l - 1]

        # found a circle in the row 
        if (walk_r_ch =='*' or walk_l_ch =='*') and (circles_in_row == 0) :
            circles_in_row = 1

        # right test
        if walk_r_ch =='>':
            
            if  col_r not in store['right']['arrow'] :
                store['right']['arrow'][col_r] = True  
                store['right']['stack'].append([col_r, 0, '>', ''])
            else:
                store['right']['arrow'][col_r] = False   # stop from counting circles in this direction 
            
        elif walk_r_ch == '<':

            if store['right']['stack']:
                store['right']['balanced'] = {'>': store['right']['stack'][-1][0] , '<': col_r, 'count': store['right']['stack'][-1][1] }
                # balanced string sequence found (traverse will ping pong on row)
                # store['right']['stack'] = [] 

        elif walk_r_ch == '*':
            
            store['has_circle'] = True 
            
            for data in store['right']['stack'] :
                column = data[0]
                if store['right']['arrow'][column]:
                    data[1] += 1
                    coin_count_in_path = data[1]
                    if store['infinite']['right'] < coin_count_in_path:
                        store['infinite']['right'] = coin_count_in_path
            
        elif walk_r_ch == 'v':
            
            store['has_tunnel'] = True 

            if store['right']['stack']:
                new_dir = 'v'
                
                count = store['right']['stack'][-1][1]
                if count > store['max_path_to_tunnel']:
                    store['max_path_to_tunnel'] = count 
                
                store['right']['stack'].clear()
        
        elif walk_r_ch == '.':
            store['has_empty_cell'] = True 


        # left test 
        if walk_l_ch == '<':

                
            if  col_l not in store['left']['arrow'] :
                store['left']['arrow'][col_l] = True  
                store['left']['stack'].append([col_l, 0, '<', ''])
            else:
                store['left']['arrow'][col_l] = False   # stop from counting circles in this direction 
            

        elif walk_l_ch == '>':

            if store['left']['stack']:
                store['left']['balanced'] = {'<': store['left']['stack'][-1][0] , '>': col_l, 'count': store['left']['stack'][-1][1] }
                # balanced string sequence found (traverse will ping pong on row)
                # store['left']['stack'] = [] 

        elif walk_l_ch == '*':
            
            store['has_circle'] = True 

            #increment coin count in all directed paths pointed left 
            for data in store['left']['stack'] :
                column = data[0]
                # add if first full sweep across row 
                if store['left']['arrow'][column]: # okay to count coin
                    data[1] += 1    #incr
                    coin_count_in_path = data[1]
                    # store max poissible coin count in this direction
                    if store['infinite']['left'] < coin_count_in_path:
                        store['infinite']['left'] = coin_count_in_path

        elif walk_l_ch == 'v':
            
            store['has_tunnel'] = True 

            if store['left']['stack']:
                new_dir = 'v'
                count = store['stack'][-1][1]
                if count > store['max_path_to_tunnel']:
                    store['max_path_to_tunnel'] = count 
                store['left']['stack'].clear()

    # print(store, new_dir )

    
    # move down marker found ( with arrow(s) )
    if new_dir == 'v' and  (store['max_path_to_tunnel'] ):
        return store['max_path_to_tunnel'] , 'v'
    
    # circle not found in row, but a door exists
    if not store['has_circle'] :

        if not store['has_empty_cell'] and not store['has_tunnel'] :
            return 0, 'end'
        
        if store['has_empty_cell']:
            return 0, 'v' if row < R else 'end'
        
        if store['has_tunnel']:
            return 0, 'v' if row < R else 'end'
        
    if store['has_circle']:
        if row < R:
            return 1, 'v'
        
        else:
            max_count_test = 0 

            #     # balanced amount > <
            right_balanced_count = store['right']['balanced']['count']
            left_balanced_count = store['left']['balanced']['count']

            # infinite direction 
            inf_right = store['infinite']['right']
            inf_left = store['infinite']['left']

            if inf_right or inf_left:
                if inf_right > inf_left:
                    return inf_right, 'end'
                else:
                    return inf_left, 'end'

            max_count_test = max (  [inf_left, inf_right , left_balanced_count, right_balanced_count, 1]   )
            
            return max_count_test, 'end'
        
    # # move down marker not found but, row has coin  
    # if not store['has_tunnel'] :
    #     row < R and store['has_circle']:
    #     return 1, 'v'


def getMaxCollectableCoins(R: int, C: int, G: List[List[str]]) -> int:
    count = 0
    dir = 'v'
    dir_code  = 'v'
    pos = (1,1)
    
    while dir_code == 'v':
        row_count, dir_code = row_check(G, pos , R, C, dir)
        # print(' row_count = {} \t {}'.format(row_count, dir_code))
        count +=  row_count
        pos = (pos[0] + 1, pos[1])  
        # print(count, pos, dir_code)
    return count if dir_code == 'end' else 0


R = 3
C = 4
G = [['.','*','*','*'],
    ['*','*','v','>'],
    ['.','*','.','.']]

answer = getMaxCollectableCoins(R, C, G)
print(answer)



R = 3
C = 3
G = [[ '>','*','*' ],
    ['*','>','*' ],
    ['*','*','>']]
answer = getMaxCollectableCoins(R, C, G)
print(answer)

R = 2
C = 2
G = [['>','>'],
    ['*','*']]

answer = getMaxCollectableCoins(R, C, G)
print(answer)


R = 4
C = 6
G = [
    [ '>','*','v','*','>','*'],
    ['*','v','*','v','>','*'],
    ['.','*','>','.','.','*'],
    ['.','*','.','.','*','v']
]
answer = getMaxCollectableCoins(R, C, G)
print(answer)
