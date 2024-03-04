from typing import List
# Write any import statements here

def getMaxExpectedProfit(N: int, V: List[int], C: int, S: float) -> float:
    q = [{'absolute_cash': 0, 'potential_cash': 0,  'path': [[0,'']] }]
    max_price = 0

    while q:

        record = q.pop(0)
        absolute_cash = record['absolute_cash']
        potential_cash = record['potential_cash']
        path = record['path']
        prev_decision = record['path'][-1][1]
        prev_day = record['path'][-1][0]
        curr_day = prev_day + 1

        if curr_day <= N:
            
            package_price = V[curr_day - 1]

            # S probablity of all items stolen on this curr_day
            # (1 - S) probability of all items NOT being stolen on this curr_day 
            if prev_decision == 'skip':
                potential_cash = potential_cash * (1 - S ) 
            
            # enter room using price_enter path 
            q.append({'absolute_cash': potential_cash + absolute_cash + package_price - C , 'potential_cash': 0 , 'path': path + [[ curr_day, 'enter']]  })

            # skipping implies person COULD have a price gain of {price + package_price} that is affected by probability the next day 
            q.append( {'absolute_cash': absolute_cash, 'potential_cash': potential_cash + package_price ,'path': path + [[curr_day, 'skip']] })
    
        # absolute cash always generates the sum of cash and potential cash
            
        if absolute_cash > max_price:
            max_price = absolute_cash

    return max_price