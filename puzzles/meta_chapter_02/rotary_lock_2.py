from typing import List
# Write any import statements here

def getMinCodeEntryTime(N: int, M: int, C: List[int]) -> int:
    q = [ {'lock_1':1, 'lock_2':1, 'seconds': 0, 'index': -1} ] 
    result_min_second = N

    while q:
        record = q.pop(0)
        lock_1 = record['lock_1']
        lock_2 = record['lock_2']
        index = record['index']
        seconds = record['seconds']
        
        next_index = index + 1
        
        if  next_index == M and seconds < result_min_second:
            result_min_second = seconds

        if next_index < M:

            next_lock_value = C[next_index]

            dist_1_ccw_forward = abs(lock_1 - next_lock_value)
            dist_1_cc_back = N - dist_1_ccw_forward
        
            dist_2_ccw_forward = abs(lock_2 - next_lock_value)
            dist_2_cc_back = N - dist_2_ccw_forward
            
            # find lock with shortest distance both  lock
            shortest_dis_lock_1 = dist_1_ccw_forward if dist_1_ccw_forward < dist_1_cc_back else dist_1_cc_back
            shortest_dist_lock_2 = dist_2_ccw_forward if dist_2_ccw_forward < dist_2_cc_back else dist_2_cc_back

            if next_lock_value == lock_1 and next_lock_value == lock_2:
                # no change in position 
                q.append({'lock_1':next_lock_value, 'lock_2':next_lock_value, 'seconds': seconds, 'index': next_index } )
            elif  lock_1 == lock_2:
                # set either lock with shortest distance (use lock 1)
                q.append({'lock_1': next_lock_value, 'lock_2': lock_2, 'seconds': seconds  +  shortest_dis_lock_1, 'index': next_index } )
            elif lock_1 != lock_2:
                # either lock1 or lock2 could change 
                q.append({'lock_1': next_lock_value, 'lock_2': lock_2, 'seconds': seconds  +  shortest_dis_lock_1, 'index': next_index  } )
                q.append({'lock_1': lock_1, 'lock_2': next_lock_value, 'seconds': seconds  +  shortest_dist_lock_2, 'index': next_index  } )
        
    return result_min_second