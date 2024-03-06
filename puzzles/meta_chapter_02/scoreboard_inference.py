from typing import List
from math import floor , ceil

# Write any import statements here

def inner_join( str1: str, str2: str ):
    ''' 
        a merge of strings 
    '''

    result = ''
    walk = 0
    ss1 = str1
    ss2 = str2

    while walk <  len(str1):
        ch1 = str1[walk]
        index = str2.find(ch1)
        if index != -1:
            # add nerge like characters to result
            result += ch1
            # remove character from str1
            str1 = str1[ : walk] + str1[ walk + 1 :  ]
            # remove character from str2
            str2 = str2[ : index] + str2[ index + 1 :  ]
        else:
            walk += 1
    result = list(str1 + str2 + result )
    result.sort() 
    result = ''.join(result)

    print(ss1, ss2, 'args', result)

    return result     

def getMinProblemCount(N: int, S: List[int]) -> int:

    events = [('',0 )]
    result = None 
    S.sort() 

    for total_score in S:
        local_events = []

        print('SCORE' , total_score)

        for point in range(1, 4):
            if point <= total_score:
                raw = total_score / point 

                whole = floor(raw)

                remainder = (raw - whole) 

                encode_points = str(point) * whole

                encode_other_point = '' if remainder == 0 else str( ceil(point * remainder) )

                encode_info = encode_points + encode_other_point 

                # add possibility for this final score                
                local_events.append( (encode_info, len(encode_info)) )

        # inner join older possible points scores with newer points
        for _ in range(len(events)):
            prior_score_record = events.pop(0)
            
            for latter_score_record in local_events:
                merged_info = inner_join(prior_score_record[0], latter_score_record[0]) 
                events.append((merged_info, len(merged_info)))
        
        # add local events to events
        # events += local_events
        min_point = min(p for _, p in events)
        print(events, '\t', 'min', min_point)
        result = min_point
        # keep score potentials with lowest length 
        walk = 0
        while walk < len(events):
            if events[walk][1] > min_point:
                print('REMOVED', events[walk])
                events.pop(walk)
            else:
                walk += 1
        print(events, '\n------------')
    return result 

N = 5
S = [1, 2, 3, 4, 5]
answer = getMinProblemCount(N, S)
print('getMinProblemCount({}, {}) = {}', N, S, answer)

# N = 4
# S = [2, 4, 6, 8]
# answer = getMinProblemCount(N, S)
# print('getMinProblemCount({}, {}) = {}', N, S, answer)

# N = 4
# S = [4, 3, 3, 4]
# answer = getMinProblemCount(N, S)
# print('getMinProblemCount({}, {}) = {}', N, S, answer)

# N = 1
# S = [8]
# answer = getMinProblemCount(N, S)
# print('getMinProblemCount({}, {}) = {}', N, S, answer)