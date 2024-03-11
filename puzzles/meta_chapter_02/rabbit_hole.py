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


def getMaxVisitableWebpages(N: int, L: List[int]) -> int:
    length = [1]
    graph = {} 
    
    # generate graph
    for i in range(N):
        link = L[i]
        page = i + 1


        if page in graph:
            
            if link not in graph:
                # create new link node (new tail)
                graph[link] = { 'ins': [] , 'out':0 }
                
                #connect active page to new link 
                graph[link]['ins'].append(page)
                graph[page]['out'] = link
            
            else:
                # connect 
                graph[page]['out'] = link 
                
                # if page not in graph[link]['ins'] :
                graph[link]['ins'].append(page)

        else:
            #create page node 
            graph[page] = {  'ins': [], 'out':0, }

            if link not in graph:
                # create link node ( new tail ) 
                graph[link] = {  'ins': [] , 'out':0 }

                # connect page->link
                graph[page]['out'] = link 
                graph[link]['ins'].append(page) 

            else:
                # new page connects to active link ( new head connects to graph )
                # connect 
                graph[page]['out'] = link
                
                # if p00age not in graph[link]['ins'] :
                graph[link]['ins'].append(page)

    # search graph
    
    max_search(graph, length)


    return length[0]



N = 4
L = [4, 1, 2, 1]
answer_ = getMaxVisitableWebpages(N, L)
print(answer_, '---\t')

N = 5
L = [4, 3, 5, 1, 2]
answer__ = getMaxVisitableWebpages(N, L)
print(answer__, '---\t')

N = 5
L = [2, 4, 2, 2, 3]
answer___ = getMaxVisitableWebpages(N, L)
print(answer___, '---\t')


N = 7
L = [2, 3, 4, 8, 4, 5, 6, 1]
answer___ = getMaxVisitableWebpages(N, L)
print(answer___, '---\t')

