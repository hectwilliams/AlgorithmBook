from typing import List

def getMaxVisitableWebpages(N: int, L: List[int]) -> int:
    q = []
    length = 0

    # start from different pages 
    for page in range(1, N + 1):
        q.append({'curr': str(page), 'path': str(page)})
        
    while q:
        record = q.pop(0)
        page = int(record['curr'])
        path = record['path']
        i = page - 1

        if len(path) > length:
            length = len(path)        

        if i >= 0 and i < N :
            page_link = L[i] # index = page - 1
            if str(page_link) not in path:
                q.append({'curr': str(page_link), 'path': path + str(page_link)})
    
    return length