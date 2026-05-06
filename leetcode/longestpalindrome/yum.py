class Solution:
    def longestPalindrome(self, s: str) -> str:
        
        acc = ""

        palin_dict = {}
        npalin_dict = {} 
        substrings = [""] # init with zero sized string (oddly enough , this is a palindrome)
        ret_max = 0
        ret_str = "" 
        ispalin=False

        for i, ch in enumerate(s):
            
            for ss in substrings + []:  #rvalue 
                
                # add new substring with appended character 
                substrings += [ss + ch]
                current_string = substrings[-1]
                
                # test palindrome 
                if len(current_string) == 1:
                    palin_dict[current_string] = True 
    
                elif len(current_string) == 2:
                    if current_string[0] == current_string[1] :
                        palin_dict[current_string] = True 
                
                else :
                    # head and tail equal && characters between head and tail are palindrome
                    if current_string[0] == current_string[-1] and current_string[1: -1] in palin_dict:
                        palin_dict[current_string] = True 
            
                # test palin length 
                if current_string in palin_dict :
                    l = len(current_string)
                    if l > ret_max:
                        ret_max = l 
                        ret_str = current_string
            
            if i > 0:
                del substrings[1: i + 1]
        
        return ret_str     
            

