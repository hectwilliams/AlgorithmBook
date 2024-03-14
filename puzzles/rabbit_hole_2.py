
from typing import List
from copy import copy, deepcopy

# Write any import statements here
class PageNode:
  def __init__(self, page) -> None:
    self.page = page 
    self.max_distance = 0
    self.visitors = {} 
    self.visitors_expected = {} 
    self.mlinks = {}

def clone_(parent: dict):
    res = {}
    for key in parent:
        if isinstance(parent[key] , list):
            res[key] = parent[key] + []
        else:
            res[key] = parent[key] 
    return res 

def getMaxVisitableWebpages(N: int, M: int, A: List[int], B: List[int]) -> int:
    graph = {} 
    q = [] 
    best_max_distance = 0

    for page in range(1, M + 1):
        i = page - 1
        m = page 

        # create node in graph for page         
        if m not in graph and  (m >= 1 and m<= N) :
            graph[m] = PageNode(m)

        m_link_page = A[i]
        
        # does m_link_page exist 
        if m_link_page not in graph:
            graph[m_link_page] = PageNode(m_link_page)
        # assign m
        graph[m_link_page].mlinks[m] = None
        # create mapping for m and page 

        # egress 
        m_link_page_ = B[i]
        if m_link_page_ not in graph:
            graph[m_link_page_] = PageNode(m_link_page_)
        graph[m_link_page].mlinks[m] = m_link_page_
        graph[m_link_page_].visitors_expected[m_link_page] = True


        if (page >= 1 and page<= N) :
            page_record = {}
            page_record['curr_node'] = graph[page]
            page_record['distance'] = 1 # start at a node 
            page_record['visitors'] = {} 
            page_record['path'] = [page]
            
            q.append(page_record)

    # first breath slowest wins
    while q:
        record = q.pop(0)


        curr_page_node = record['curr_node']
        curr_page_node_distance = record['distance']
        curr_page_node_path = record['path']

        # update visitors in node (i.e. static store) 
        curr_page_node.visitors = record['visitors']
        
        # update node's max distance rcvd  ( measure when entering this node)
        if curr_page_node_distance > curr_page_node.max_distance:
           curr_page_node.max_distance = curr_page_node_distance
        
        # update global max distance 
        if curr_page_node_distance > best_max_distance:
            best_max_distance = curr_page_node_distance
        
        # hold past list of  visitors 
        # print(record)

        # only search if walker distance is equal to larger previous passer
        for m_link in curr_page_node.mlinks:

            
            next_page = curr_page_node.mlinks[m_link]

            next_page_node = graph[next_page]
            
            next_distance = curr_page_node_distance + 1
            
            # restrict visiting curr node 
            if next_page == curr_page_node.page or next_page in curr_page_node_path:
                continue
            
            # clone visitors 
            next_page_visitors = clone_(next_page_node.visitors) 
            
            if curr_page_node.page not in next_page_visitors:
                next_page_visitors[curr_page_node.page] = [curr_page_node.page]
            next_page_visitors[curr_page_node.page] +=   [next_page] 

            if ( next_page_visitors.keys() != next_page_node.visitors_expected.keys() ) or (next_distance >= next_page_node.max_distance)  :
                q.append({ 'curr_node': next_page_node, 'distance': next_distance,  'visitors':  next_page_visitors, 'path':  curr_page_node_path + [next_page] })
 
    return best_max_distance
    

N = 4
M = 4
A = [1, 2, 3, 4]
B = [4, 1, 2, 1]
answer = getMaxVisitableWebpages(N, M, A, B)
print(answer)


N = 5
M = 6
A = [3, 5, 3, 1, 3, 2]
B = [2, 1, 2, 4, 5, 4]
answer = getMaxVisitableWebpages(N, M, A, B)
print(answer)

N = 10
M = 9
A = [3, 2, 5, 9, 10, 3, 3, 9, 4]
B = [9, 5, 7, 8, 6, 4, 5, 3, 9]
answer = getMaxVisitableWebpages(N, M, A, B)
print(answer)
