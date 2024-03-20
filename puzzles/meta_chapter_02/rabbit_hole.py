from typing import List



def max_search(graph, buffered_length):
    
    q = [] 

    for node in graph:
        q.append({'node':node, 'count' : 0, 'pad' :{}})

    while q:
        record = q.pop(0)
        node = record['node']
        count = record['count'] + 1
        scratch_pad = record['pad']

        if buffered_length[0] < count:
            buffered_length[0] = count 

        scratch_pad[node] = True 
        for ingress_node in graph[node]['ins']:
            if ingress_node not in scratch_pad:
                q.append({'node': ingress_node , 'count': count, 'pad' : scratch_pad  } )


# def getMaxVisitableWebpages(N: int, L: List[int]) -> int:
#     length = [1]
#     graph = {} 
    
#     # generate graph
#     for i in range(N):
#         link = L[i]
#         page = i + 1


#         if page in graph:
            
#             if link not in graph:
#                 # create new link node (new tail)
#                 graph[link] = { 'ins': [] , 'out':0 }
                
#                 #connect active page to new link 
#                 graph[link]['ins'].append(page)
#                 graph[page]['out'] = link
            
#             else:
#                 # connect 
#                 graph[page]['out'] = link 
                
#                 # if page not in graph[link]['ins'] :
#                 graph[link]['ins'].append(page)

#         else:
#             #create page node 
#             graph[page] = {  'ins': [], 'out':0, }

#             if link not in graph:
#                 # create link node ( new tail ) 
#                 graph[link] = {  'ins': [] , 'out':0 }

#                 # connect page->link
#                 graph[page]['out'] = link 
#                 graph[link]['ins'].append(page) 

#             else:
#                 # new page connects to active link ( new head connects to graph )
#                 # connect 
#                 graph[page]['out'] = link
                
#                 # if p00age not in graph[link]['ins'] :
#                 graph[link]['ins'].append(page)

#     # search graph
    
#     max_search(graph, length)


#     return length[0]



# # N = 4
# # L = [4, 1, 2, 1]
# # answer_ = getMaxVisitableWebpages(N, L)
# # print(answer_, '---\t')

# # N = 5
# # L = [4, 3, 5, 1, 2]
# # answer__ = getMaxVisitableWebpages(N, L)
# # print(answer__, '---\t')

# # N = 5
# # L = [2, 4, 2, 2, 3]
# # answer___ = getMaxVisitableWebpages(N, L)
# # print(answer___, '---\t')


# # N = 7
# # L = [2, 3, 4, 8, 4, 5, 6, 1]
# # answer___ = getMaxVisitableWebpages(N, L)
# # print(answer___, '---\t')


# def merge_paths (pathA, pathB):
#     buffer = [] 
#     walk = 0 

#     while walk < len(pathA):
#         node = pathA[walk]
#         index = -1

#         for i in range(len(pathB)):
#             if node == pathB[i]:
#                 index = i
#                 break

#         if index != -1:
#             pathB = pathB[:index] + pathB[index + 1 :] 
#             pathA = pathA[:walk] + pathA[walk + 1 :] 
#             buffer += [node]
#         else :
#             walk +=1 

#     # turn back to array
#     return buffer + pathA + pathB

# def back_prop(graph, page):
#     scratch_pad = {}

#     q = [page]

#     while q:
        
#         node = q.pop(0)
        
#         if node not in scratch_pad:

#             scratch_pad[node] = True 
        
#             link = graph[node]['out']
#             graph[node]['paths'] = [node] + graph[link]['paths']

#             for ingress_page in graph[node]['ins']:
#                 q.append(ingress_page)


    
# def getMaxVisitableWebpages_(N: int, L: List[int]) -> int:
#     length = [1]
#     graph = {} 
    
#     # generate graph
#     for i in range(N):
#         link = L[i]
#         page = i + 1

#         if page in graph:
            
#             if link not in graph:

#                 # create new link node (new tail)
            
#                 graph[link] = { 'is_loop': False,  'paths': [link], 'ins': [] , 'out':0 }
                
#                 #connect active page to new link 
#                 graph[link]['ins'].append(page)
#                 graph[page]['out'] = link
                
#                 graph[page]['paths'] = [page] + [link]

#                 # backpropagate 
#                 back_prop(graph, page)
            
#             else:

#                 # connect 
#                 graph[page]['out'] = link 
                
#                 # if page not in graph[link]['ins'] :
#                 graph[link]['ins'].append(page)

#                 # info from link node 
#                 path_link = graph[link]['paths']
                
#                 # if not loop
#                 if page not in path_link:
                    
#                     graph[page]['paths'] =  graph[page]['paths']  + path_link

#                 # loop found 
#                 else :
#                     graph[page]['is_loop'] = True
#                     # graph[page]['paths'] =  graph[page]['paths']  + path_link[:-1]
                    
#                     graph[link]['is_loop'] = True

#                     nodes = graph[link]['paths']

#                     for _ in range(len(nodes)):

#                         graph[nodes[0]]['paths'] =  nodes
#                         graph[nodes[0]]['is_loop'] = True
#                         # right rotate
#                         nodes = [nodes[-1]] + nodes[ : -1 ]

                

#         else:
#             #create page node 
#             graph[page] = { 'is_loop': False,  'paths': [page] +  [link],  'ins': [], 'out':0, }

#             if link not in graph:

#                 # create link node ( new tail ) 
#                 graph[link] = { 'is_loop': False, 'paths': [link],   'ins': [] , 'out':0 }

#                 # connect page->link
#                 graph[page]['out'] = link 
#                 graph[link]['ins'].append(page) 

#             else:
#                 # new page connects to active link ( new head connects to graph )
#                 # connect 
#                 graph[page]['out'] = link
                
#                 # if page not in graph[link]['ins'] :
#                 graph[link]['ins'].append(page)

#                 # max count 
#                 graph[page]['paths']  = [page] +  graph[link]['paths']
                
        
#         lm = graph[page]['paths']

#         if len(lm) > length[0] :
#             length[0] = len(lm)

#     # print(graph)
#     return length[0]



#     # search graph
    
#     # max_search(graph, length)
class PageNode:
  def __init__(self, page) -> None:
    self.page = page 
    self.links = [] 

def getMaxVisitableWebpages_(N: int ,  L: List[int]) -> int:
    graph = {} 
    q = [] 
    best_max_distance = 0

    for page in range(1, N + 1):
        i = page - 1

        # create node in graph for page         
        if page not in graph:
            graph[page] = PageNode(page)

        # new link ( could link to same page :( ))
        to_link_a = L[i]

        # node does not exist 
        if to_link_a not in graph:
            graph[to_link_a] = PageNode(to_link_a)

        # link on page 
        if to_link_a not in graph[page].links:
            graph[page].links.append(to_link_a)

        page_record = {}
        page_record['curr_node'] = graph[page]
        page_record['distance'] = 1 # start at a node 
        page_record['path'] = [page]
        
        q.append(page_record)

    # first breath slowest wins
    while q:
        record = q.pop(0)


        curr_page_node = record['curr_node']
        curr_page_node_distance = record['distance']
        curr_page_node_path = record['path']

        # update visitors in node (i.e. static store) 
        # curr_page_node.visitors = record['visitors']
        
        # update global max distance 
        if curr_page_node_distance > best_max_distance:
            best_max_distance = curr_page_node_distance
        
        # only search if walker distance is equal to larger previous passer
        for next_page in curr_page_node.links:
            
            next_page_node = graph[next_page]
            next_distance = curr_page_node_distance + 1
            
            # restrict visiting curr node 
            if next_page in curr_page_node_path:
                continue
            q.append({ 'curr_node': next_page_node, 'distance': next_distance, 'path':  curr_page_node_path + [next_page] })
 
    return best_max_distance


N = 4
L = [4, 1, 2, 1]
answer_ = getMaxVisitableWebpages_(N, L)
print(answer_, '---\t')

N = 5
L = [4, 3, 5, 1, 2]
answer__ = getMaxVisitableWebpages_(N, L)
print(answer__, '---\t')

N = 5
L = [2, 4, 2, 2, 3]
answer___ = getMaxVisitableWebpages_(N, L)
print(answer___, '---\t')


# N = 7
# L = [2, 3, 4, 8, 4, 5, 6, 1]
# answer___ = getMaxVisitableWebpages_(N, L)
# print(answer___, '---\t')

