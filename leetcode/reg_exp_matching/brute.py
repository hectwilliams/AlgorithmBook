"""

  Purpose: Solve leetcode regex matching problem

  Author : Hectron 

  Notes: This method is brute force method and was able to answer 10 percent of testcase. I am working on another "streamlined" approach. Nevertheless this was fun!

  Example: 

  s = "mississippi"
  p = "mis*is*ip*."
  solution = Solution()
  ret = solution.isMatch(s, p)

"""

def generate_bins(current_index, raw_commands, target, spad, greedy_indices): 
    
    p = current_index #
    greedy_indices += [len(greedy_indices)]
    greedy_flag = True  # We enter this logic state in a greedy operation 
    spad[target] += [1] #  Create accumulator for greedy operation 
    
    while p < len(raw_commands):
    
        if p + 1 >= len(raw_commands):
            #last command in command sequence ( sequence may not match input paramter s)  
            if raw_commands[p] == target:
                if greedy_flag:
                    spad[target][-1] += 1
                else:
                    spad[target]+= [1]
        else:
            
            if (raw_commands[p + 1] == "*") and  (raw_commands[p] == target) :
                #lookahead, check if next command is greedy 
                greedy_flag = True
                spad[target] += [0]
                greedy_indices += [len(greedy_indices)]

            if greedy_flag and (raw_commands[p] != target) and (raw_commands[p] != "*"):
                # turn off greedy flag
                greedy_flag = False 
            
            # accumulate greedy operation
            if greedy_flag and target == raw_commands[p]:
                spad[target][-1] += 1
            
            # new operation found (bin created)
            if not greedy_flag and target == raw_commands[p]:
                spad[target] += [1]
    
        # print(p, commands, spad[target] , f"NUMBER OF FLOATINGS TARGETS {n_contiguous_targets_input}")    
        p += 1
        
    return spad, greedy_indices

def generate_bins_dot(raw_commands, target, spad, greedy_indices): 
    
    greddy_flag = False 
    k = len(raw_commands) - 1
    r = -1
    

    while k > -1:
        if raw_commands[k]  == "*":
            greddy_flag = True
        else:
            spad[target].insert(0,+(not greddy_flag) )  # greedy bins start with zero
            if greddy_flag:
                greedy_indices.insert(0, r) 
                spad["info"].insert(0,  "z-"  + raw_commands[k]  ) 

            else:
                spad["info"].insert(0,  "s-" + raw_commands[k]  ) 
            greddy_flag = False
            r -= 1   
        k -=1


  
def regex_is_valid(spad, s):
    # test whether commands can produce a regex match to the input 
    # if buffer is zero after test, then return True, otherwise all test have failed 
    
    size_bins = len(spad["info"])
    ticks = [0 for _ in range(size_bins)]
    ticks_fifo = [1 for _ in range(size_bins)] #ticks bins have single single element
    threshold_ticks_bins = len(s)  
    last_tick_bin_state = [ threshold_ticks_bins  for _ in range(size_bins)]
    ticks_thresholds = [ int((threshold_ticks_bins + 1) **k) for k in range(0,size_bins + 1 )]
    
    print('enter', s, last_tick_bin_state, threshold_ticks_bins)
    print(spad)
    
    while 1 :
        # validate regex 
        state = True
        s_available = s + ""
        s_acc = ""
        
        for i in range(len(ticks)):
            
            # if ticks == [2,1,2,1,2,1]:
            #     print(ticks[i], s_available)
            
            if spad["info"][i][0] == 'z' :
            
                # any character case 
                if ticks[i] == 0 :
                    # don't absorb during this trial
                    pass 
                
                elif ticks[i]:
                    # absorbs x number of characters ?
                    n_reads = ticks[i]
                    for _ in range(n_reads):
                        # any symbols are available for absorption
                        if (spad["info"][i][2] == '.' and not s_available) :
                            # empty with more reads to invoke --> not possible method (exit test)
                            state = state and False 
                            break
                        # specific type of symbol absorption test 
                        elif (spad["info"][i][2] != '.') and (not s_available or s_available[0] != spad["info"][i][2]  ) :
                            # empty with more reads to invoke --> not possible method (exit test)
                            # specific symbol does not match command expectation 
                            state = state and False 
                            break
                        else:
                            s_acc += s_available[0]                                    
                            s_available = s_available[1:] 
                    
            if spad["info"][i][0] == 's' :
                # nothing read ( even though I have been asigned to read)
                
                if ticks[i] != 1:
                    # invalid state, all non-greedy commands match to a symbol 
                    state = state and False
                
                elif ticks[i]:
                    
                    # aborb unique symbol
                    
                    if not s_available:
                        # no symbol to absorb 
                        state = state and False 
                    
                    else:
                            
                        if spad['info'][i][2] == '.' or spad['info'][i][2] == s_available[0]:
                            # match any symbol or expected symbol
                            s_acc += s_available[0]
                            s_available = s_available[1:]
                       
                        else :
                            # danger 
                            state = state and False 
          
        state = state and (not s_available)
        
        if (state):
            return state
        
        if last_tick_bin_state == ticks:
            break
        
        # update ticks ( ticks bin represents all possible matches for greedy command)
        for i in range(size_bins):
            
            if ticks_fifo[i] >= ticks_thresholds[i]:
                # clear bin
                ticks_fifo[i] = -1 # represents clearing bin
                
                # ticks bins can stack repeated values; if a bin is full, remove all values and replace with next number 
                ticks[i] = (ticks[i] + 1) % (threshold_ticks_bins + 1 ) 
                
                # update status of bin
                ticks_fifo[i] = 1
            
            else:
                # add value to tick bin
                
                ticks_fifo[i] += 1 
                
    return state

class Solution:
    def isMatch(self, s: str, p: str) -> bool:
        w = 0
        commands =  list(p)
        s_init = s
        prev_command = ""
        test_string = ""
        spad = {}
        rules = {}
        greedy_indices = []
        main_commands_index = 0
        raw_commands = commands + []
        count = 0
        
        while commands  :
            
            spad = {}
            
            greedy_indices = []

            cmd = commands.pop(0)
            
            main_commands_index += 1
            
            skip_n_commands = 0
            
            if cmd == "*":
                
                target = prev_command
                spad[target] = []
                spad["info"] = []
                eff_main_commands_index = main_commands_index - 2
                generate_bins_dot(raw_commands[eff_main_commands_index:], prev_command, spad, greedy_indices)
                ret = regex_is_valid(spad, s[w:]) # regex can occupy string 
                return ret 

            else:
                
                if cmd == ".":
                    
                    if not commands:
                        # empty command list (last command)
                        
                        if w >= len(s):
                            return False
                        else:
                            test_string += s[w] 
                        
                    elif  w >= len(s):
                        # evaluated all charaters in string
                        pass
                    
                    elif  len(s) == 0:
                        # eval an empty list pass ( match empty set)
                        pass 
    
                    elif commands[0] == '*':
                        # test_string appended value is a placeholder ,  next value is greedy command
                        test_string += s[w] 
                    
                    else :
                        
                        test_string += s[w] 
                        w += 1
                    
                else:
                    
            
                    
                    if not commands:
                        
                        if w >= len(s):
                            #evaluated all characters while still trying to search for a new character
                            return False
                            
                        if cmd == s[w]:
                            test_string += s[w]
                            w += 1
                    else:
                        
                        if commands[0] == '*':                            
                            pass

                        elif cmd == s[w] :
                            # match to simple operation 
                            test_string += s[w]
                            w += 1
                        else: 
                            return False
            
            prev_command = cmd
            
    
        return test_string  == s   and not commands
        



