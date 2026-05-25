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
// #include <algorithm>

using WordBin = std::map<std::string, int>;
using Words = std::vector<std::string> ;
using StartIndices = std::vector<int> ;


/**
 * Zeros all eval bin and word count
 * 
 * @param bin Caller's accumulator evaluation bin 
 * @param word_count integer number 
 */
void reset_eval(WordBin &bin, int &word_count) {
     word_count = 0;
    for(const auto &[key, value]: bin) {
        bin[key] = 0;
    }
}
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
    WordBin wbin;
    WordBin wbin_zeroed;

    int word_length;
    
    /**
     * loads words into map
     * @param words List of words 
    */
    void map_words(const Words &words) {
        for (const std::string &w: words) {
            word_length = w.length();
            if (wbin.count(w) == 0 ) {
                wbin[w] = 0;
                wbin_zeroed[w] = 0;
            }
            wbin[w] += 1;
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
            return;
        }
        
         int start_of_index = 0;
         int i = 0;
         int j = 0;
         int r = -1;
         int word_hits = 0;
         WordBin wbin_eval = wbin_zeroed;

        // default code block
         while (i < s.length()) {
             
             // search for word 
             std::string test_word = s.substr(i, word_length);
   
             if (  wbin.count(test_word)  ) {

                 if ( wbin_eval[test_word] < wbin[test_word] ) {
                     // threshold not violated 
                     if (r == -1 ) {
                        r = i + 1;
                    }
                     
                     // increment bin for word 
                     wbin_eval[test_word] += 1;
                     
                    // found matching word ( jump ahead
                     i += word_length;
                     
                     // increment word_hit
                     word_hits +=1;
                    
                     if (word_hits == words.size()) {
                         // concat match found 
                         s_indices.push_back(start_of_index);
                         // move start index forward 
                         start_of_index = i;
                         // reset hits 
                         word_hits = 0;
                         // go back 
                         i = r;
                         start_of_index  = i;
                         // reset r
                         r = -1;
                         // reset eval bin
                        reset_eval(wbin_eval, word_hits);

                     } 
                     
                 } else {
                     // bin (word bin) overshoot (incorrect concatenation)
                     
                    // go back
                    i = r;
                    start_of_index = i;
                    r = -1;
                    reset_eval(wbin_eval, word_hits);
                 }
            } else {
                // found substring that is not part of index store 
                if (r == -1) {
                // searching for word
                    i+= 1;
                } else {
                    i = r; // go back  
                    r = -1; // reset 
                }
                start_of_index = i;
                reset_eval(wbin_eval, word_hits);
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
