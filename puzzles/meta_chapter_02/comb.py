from typing import List

def combination(S: str) ->List[str]:
    q = []
    samples = [] 

    q.append({'data': S, 'buf' : ['']})
    
    while q:
        record = q.pop(0)
        print(record)
        data  = record['data']
        buf  = record['buf'] + []

        if data:
            c = data[0]
            data = data[ 1 : ]
            fetch_len = len(buf)

            for i in range(fetch_len):
                prefix = buf[i]
                buf.append( prefix + c )

            q.append({'data': data, 'buf' : buf })
                
        else:
            samples += buf[1 : ]
    
    return samples 

S = "abcd"
answer = combination(S)
print("combination({}) =\t {}".format(S, answer))