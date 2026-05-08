
'''
    Purpose: 
    
        Showcase ability to bucketize data and handle translation of data. I was not able to highlight this in assessment; timedelta class is required to solve this problem :). 
        
    Author:
        
        Engineer Candidate: Hector Williams 

    Note:
	
	Ready knowledge of datetime module is a prerequisite to solve this problem :)
'''
  
'''

    Solver notes:
    
    Time flow:
        
        12AM ... 4AM ....11 AM ...11:59AM ... 12:00PM ...5:PM ... 10..PM ...11:59 PM  ...
    
    Description of cluster loading logs in time with timeout flag:
        
        x - minute flag
    
        [1] ...[9]...x ...[1]...21...x...[11] ...x...[1] ....x...[1]
    
    Description of cluster handling logs per day event of new day 
    
        [1] ...[8]...x ...[0]...[100] ...x....[0] 
    
'''

from datetime import timedelta

THRESHOLD = 10 

def parser_greedy_amazon(logs):
    '''
        A solution to the assessment "10 minutes per day". 
        This assumes the service can be started once. Service shuts down once 'Complete' log is received. The data is stored in S3 cache. 
        Restarts are permitted. A fresh bin is created after every restart. 
    '''
    
    bins = [] 
    static_S3_store = [] # days captures are stored here
    minutes = 0
    
    for record in logs:
        
        time_ = record[1:9]
        current_time = datetime.strptime(f"{time_}", "%I:%M %p")
    
        if "Started" in record:
            if not bins:
                # init bin's accumulator
                bins += [0]
            prev_time = datetime.strptime(f"{time_}", "%I:%M %p")
            minutes = 0
            
        # find minutes logging 
        delta = current_time - prev_time
        minutes += delta.total_seconds() / 60
        
        if minutes >= 60 :
            # create new bin to load iff last bin is full 
            print('ALERT', "minutes alert")
            pos = len(bins) - 1
            while bins[pos] > THRESHOLD:
                # tail bin should be < THRESHOLD
                if bins[-1] >= THRESHOLD:
                    bins += [0]
                else:
                    bins[-1] += 1  #incr
                    bins[pos] -=1  #decr 
            
            minutes = 0 # reset delta accumulator 
            
        else:
            bins[-1] += 1
    
        prev_time = current_time 
        
        if "Restarted" in record:
            '''
                Handling restart is an interesting conundrum.
            
                Our service could restart on the same day.
            
                Our Service restart could occur days later. 
            
                Knowing if the system stopped on same-day or days later requires more meta data from system hardware ( i.e. ambiguous log data)
            
                best course of action is to write parser translation to a file  after each restart 
            '''
            
            static_S3_store += bins +[]
            bins = [0] # :) 
            minutes = 0
            
            # handle restart log 
            delta = current_time - prev_time
            minutes += delta.total_seconds() / 60
            
    
    if bins:
        if bins[-1]:
            static_S3_store += [bins[-1]]
    
    return (static_S3_store)

if "__main__" == "__main__":
    
    logs = [
        "[05:00 AM] Sever Started",
        "[05:00 AM] Sever Writing",
        "[05:01 AM] Sever Writing",
        "[05:01 AM] Sever Writing",
        "[05:01 AM] Sever Writing",
        "[05:01 AM] Sever Writing",
        "[05:01 AM] Sever Writing",
        "[05:01 AM] Sever Writing",
        "[05:01 AM] Sever Writing",
        "[05:01 AM] Sever Writing",
        "[05:01 AM] Sever Writing",
        "[05:01 AM] Sever Writing",
        "[05:01 AM] Sever Writing",
        "[05:01 AM] Sever Writing",
        "[01:13 PM] Sever Writing",
        "[01:10 PM] Sever Restarted", # 
        "[01:14 PM] Sever Restarted", # 
        "[01:45 PM] Sever Restarted", # 
        "[01:48 PM] Sever Writing", 
        "[05:33 PM] Sever Writing",
        "[02:01 PM] Complete",
        ]
        
    ret = parser_greedy_amazon(logs)
    
    print("Representative Data of logs", ret)

    
    
  
