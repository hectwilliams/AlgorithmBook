/*
 
  Purpose: Solve leetcode problem

  Author: HW 

  URL: https://leetcode.com/problems/wildcard-matching/

*/


#include <iostream>
#include <string>
#include <deque>
#include <regex>
#include <map>
#include <numeric>
#include<array>
#include<vector>

const std::regex regex_pattern(R"(<(\d+)y>)"); 
const std::regex regex_pattern2(R"((<(\d+)>).+)"); 
const std::regex regex_pattern3(R"((^[a-z]\d+).+)"); 
const std::regex regex_pattern4(R"((^\*[a-z\?]).*)"); 
const std::regex regex_pattern5(R"((^[a-z]\*)$)"); 
const std::regex regex_pattern6(R"(^<(\d+)>)"); 
// const std::regex regex_all_wildcard(R"((^?+).*)"); 

struct SNode {
    std::string acc;
    std::string s;
    std::string p;
    std::map <char, int> indices;
    std::vector<SNode*> children;
    int depth;
    int depth2;
};


/**
 * Get rid of contigious 
 * 
 * @param seq String sequence 
 * @return new sequence 
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



std::string seq_xform(std::string s) {
    
    std::string data;
    int count = 0;
    char prev;
    char curr;
    
    if (s.length() == 0) {
        return s;
    }
    
    count +=1;
    prev = s[0];
    
    for(int i = 1; i < s.length(); i++) {
        
        curr = s[i];
        
        if (curr == prev) {
            count+= 1;
        }
        
        if  (i == s.length() - 1 ) {
            
            if (curr == prev) {
                if (curr == '*') {
                    data += prev;
                } else {
                    data += prev + std::to_string(count + 1);
                }
                
            } else if (curr != prev) {
                
                if (curr == '*') {
                    data += prev;
                    data += '*';
                } else {
                    // diff curr, prev
                    data += prev + std::to_string(count);
                    data += curr + std::to_string(1);
                }
            }
            
        } else if ( (curr != prev)   ) {
            data += prev + (prev == '*'? "": std::to_string(count) ) ;
            count = 1;
        }
        
        prev= curr;
        
    }
    
    return data;
    
}


void show_map(std::map<char, int> data) {
    for(const auto [key, value]: data) {
        std::cout << key << "," << value << "-------" << "\n";
    }
}


/**
 * Merge repeating *<> is command list
**/
std::string remove_greedy_pairs(std::string s, std::map<char, int> &map) {
    std::string s_out;
    int w = 0;
    while (w < s.length() ) {
        int w_eye = w;
        char c = s[w];
        
        if (s_out.length() > 1) {
            
            if (w + 1 < s.length() ) {
                char out_tail = s_out[s_out.length() - 1];
                char out_tail_prev = s_out[s_out.length() - 2];
                
                if (s[w] == s_out[s_out.length() - 2] &&  s[w + 1] == s_out[s_out.length() - 1]  && out_tail_prev == '*'  && out_tail != '?' ) {
                    // jump w
                    w += 2;
                    // continue;
                } else {
                    s_out += c;
                    w += 1;
                }
            } else {
                // last element
                s_out += c;
                w += 1;
            }
            
        } else {
            s_out += c;
            w += 1;
        }
        
       if ( s_out[s_out.length()-1] != '*' && w_eye + 1 == w ) {
           // does not capture skipped subset
            if (map.count( s_out[s_out.length()-1 ] ) == 0) {
                map[ s_out[ s_out.length() - 1] ] = 0;
            } 
            map[ s_out[ s_out.length() - 1]  ] += 1;
        }
        
    }
    // std::cout << s_out << "\n";
    return s_out; 
    
}


std::map<char, int> get_map(std::string s) {
    std::map<char, int> m;
    
    bool pause = false;
    for(const auto &c: s) {
        if (c == '<')
            pause = true;
        
        
        if (!pause) {
            
            if(c != '*') {
                if (m.count(c) ==0)
                    m[c] = 0;
                m[c] +=1;
            }
            
        }
        
        if (c == '>')
            pause = false;
    }
    return m;
}


bool valid_maps(std::string command, std::string data) {
    
    auto cmd_map = get_map(command);
    auto data_map = get_map(data);
    
    //   std::cout << command << "\n";
    //     std::cout << data << "\n";
            
    // for( const auto &[key, cmd_size_of_char ]: cmd_map ) {
    //     if (key == '*' || key == '?')
    //         continue;
    //     if(data_map.count(key) == 0)
    //         return false;
    //     int data_size_of_char = data_map[key];
    //     if (data_size_of_char < cmd_size_of_char /*data bin cannot absorb all of command bin */)
    //         return false;
    // }
    // return true;
    
        
    //   std::cout <<  "____T___ " << command << "\n";
    //   std::cout <<  "____T___ "  << data << "\n";
            
    for( const auto &[key_, cmd_size_of_char ]: cmd_map ) {
        
        if (key_ == '*' )
            continue;
            
        char key; 
        if ( key_ == '?') {
            // pluck a key from data_map
            key = data_map.begin()->first;
        } else {
            key = key_;
        }
        
        // std::cout << key << " TEST " << "\n";
        
        if ( data_map.count(key) == 0) {
            // no data available; violation
            return false;
        } else {
            data_map[key]--; 
            if (data_map.count(key) == 0) {
                data_map.erase(key);
            }
        }
        
    }
    return true;
    
    
}

int num_chars (std::string s) {
    int count = 0;
    for(const auto &c: s) {
        if (c!='*')
            count++;
    }
    return count; 
}

void set_eval_table(std::string p, std::vector< std::pair<std::string, std::string> > &table) {
    std::string buffer;
    bool read_mode = false;
    char prev = '*';
    bool any_mode = false ; 
    std::string prev_window; 
    
    for (int i = 0; i < p.length(); i++) {
        
       char curr = p[i];
       
       
    //   if (prev == '*') {
    //       any_mode = true;
    //   }
       
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

struct Node {
  std::string string;
  int depth;
  bool paths_set;
};

class Solution {
public:
 Solution() {root=nullptr;};
    SNode *root;


    bool isMatch(std::string s, std::string p) {
        
        std::smatch matches;
        std::deque<SNode*> q;
        int num_unique_values = 0;
        std::map <char, int> tmp;
        // std::map <std::string , void*> table;
        // std::vector< std::pair<std::string, bool> > table;
        std::map <int , int> dtable;
        
        
        if (root == nullptr) {
            p = squeeze_any( p, num_unique_values );
            // p = remove_greedy_pairs( p, tmp );
            std::cout << s << "\n";
            std::cout << p << "\n";
            q.push_back ( new SNode{"",s,p,tmp,{},0, 0} ) ;
            
        } 
        
        std::vector< std::pair<std::string, std::string> > eval_table;
        // std::deque< std::pair<std::string, int> > s_queue;
        std::deque< Node * > s_queue;

        set_eval_table(p, eval_table);
        
        int k = 0;
        
        std::string ss = s;
        
        bool match_count = true; 
        
        std::cout << "Commands -> p: "<< "\n";
        for (const auto &[a, b]: eval_table) {
            std::cout << a << "," << b  <<  "\n";
            
        }
        
        s_queue.push_back(new Node{ss, 0, false}); // init buffer
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
                
                
                std::cout << "TEST STRING: " << curr_string << "\n";
                std::cout << "TARGET: " << target_str << "\n";

                if ((prev_str == "") && (target_str == "*") ) {

                    // std::cout << "hello" << "\n";
                    std::string ss_next = curr_string.substr( curr_string.length(), 0 );
                    // std::cout << ss_next << "\n";
                    s_queue.push_back( new Node{ss_next, depth + 1, paths_set } );
                    
                } else if (prev_str == "*") {
                    
                    // multiple matches in substring target
                    
                    if (target_str[0] == '?') {
                        
                        if (curr_string.length() == 0) {
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
                            std::cout << 122;

                            if (depth == 0) {
                                    
                                // convolutional sweep 
                                for (int n = 0; n < curr_string.length(); n++) {
                                    
                                    std::string test_string = curr_string.substr( n , curr_string.length() - n  ); // [*][][][] , [][*][][] , [][][*][]
                                    
                                    // skip n number of chatacers ABCDEC -- ?? -- > CDEC | DEC | EC
                                    if (test_string.length() >= target_str.length()) {
                                        
                                        std::string ss_next = test_string.substr( target_str.length(), test_string.length() - target_str.length()  );
                                    
                                        // return 1;

                                    // if (ss_next.length()  >= num_unique_values) {
                                        s_queue.push_back(new Node{ss_next, depth + 1, paths_set });
                                        // s_queue.push_back({ss_next, depth + 1});
                                    // }
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
                        
                        if (depth == 0 || !paths_set) {
                            // create paths ( find all matching prefix of full sequence)
                            for (int n = 0; n < curr_string.length(); n++) {
                                std::string analysis_str = curr_string.substr( n , curr_string.length() - n );
                                auto find_index = analysis_str.find(target_str);
                                if (find_index != std::string::npos) {
                                    find_index = static_cast<int>(find_index); 
                                    if (find_index == 0) {
                                        // move forward past matching prefix 
                                        std::string ss_next = analysis_str.substr(target_str.length(), analysis_str.length() - target_str.length());
                                        // if (ss_next.length()  >= num_unique_values) {
                                            std::cout << ss_next << "\n";
                                            s_queue.push_back(new Node{ss_next, depth + 1, true });
                                        // }
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
                                std::cout << "TEST: \t" << ss_next  << "\t" << depth << " " << target_str << "\n";
                                    s_queue.push_back(new Node{ss_next, depth + 1, paths_set });
                                // std::cout << target_str << "\t" <<  curr_string <<  "\t" << find_index << ":" << ss_next <<"\n";
                                // std::cout << "TEST -> : " <<ss_next << "\n";
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
                        
                        std::cout << target_str << "\t" << curr_string << "\n";
                        
                        if (  find_index != std::string::npos  ) {
                            find_index = static_cast<int>(find_index);
                            
                            if (find_index == 0) {
                                // immediate match 
                                std::string analysis_str = curr_string.substr( find_index , curr_string.length() - find_index );
                                std::string ss_next = analysis_str.substr(target_str.length(), analysis_str.length() - target_str.length() );
                                // std::cout << "TEST: \t" << ss_next  << "\t" << depth << " " << target_str << "\n";
                                s_queue.push_back(new Node{ss_next, depth + 1, paths_set });
                            }
                        }
                    }
                }
            }
            
            target_index += 1;
        }
        
        
        bool found = false; 
        for(const auto &eval_node : s_queue) {
            found |= (eval_node->string.length() == 0 && eval_node->depth == eval_table.size());
        }
        return found;
           
    }
        
};

