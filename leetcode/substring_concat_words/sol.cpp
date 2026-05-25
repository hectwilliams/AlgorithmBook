/*

  Purpose: Solve substring with concat of all words ( hard leetcode) 

  Author: HW

  LeetcodeURL: https://leetcode.com/problems/substring-with-concatenation-of-all-words/

*/

#include <iostream>
#include <string>
#include <deque>
#include <vector>
#include <map>
#include <algorithm>
#include <array>


using CMap = std::map<char, void*>;
using WordMap = std::map<std::string, int>;
using Words = std::vector<std::string> ;
using StartIndices = std::vector<int> ;



struct Node {
    int start;
    std::string s;
    int depth;
    WordMap wbin;
};

/**
* Parsers string and words to determine if simple convolution sweep 
* may be used to support caller's routine. If the string consist of a repeating 
* single character and the words contain strings strings of width 1 with the same character
* convolutional can be used. 
* 
*@param s String 
*@param words List of words 
*@returns tuple of width 2, containing the number of repeating single characters from both s and words. If they are not repeating return -1 for both array slots
*/


std::array<int, 2> discrete_mode(std::string s, Words &words) {

    std::array<int,2 > result{0,0};
    char c;
    if (s.length() != 0 && words.size() != 0){
        
        c = s[0];
        int slen = 0;
        int wlen = 0;
        int threshold = s.length() + words.size();
        
        for (int i= 0; i < threshold ; i++) {
            
            if (slen < s.length()) {
                result[0] += +(c == s[slen]);
                slen++;
            }

            if (wlen < words.size()) {
                std::string w = words[wlen];
                result[1] += +(c == w[0] && w.length()==1);
                wlen++;
            }

        }

    } else {
        result[0] = -1;
        result[1] = -1;
    }
    
    return result;
    
}

class Solution {
    CMap cmap;
    WordMap wmap;
    int word_len;
    
    
    /**
     * loads words into map
     * @param words List of words 
    */
    void map_words(const Words &words) {
        for (const std::string &w: words) {
            if(wmap.count(w) == 0)
                wmap[w] = 0;
            wmap[ w ] += 1;
            cmap[ w[0] ] = nullptr;
            word_len = w.length();
        } 
    }
    
    /**
     * solver for findSubstring caller
     * 
     *@param s String which may contain concatenation of words 
     *@param words List of words
     *@param indices List of indices indicating starting positions for concatenated words
     */
     
     void solver(std::string s, Words& words, StartIndices &s_indices) {
       
       
       
        // quick convolution code block
        std::array<int,2> conv_tuple = discrete_mode(s, words);
        if (conv_tuple[0] == s.length()  && conv_tuple[1] == words.size()) {
            int limit = (conv_tuple[0] - conv_tuple[1]) + 1;
            for(int k = 0; k < limit; k++ ) {
                s_indices.push_back(k);
            }
        } else {
            // default code block 
            std::deque<Node*> q;
            
            // init queue 
            for(int i = 0; i < s.length(); i++) {
               if ( cmap.count(s[i]) ) {
                   // potential concat string start at this index 
                   q.push_back( new Node{i, s.substr(i, s.length()) , 0, {}} );
               }
            }
            
            int depth = 0;
            while (!q.empty()) {
               Node * node = q.front();
               q.pop_front();
               
               std::string test_string = node->s.substr(0, word_len);
                
               if (node->depth == words.size()) {
                   s_indices.push_back(node->start);
                   delete node;    
                   
               } else if ( wmap.count(test_string) ) {
                   // a valid word
                   
                   if (node->wbin.count(test_string) == 0) {
                       // add word to nodes bin map
                       node->wbin[test_string] = 0;
                   }
                   
                   if( node->wbin[test_string] < wmap[test_string] ) {
                       
                       node->wbin[test_string] += 1; 
                       // available for concat string
                       node->depth += 1;
                       //truncate valid word (header)
                       node->s = node->s.substr(word_len, node->s.length() - 1 );
                       q.push_back(node);
                   }
                   
               } else {
                   delete node;     
               }
              
            }   
        
        }

    }

public:
    vector<int> findSubstring(string s, vector<string>& words) {
        map_words(words);
        StartIndices si;
        solver(s, words, si);
        return si;
    }
};
