"""

  EUREKEA !!!!!!!!!!!!!!!!!!!!! THIS SOLUTION WAS THOUGHT OF WHILE DEEP THOUGHT IN THE SHOWER :)

  PURPOSE -  Solve regex matching problem (leetcode)

  NOTE - 100 % of testcases !!!

  AUTHOR - Hectron

"""

import re 


def translate_seq(s):
    bins = []
    main_actor = "DEAD"
    for i in range(len(s)):
        if s[i] != main_actor:
            # update action 
            main_actor = s[i]
            bins += [[main_actor, 0]]
        bins[-1][-1] += 1
        
    return bins 


def translate_commands(raw_commands): 
    pad = [] 
    greddy_flag = False 
    k = len(raw_commands) - 1
    while k > -1:
        if raw_commands[k]  == "*":
            greddy_flag = True
        else:
            if greddy_flag:
                pad.insert(0,  "z-"  + raw_commands[k]  ) 
                if pad.__len__() > 1:
                    if pad[0] == pad[1] and pad[0][0] == 'z':
                        #prevent repeated/contigious greedy commands 
                        pad.pop(0)

            else:
                pad.insert(0,  "s-" + raw_commands[k]  ) 
            greddy_flag = False
        k -=1
    
    return pad 
    

class processNode:
    # Landing node for processing serialized translattion (eureka baby, thoguh of this in the shower)
    def __init__(self, s: list[list[str, int]], p: list[str]) :
        
        self.p = [] + p
        self.s = [] + s
        self.meta = [] # blah blah future proof 
        self.counter = 0
        self.history = []

def split_end(node : processNode, side: int) -> list[processNode]:
    # z-. or z<CHARACTER>
    p = node.p.pop(side * -1) # the head node is replaced with new node; 
    # node.p.pop(0)
    # print(p)
    if p[0] == 'z':
        m1 = ['y1-' + p[2] ]
        m2 = []
    elif p[0] == 'y':
        # print(p, 'HELLo')
        specific_size, cmd = re.match(r"y(\d+)\-(\.|[a-zA-Z])", p ).groups(0) # command equals z-. or z-<CHARACTER>
        m1 = [f'[{int(specific_size) }]-{cmd}' ]
        m2 = [f"y{int(specific_size) +1 }-{cmd}"]
    else:
        # something is wrong
        raise ValueError("current evaluation must have a greedy command at either head or tail of serial commands (properties p)")
        
    if side == 0:
        
        return processNode(node.s , m1 + node.p), processNode( node.s , m2 + node.p )
    
    else:

        return processNode(node.s  , node.p + m1 ), processNode( node.s  , node.p + m2)

def split_end_dual(node):
    '''
        Splitting both sides of the commands/serial regex requires 1 node to 4 nodes growth
        
        First split the left side :
        
            A1_one_of_more --- B1_one_or_more 
            
                A1_one <-->  B1_one_or_more                    
                         
                A1_more <--> B1_one_or_more
            
            
        
        Next split the right side:
        
            A1_one -->  B1_one_or_more --x
            
                A1_one <-->  B1_one
                
                A1_one <-->  B1_more
                
            A1_more -->  B1_one_or_more --x
            
                A1_more <-->  B1_one
                
                A1_more <-->  B1_more
        
        Then repeat for the right side splitting first                     
    
    '''
    # node.p.insert(0, 'y1-.')
    # node.p.append('y1-.')
    # print('split left')
    a1_one_to_b1_one_or_more ,a1_more_to_b1_one_or_more = split_end(node, 0) # left side
    # print('split right')
    a1_one_to_b1_one ,a1_one_to_b1_more = split_end(a1_one_to_b1_one_or_more, 1) # right side on each 
    a1_more_to_b1_one ,a1_more_to_b1_more = split_end(a1_more_to_b1_one_or_more, 1) # right side on each
    
    # print(a1_one_to_b1_one.p)
    # print(a1_one_to_b1_more.p)
    # a,b = split_end(b, 0)
    
    return a1_one_to_b1_one, a1_one_to_b1_more , a1_more_to_b1_one, a1_more_to_b1_more

def safe_s_bin_op(node, u):
    # Adds to the value property in bin 
    data_bin = node.s[0] + []
    data_bin[1] += u
    # update bin
    node.s[0] = data_bin
    
class Solution:
    def isMatch(self, s: str, p: str) -> bool:
        
        s_stream = translate_seq(s)
        p_stream = translate_commands(p)
        s_len = len(s)
        
        print(s_stream, p_stream)
        
        q = [ processNode(s_stream, p_stream) ]
        
        while q:
            
            node = q.pop(0) 
            
            if not node.p and not node.s:
                # both command bin and sequence empty 
                return True
    
            if len(node.p) == 1 and node.p[0][0] == 'z'  :

                if  not node.s:
                    # s = ""  p = .* 
                    # s = ""  p = d*
                    return True 
                
                if node.s:
                        
                    if node.p[0][2] == '.':
                        # The Thing aborbs all!
                        return True
                        
                    elif node.p[0][2] != '.':
                        
                        if node.p[0][0] == node.p[0][2] :
                            # matching command and head of bin 
                            
                            if len(node.s) == 1:
                                # command  matches front of bin
                                    return True 
                            
                            if all([ propp[0] == node.s[-1] for propp in node.s]) :
                                # all symbols in bin are the same 
                                return True 
                            
                            # heterogenous bin 
                            return False
                    
            if not node.s:
                # all symbol bins absorbed
                if all([ propp[0] == 'z'  for propp in node.p]):
                    return True 


            if (node.p  and not node.s) or (node.s and not node.p):
                #either bins list is empty, discard node 
                continue 
            
            if node.p[0][0] == 'z':
                #greedy command, # split this bugger :) 
                node1, node2 = split_end(node, 0)
                q.append(node1)
                q.append(node2)
                continue
            elif node.p[0][0] == 'y':
                #greedy command;  n or more matches. Ambigious, split this bugger again 
                r = re.match(r'^y(\d+)\-.', node.p[0])
                n_expected_matches = int(r.groups(0)[0])
                if n_expected_matches  <= s_len + 3 :
                    # number of commands exceed sequence length ( throw away node)
                    node1, node2 = split_end(node, 0)
                    q.append(node1)
                    q.append(node2)
                    continue 
                else:
                    # instructions/rules larger than input string ( dump )
                    continue
            elif node.p[0][0] == 's':
                # Single command
                if node.p[0][2] == '.':
                    # match any symbol 
                    safe_s_bin_op(node, -1)
                    node.history = node.history + [node.p[0]]
                    node.p.pop(0) # remove single command 
                    if node.s[0][1] == 0:
                        # all commands handled, remove bin
                        node.s.pop(0)
                        
                elif node.p[0][2] == node.s[0][0]:
                    #match specific symbol 
                    safe_s_bin_op(node, -1)
                    node.history = node.history + [node.p[0]]
                    node.p.pop(0)
                    if node.s[0][1] == 0:
                        node.s.pop(0)
                else:
                    # command rule does equal current symbol (i.e. instruction - read 'e'  , sequence current letter is 'r')
                    continue
                    
            elif node.p[0][0] =="[" :
                # read from edge
                end = node.p[0].index("]")
                n_reads = int(node.p[0][1:end])
                cmd = node.p[0][end+2]  
                
                if cmd == ".":
                    # read sequence bins data
                    while n_reads > 0:
                        # read nonspecific bin data ( The Thing parasite does not deciminate :) )
                        safe_s_bin_op(node, -1)
                        n_reads = n_reads - 1
                        node.history = node.history + [node.p[0]]
                        if node.s[0][1] == 0:
                            # sequence bin empty, remove it
                            node.s.pop(0)
                        
                        if not node.s:
                            # sequence bins are empty 
                            break
                    
                    if  n_reads == 0 :
                        # all commands in commands bin handled, remove front command bin 
                        node.p.pop(0)
                    else:
                        # too many request from commands bins 
                        continue 
                
                else:
                    # read specific bin data (contigious)
                    if cmd != node.s[0][0]:
                        # cmd does not match current bin 
                        continue
                    
                    while n_reads > 0 and node.s[0][1]  > 0:
                        safe_s_bin_op(node, -1)
                        n_reads = n_reads - 1                        
                        node.history = node.history + [node.p[0]]
                   
                    if n_reads == 0:
                        # all reads were complete, remove command bin and sequence bin
                        node.p.pop(0)
                        if node.s[0][1] == 0:
                            # drop active symbol bin iff empty, else persist for next command bin
                            node.s.pop(0)
                        else:
                            pass
                            # continue
                        
                    else:
                        # invalid state , cannot handle commands 
                        # print("FAILIURE", n_reads, node.p, node.s)
                        continue
                    
            q.append(node) # put node back
        
        return False    
