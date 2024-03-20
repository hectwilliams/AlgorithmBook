from typing import List
# Write any import statements here

def is_valid(discs, new_top_disc):
    if new_top_disc <= 0:
        return False 
    
    
    if len(discs) > 0 and new_top_disc >= discs[0]:
        return False 
    

    
    return True 
    
def getMinimumSecondsRequired(N: int, R: List[int], A: int, B: int) -> int:

    min_seconds = 10**9
    start_record = {
        'prev_disc': 0,
        'position': N - 1,
        'seconds': 0,
        'path' : [],
        'delta_info': []
    }
    a = 0
    b = 0
    q = [start_record]

    while q:
        record = q.pop(0)
        current_position = record['position']
        seconds = record['seconds']
        # stack_size = len(current_stack)
        prev_disc = record['prev_disc']
        path = record['path']
        delta_info = record['delta_info']

        max_radius = R[current_position]
        next_move_buffer = []

        # print(record, '\t', R)

        
        if current_position == -1:

            if seconds < min_seconds:

                min_seconds = seconds
        else:

            for i in range( current_position + 1 ):

                value = R[i]

                if value > max_radius:

                    max_radius = value 
                
                # if i >= current_position and i < stack_size - 1:
                #     if R[i] >= R[i + 1]:
                #         continue 
                    
            current_disc = R[current_position]
            next_position = current_position - 1
    
            # inflate disc to largest possible size in stack region

            if max_radius >= current_disc:
                delta = abs(max_radius - current_disc)
                a = delta * A
                next_move_buffer.append( (a, max_radius, ['a', delta]) )

            # decrement current disc radius
                
            b = B 
            next_move_buffer.append( (b, current_disc  - 1, ['a', 1]) )

            # increment current disc radius 

            a = A 
            next_move_buffer.append( (a, current_disc  + 1, ['a', 1]) )
            
            # no op  
            next_move_buffer.append( (0, current_disc , ['', 0]) )
            
            # decrement prev disc value 

            if path:
                
                prev_disc = path[0]
                next_disc = prev_disc - 1
                delta = (current_disc - next_disc)
                if  delta >= 0:
                    b = delta * B 
                    next_move_buffer.append( (b, next_disc, ['b', delta]) )

            # set to max possible length in sub-stack (i.e. segment of stack)
                
            length = current_position + 1
            
            delta = abs( length - current_disc ) 

            if length > current_disc:
            
                a = delta * A
            
                next_move_buffer.append( (a, length,  ['a', delta] ) )

            else:
                
                b = delta * B
                
                next_move_buffer.append( (b, length ,  ['b', delta] ) )

          

            # sort 
            next_move_buffer.sort(key=lambda tup: tup[0])

            # possible paths 
            while next_move_buffer:

                tuple_next_move_data = next_move_buffer.pop(0)
                
                sec = tuple_next_move_data[0]

                new_disc_size = tuple_next_move_data[1]

                update_code = tuple_next_move_data[2]

                if is_valid(path, new_disc_size ):

                    q.append( {'prev_disc': current_disc , 'position': next_position, 'seconds' : seconds + sec , 'path' : [new_disc_size] + path , 'delta_info':  [update_code] +  delta_info  } )
                
    return min_seconds

N = 5
R = [2, 5, 3, 6, 5]
A = 1
B = 1

answer = getMinimumSecondsRequired(N,R,A,B)
print('answer -->\t', answer)

N = 3
R = [100, 100, 100]
A = 2
B = 3
answer = getMinimumSecondsRequired(N,R,A,B)
print('answer -->\t', answer)

N = 3
R = [100, 100, 100]
A = 7
B = 3
answer = getMinimumSecondsRequired(N,R,A,B)
print('answer -->\t', answer)


N = 4
R = [6, 5, 4, 3]
A = 10
B = 1
answer = getMinimumSecondsRequired(N,R,A,B)
print('answer -->\t', answer)


N = 4
R = [100, 100, 1, 1]
A = 2
B = 1
answer = getMinimumSecondsRequired(N,R,A,B)
print('answer -->\t', answer)

N = 6
R = [6, 5, 2, 4, 4, 7]
A = 1
B = 1
answer = getMinimumSecondsRequired(N,R,A,B)
print('answer -->\t', answer)
