/*
  
  Purpose: Solve leetcode problem; only hard problems over here :). 

  URL:  https://leetcode.com/problems/permutation-sequence/

  Author: HW

*/

#include <iostream>
#include <string> 

unsigned long long recursiveFactorial(int n) {
    if (n < 0) return 0;  // Error handling for negative input
    if (n <= 1) return 1; // Base case: 0! and 1! are equal to
    
    return n * recursiveFactorial(n - 1);
}

std::string first_perm(int n) {
    std::string s;
    for(int i = 1; i <= n; i++) {
        s += std::to_string(i);
    }
    return s; 
}

class Solution {
    
public:
    std::string getPermutation(int n, int k) {
        
        std::string first_permutation = first_perm(n);

        if (n == 1) {
            return first_permutation;    
        }
        
        int n_perms = recursiveFactorial(n);
        
        auto  chars = first_permutation; 
        
        std::string acc;
        
        int n_samples_per_row_block = n_perms / n;
        
        int k_dynamic = k - 1;
        
        int row_block_index = k_dynamic / n_samples_per_row_block;
        
        for (int i = 0; i < n; i++) {
            
            
            acc += chars[row_block_index];
            
            chars = chars.substr(0, row_block_index) + chars.substr(row_block_index + 1, chars.length());
            
            if (i == n - 1) {
                acc += chars.substr(0, 1);    
                break;
            }
            
            k_dynamic = k_dynamic - row_block_index * n_samples_per_row_block;
            
            n_samples_per_row_block = n_samples_per_row_block / chars.length();
            
            row_block_index = k_dynamic / n_samples_per_row_block;
  
        }
        
        return acc;
    }
};

int main() {
    
    Solution sol = Solution();
    
    std::string s = sol.getPermutation(5, 37);
    
    std::cout << " solution: " << s << "\n";
    
    return 0;
    
}
