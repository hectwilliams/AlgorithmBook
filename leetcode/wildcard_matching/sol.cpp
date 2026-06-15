/*
 
  Purpose: Solve leetcode problem

  Author: HW 

  URL: https://leetcode.com/problems/wildcard-matching/

  Note: This was daunting, until the dendrite connection  :) 

*/

#include <iostream>
#include <string>
#include <deque>
#include <regex>
#include <map>
#include <numeric>
#include<array>
#include<vector>



struct Node {
  std::string string;
  int depth;
  bool paths_set;
};

/**
 * Get rid of contigious 
 * 
 * @param seq Command sequence 
 * @param count Ref containing number of 'true' characters
 * @return Compressed sequence 
*/
std::string squeeze_any(std::string seq, int &count) {
    std::string s;
    
    count = 0;
    
    if (seq.length() == 0) 
        return seq;
    
    s += seq[0];
    
    if (seq[0] != '*'){
        count++;
 
    }
    
    for (int i = 1; i < seq.length(); i++) {
        
        if (s[s.length() - 1] == '*' && seq[i] == '*') {
            //skip
        } else {
            s += seq[i];
        }
        
        if (seq[i] != '*'){
            count++;
        }
    
    }
    
    return s; 
}



/**
 * Parse command string and concat/partition contigious commands into list.
 * The data stream should flow/match with the ordered commands list
 * 
 * @param p Commands string
 * @param table List containing tuple containing packed command and prev packed command 
*/
void set_eval_table(std::string p, std::vector< std::pair<std::string, std::string> > &table) {
    std::string buffer;
    bool read_mode = false;
    char prev = '*';
    bool any_mode = false ; 
    std::string prev_window; 
    
    for (int i = 0; i < p.length(); i++) {
        
       char curr = p[i];

       if (curr == '*') {
           
           
           if (buffer.length()) {
              table.push_back( {buffer, prev_window} );
              prev_window = std::string() + '*';
               buffer.clear();
           }

           if (i + 1 == p.length()) {
            table.push_back( {std::string{} + '*', ""} );
           }
           
           prev_window = std::string{} + '*';
           
       } else {
           
        if ( (curr=='?' && curr != prev ) || (prev == '?' && curr != prev)  ) {
            // handle start and end of wildcard '?'

            if (buffer.length()) {
                table.push_back(  {buffer, prev_window}  );
                prev_window = buffer;
                buffer.clear();
            }
        } 
        
        buffer.push_back(curr);
        
        if (i + 1== p.length()) {
            // tail reached
            table.push_back(  {buffer, prev_window}  );
        }
       
       }
       
       prev = curr;
       
    }
}


class Solution {
public:

    bool isMatch(std::string s, std::string p) {
        
        std::vector< std::pair<std::string, std::string> > eval_table;
        std::deque< Node * > s_queue;
        int num_unique_values = 0;        

        p = squeeze_any( p, num_unique_values );
        set_eval_table(p, eval_table);
                                
        // std::cout << "Commands -> p: "<< "\n";
        // for (const auto &[a, b]: eval_table) {
        //     std::cout << a << "," << b  <<  "\n";
        // }
        
        s_queue.push_back(new Node{s, 0, false}); // init buffer
        int target_index = 0;
        for (const auto &[target_str, prev_str]: eval_table) {
            
            int queue_len = s_queue.size();
            
            for (int i = 0; i < queue_len; i++) {
                
                // get test string 
                auto node = s_queue.front();
                s_queue.pop_front();
                std::string curr_string = node->string;
                int depth = node->depth;
                bool paths_set = node->paths_set;

                if ((prev_str == "") && (target_str == "*") ) {
                    
                    std::string ss_next = curr_string.substr( curr_string.length(), 0 );
                    s_queue.push_back( new Node{ss_next, depth + 1, paths_set } );
                    
                } else if (prev_str == "*") {
                    
                    // multiple matches in substring target
                    
                    if (target_str[0] == '?') {
                        
                        if (curr_string.length() == 0) {
                            delete node;
                            continue;
                        }
                        
                        if ( target_index  + 1 == eval_table.size() ) { 
                            // last substring 
                            
                            // one or more tail of '?' 
                            if(  curr_string.length()  >= target_str.length()   ) {
                                
                                std::string ss_next = curr_string.substr( curr_string.length(), curr_string.length()  ); // should produce an empty string 
                                s_queue.push_back(new Node{ss_next, depth + 1, paths_set });
                            }
                            
                        } else {
                            
                            // all excluding last substring 

                            if (depth == 0 || !paths_set) {
                                    
                                // convolutional sweep 
                                for (int n = 0; n < curr_string.length(); n++) {
                                    
                                    std::string test_string = curr_string.substr( n , curr_string.length() - n  ); // [*][][][] , [][*][][] , [][][*][]
                                    
                                    // skip n number of chatacers ABCDEC -- ?? -- > CDEC | DEC | EC
                                    if (test_string.length() >= target_str.length()) {
                                        
                                        std::string ss_next = test_string.substr( target_str.length(), test_string.length() - target_str.length()  );
                                
                                        s_queue.push_back(new Node{ss_next, depth + 1, paths_set });
                                    }
                                    
                                }
                                
                            } else {
                                
                                // skip n number of chatacers
                                 if (curr_string.length() >= target_str.length() /*target string is repeating '?' character */) {
                                    // requires n character available in current string 
                                    std::string ss_next = curr_string.substr( target_str.length(), curr_string.length() - target_str.length()  );
                                    s_queue.push_back(new Node{ss_next, depth + 1, paths_set });
                                 }
                            } 
                        }
                                
                    } else {
                        
                        
                        // all possible matches 
                        if ( target_index  + 1 == eval_table.size() ) { 
                            
                            // last sub string 
                          
                            size_t find_index = curr_string.rfind(target_str);
                            
                            if (find_index != std::string::npos) {
                                
                                find_index = static_cast<int>(find_index); 
    
                                // move to last match 
                                std::string analysis_str = curr_string.substr( find_index , curr_string.length() - find_index );
                                
                                std::string ss_next = analysis_str.substr( target_str.length(), analysis_str.length() - target_str.length()  );
                                
                                s_queue.push_back(new Node{ss_next, depth + 1, paths_set });
                                
                            }

                        } else if (depth == 0 || !paths_set) {
                            // create paths ( find all matching prefix of full sequence)
                            for (int n = 0; n < curr_string.length(); n++) {
                                std::string analysis_str = curr_string.substr( n , curr_string.length() - n );
                                auto find_index = analysis_str.find(target_str);
                                if (find_index != std::string::npos) {
                                    find_index = static_cast<int>(find_index); 
                                    if (find_index == 0) {
                                        // move forward past matching prefix 
                                        std::string ss_next = analysis_str.substr(target_str.length(), analysis_str.length() - target_str.length());
                                            std::cout << ss_next << "\n";
                                            s_queue.push_back(new Node{ss_next, depth + 1, true });
                                    }
                                }
                            }
                        } else {
                            // are next jump valid 
                            auto find_index = curr_string.find(target_str);
                            if (find_index != std::string::npos) {
                                find_index = static_cast<int>(find_index);
                                std::string analysis_str = curr_string.substr( find_index , curr_string.length() - find_index );
                                std::string ss_next = analysis_str.substr(target_str.length(), analysis_str.length() - target_str.length());
                                s_queue.push_back(new Node{ss_next, depth + 1, paths_set });
                            }
                        }
                        
                    }
                    
                } else {
                    
                    // single match of target substring?
                    if (target_str[0] == '?') {
                        // n number of prefix characters 
                        if ( curr_string.length() >= target_str.length()  ) {
                            // curr_string has n number of character available ( from prefix)
                            std::string ss_next = curr_string.substr(target_str.length(), curr_string.length() - target_str.length() );
                            s_queue.push_back(new Node{ss_next, depth + 1, paths_set });
                        }
                    } else {
                        // single prefix
                        auto find_index = curr_string.find(target_str);
                        
                        if (  find_index != std::string::npos  ) {
                            find_index = static_cast<int>(find_index);
                            
                            if (find_index == 0) {
                                // immediate match 
                                std::string analysis_str = curr_string.substr( find_index , curr_string.length() - find_index );
                                std::string ss_next = analysis_str.substr(target_str.length(), analysis_str.length() - target_str.length() );
                                s_queue.push_back(new Node{ss_next, depth + 1, paths_set });
                            }
                        }
                    }
                }
                
                delete node;
            }
            
            target_index += 1;

        }
        
        // validity test 
        bool found = false; 
        for(const auto &eval_node : s_queue) {
            found |= (eval_node->string.length() == 0 && eval_node->depth == eval_table.size());
        }
        return found;
           
    }
        
};
