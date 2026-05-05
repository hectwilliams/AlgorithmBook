
class Solution:

    def lengthOfLongestSubstring(self,s: str) -> int:
            
        d = {}

        max_length = 1 if len(s) else 0 

        acc = "" 

        for i,ch in enumerate(s):
            
            # remove repeated char
            
            idx_found = acc.find(ch)
            
            # head case 
            if (idx_found == 0):
                acc = acc[1:] 
                
            # middle case 
            elif idx_found > 0 and idx_found < len(acc) - 1:
                acc = acc[idx_found + 1:]
            
            # tail case 
            elif idx_found == len(acc) - 1:
                acc = ""
                
            # append char 
            
            acc += ch
            
            if len(acc) > max_length:
                max_length = len(acc)
            

        return max_length
