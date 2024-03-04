from typing import List
# Write any import statements here

def getSecondsRequired(N: int, F: int, P: List[int]) -> int:
  
    P.sort() 

    seconds = 0

    # pack all frogs together (link)

    walk = len(P) - 1 # walking backwards btw 

    while walk > 0:
        walk  -= 1
        
        curr_frog_i = P[walk + 1] # immediate frog in front 
        next_frog_i = P[walk ]
        distance = curr_frog_i - next_frog_i 
        
        if distance > 1:
            # shift frog to lily directly behind lead_frog 
            seconds += distance - 1
            frog_shift_pos = next_frog_i + seconds
            P[walk] = frog_shift_pos

    # move packed frogs to end ( formula based)
    front_frog_i = P[-1]
    end_frog_i = P[0]
    num_of_frogs = front_frog_i - end_frog_i + 1
    lilys_in_front_of_pack =  N  - front_frog_i 

    secs_packed_shift = lilys_in_front_of_pack + (num_of_frogs - 1)

    # print("number of frongs \t {} ".format (num_of_frogs))

    # print("lilly in front of line list of frogs  \t {} ".format (lilys_in_front_of_pack))

    seconds += secs_packed_shift

    return seconds
