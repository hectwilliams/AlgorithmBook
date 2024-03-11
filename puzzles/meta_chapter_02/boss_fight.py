from typing import List
from math import sqrt
import time 


# Write any import statements here

SPACE_XY = (10**9 + 100, 10**9 + 100)

def euclid_distance(x, y):
    res = sqrt((x[0] - y[0])**2 + (x[1] - y[1])**2)
    return res

def fight_boss (warrior, boss, unit) :
    damage_out = warrior[1]
    damage = unit * damage_out
    
    return damage, (0,damage_out)


def getMaxDamageDealt(N: int, H: List[int], D: List[int], B: int) -> float:

    highest =    () 
    neighbor = ()

    #SPACE XY is highest D and highest H possible in existence ( or operation region we desire)
    if euclid_distance(SPACE_XY, ( H[0], D[0] )) < euclid_distance(SPACE_XY, (H[1], D[1]) ) :
        highest, neighbor = (H[0], D[0]) , (H[1], D[1]) 
    else:
        neighbor, highest = (H[0], D[0]) , (H[1], D[1]) 
    
    for i in range(2, N):
        point = (H[i], D[i])
        
        # new high point
        if euclid_distance(SPACE_XY, point) < euclid_distance(SPACE_XY, highest):
            if euclid_distance(point, highest) < euclid_distance(point, neighbor):
                neighbor = highest
            highest = point 
        
        # possible new neighbor  ( closest to highest fighter )
        elif euclid_distance(point, highest) < euclid_distance(highest, neighbor) :
            neighbor = point 

    warriors = [highest, neighbor]
    damage = 0
    
    print(warriors)

    while warriors:
        
        # potential scale change 
        health_units = warriors[0][0]
        damage_out_units = warriors[0][1]

        scale_factor = (health_units / B)   # seconds until this warrior is dead 
        
        if health_units > B:
            # interpolation of damage bins 
            scale_factor = (health_units / B) 

        if damage_out_units > B:
            # decimate danage_out
            scale_factor *= (damage_out_units/ health_units)
            warriors[0] = (warriors[0][0], health_units )

        dam, _ = fight_boss(warriors[0], B, scale_factor)
        damage += dam

        # warriror 2 got some hits in this second ( while taking no damage ) 
        if len(warriors) == 2:
            dam, _  = fight_boss(warriors[1], B, scale_factor)
            damage += dam

        warriors[0] = (0, warriors[0][1])

        # # remove warrior 1 (he/she is dead)
        if warriors[0][0] <= 0:
            warriors.pop(0)

    return damage

N = 3
H = [2, 1, 4]
D = [3, 1, 2]
B = 4
answer = getMaxDamageDealt(N,H,D,B)
print('getMaxDamageDealt({}, {}, {}, {}) =\t {}'.format(N, H, D, B, answer))
print("----")

N = 4
H = [1, 1, 2, 100]
D = [1, 2, 1, 3]
B = 8
answer = getMaxDamageDealt(N,H,D,B)
print('getMaxDamageDealt({}, {}, {}, {}) =\t {}'.format(N, H, D, B, answer))
print("----")


N = 4
H = [1, 1, 2, 3]
D = [1, 2, 1, 100]
B = 8
answer = getMaxDamageDealt(N,H,D,B)
print('getMaxDamageDealt({}, {}, {}, {}) =\t {}'.format(N, H, D, B, answer))



def getMaxVisitableWebpages(N: int, L: List[int]) -> int:
    length = 1
    graph = {} 
    
    for i in range(N):
        link = L[i]
        page = i + 1

        if page in graph:
            
            graph[page]['out'] = link 
            
            if link not in graph:
                graph[page]['node_count'][0] += 1
                graph[link] = {'node_count': graph[page]['node_count'] , 'out': 0, 'in': page }
        else:
            
            if link not in graph:
                
                graph[page] = {'node_count': [2], 'out': link, 'in': 0}
                graph[link] = {'node_count': graph[page]['node_count'], 'out': 0, 'in': page }

            else:
                graph[page] = {'node_count': graph[link] ['node_count'], 'out': link, 'in': 0 } 
                
                # link has more than on ingress 
                if graph[link]['in'] not in graph:
                    graph[page]['node_count'][0] += 1

                graph[link]['in'] = page
                graph[link] ['node_count'] = graph[page] ['node_count']
        
        if graph[page]['node_count'][0] > length:
            length = graph[page]['node_count'][0]

    return length 

N = 4
L = [4, 1, 2, 1]
print(getMaxVisitableWebpages(N, L))

N = 5
L = [4, 3, 5, 1, 2]
print(getMaxVisitableWebpages(N, L))

N = 5
L = [2, 4, 2, 2, 3]
print(getMaxVisitableWebpages(N, L))
