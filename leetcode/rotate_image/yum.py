class Solution:
    def rotate(self, matrix: List[List[int]]) -> None:
        """
        Do not return anything, modify matrix in-place instead.
        """

        if not matrix:
            return matrix 
        
        if len(matrix[0]) == 1:
            return matrix

        n = len(matrix[0])
        
        dir_list = [[0, 1], [1, 0], [0, -1], [-1, 0]]  # r d l u

        p = [0, 0] # top left 

        # corners
        top_left = [0, 0]
        top_right = [0, n - 1]
        bottom_left = [n-1, 0]
        bottom_right = [n-1, n-1]
        
        bounds = [0, n-1] # bounds per rotation space 
        dir_sel = 0 # select direction to move and swap data
        init = p + [] # start cell
        tmp = matrix[p[0]][p[1]] 

        while 1:
            
            # number of clockwise rotations 
            for i in range(bounds[1] - bounds[0]):
                
                print("start", p)

                #inner rotation
                while 1:
                
                    # move block  
                    offsets = dir_list[dir_sel]
            
                    #eval move 
                    valid_row_move = p[0] + offsets[0] >= bounds[0] and p[0] + offsets[0] <= bounds[1] 
                    valid_col_move = p[1] + offsets[1] >= bounds[0] and p[1] + offsets[1] <= bounds[1] 
            
                    # valid move 
                    if (valid_row_move & valid_col_move):
                        p[0] = p[0] + offsets[0]
                        p[1] = p[1] + offsets[1]
                        
                    else:
                        # change direction 
                        dir_sel += 1
                        continue
                    # swap 
                    tmp, matrix[p[0]][p[1]] =  matrix[p[0]][p[1]], tmp
                    
                    # returned to start position 
                    if p[0] == init[0] and p[1] == init[1]:
                        print("back to start")
                        break 
                
                print(matrix)
                # reset this inner rotation routine 
                dir_sel = 0
                p = init + p
                # init = 
                tmp = matrix[p[0]][p[1]] 
                
            #sink 
            top_left = [top_left[0] + 1, top_left[1] + 1 ] # right down diagonal
            top_right = [top_right[0] + 1, top_right[1] - 1 ] # left down diagonal
            bottom_left = [bottom_left[0] -1, bottom_left[1] + 1 ] # left bottom  diagonal
            bottom_right = [bottom_right[0] -1, bottom_right[1] -1  ] # right bottom diagonal
            
            # set new boards 
            min_value = 2**32 # dummy large value 
            max_value = 0
            for b in top_left + top_right + bottom_left + bottom_right:
                if b < min_value:
                    min_value = b 
                if b > max_value :
                    max_value = b 
            bounds = [min_value, max_value]
            print('bounds', bounds)
            
            # new init position  
            p = top_left + [] 
            
            # new init
            init = p + [] 
            
            # read init cell value 
            tmp = matrix[p[0]][p[1]]
            
            #reset dir_sel
            dir_sel = 0
            
            # eval inner focused board ( bottom diagonal cannot be less than or equal to top diaginal)
            if (bottom_left[0] <= top_right[0]): 
                break
        
        return matrix


