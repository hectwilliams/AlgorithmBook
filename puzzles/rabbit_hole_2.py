
from typing import List
from copy import deepcopy
# Write any import statements here
class PageNode:
  def __init__(self, page) -> None:
    self.page = page 
    self.max_distance = 0
    self.exited = {} 
    self.exited_expected = {} 
    self.visitors = {} 
    self.visitors_expected = {} 
    self.mlinks = {}

def clone_(parent):
    res = parent 

    # top level
    if isinstance(parent, list):
        res = []
        for i in range(len(parent)):
            child = parent[i]
            res.append(clone_(child))
    elif isinstance(parent, dict):
        res = {}
        for key in parent:
            child = parent[key]
            res[key] = clone_(child)
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
        # graph[m_link_page_].visitors_expected[m_link_page] = True
        graph[m_link_page_].visitors_expected[m] = True

        if (page >= 1 and page<= N) :
            page_record = {}
            page_record['curr_node'] = graph[page]
            page_record['distance'] = 1 # start at a node 
            page_record['visitors'] = {} 
            page_record['exitors'] = {} 
            page_record['path'] = [page]
            q.append(page_record)

    # for page in graph: 
    #     node = graph[page]
    #     print('page] {}   visitors_expected = {}\t existed_expected {}\t node links = {}  '.format(page, node.visitors_expected , node.exited_expected   , node.mlinks))

    while q:
        record = q.pop(0)
        
        # print(record)

        curr_page_node = record['curr_node']
        curr_page_node_distance = record['distance']
        curr_page_node_path = record['path']
        exitors = record['exitors'] 
        visitors =   record['visitors'] 

        # # update node's max distance rcvd  ( measure when entering this node)
        # if curr_page_node_distance > curr_page_node.max_distance:
        #    curr_page_node.max_distance = curr_page_node_distance
        
        # update global max distance 
        if curr_page_node_distance >= best_max_distance:
            print(curr_page_node_path)
            best_max_distance = curr_page_node_distance
        
        # only search if walker distance is equal to larger previous passer
        for m_link in curr_page_node.mlinks:
            
            next_page = curr_page_node.mlinks[m_link]
            next_page_node = graph[next_page]
            next_distance = curr_page_node_distance + int(next_page not in curr_page_node_path)

            # revisited page
            if next_page in visitors : 
                if  m_link in visitors[next_page]:
                    continue
            
            ## visitor block 
            visitors_in_path = clone_(visitors)
            if next_page not in visitors_in_path:
                visitors_in_path[next_page] = {} 
            if m_link not in visitors_in_path[next_page]:
                visitors_in_path[next_page][m_link] = True
            
            ## exitors block 
            exitors_in_path = clone_(exitors)
            if curr_page_node.page not in exitors_in_path:
                exitors_in_path[curr_page_node.page ] = {} 
            if m_link not in exitors_in_path[curr_page_node.page]:
                exitors_in_path[curr_page_node.page ] [m_link] = True
            
            q.append({ 'curr_node': next_page_node, 'distance': next_distance,  'visitors':  visitors_in_path, 'exitors': exitors_in_path, 'path':  curr_page_node_path + [next_page] })

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
