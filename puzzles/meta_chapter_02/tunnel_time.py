from typing import List 
from math import floor 
def getSecondsElapsed(C: int, N: int, A: List[int], B: List[int], K: int) -> int:

    p = list(zip(A,B)) 
    p.sort(key=lambda item: item[0])
    
    total_tracks_per_track = sum([end - begin for begin, end in p ])

    # find row or number of times train completes a cycle 
    raw = K / total_tracks_per_track 
    revolutions = floor( raw )
    seconds = revolutions * C
    track_metres_pending = K - revolutions * total_tracks_per_track

    # compute contigious or non contigious number of tracks 
    q = [{'start': 0, 'end': 0, 'prev_untrack': 0, 'track_metres_pending': track_metres_pending , 'seconds': seconds}]

    while q:
        record = q.pop(0)
        # print(record)
        prev_tunnel_start = record['start']
        prev_tunnel_end = record['end']
        prev_untrack = record['prev_untrack']
        track_metres_pending = record['track_metres_pending']
        seconds = record['seconds']

        if track_metres_pending > 0 :
            delta_track = prev_tunnel_end - prev_tunnel_start
            seconds += prev_untrack
            tunnel = p.pop(0)
            next_tunnel_start = tunnel[0]
            next_tunnel_end = tunnel[1]

            if track_metres_pending >= delta_track:
                track_metres_pending = track_metres_pending - delta_track 
                seconds += delta_track
            else:
                seconds += track_metres_pending  # add track segments occupied
                track_metres_pending = 0
            
            q.append({'start': next_tunnel_start, 'end': next_tunnel_end, 'prev_untrack': next_tunnel_start - prev_tunnel_end , 'track_metres_pending':track_metres_pending  , 'seconds': seconds })

    return seconds 

C = 10
N = 2
A = [1, 6]
B = [3, 7]
K = 7
answer = getSecondsElapsed(C, N,A,B, K)
print(' getSecondsElapsed({},{},{},{},{}) => \t{}'.format(C,N,A,B,K, answer))

C = 50
N = 3
A = [39, 19, 28]
B = [49, 27, 35]
K = 15
answer = getSecondsElapsed(C, N,A,B, K)
print(' getSecondsElapsed({},{},{},{},{}) => \t{}'.format(C,N,A,B,K, answer))