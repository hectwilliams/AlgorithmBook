#include "Solution.h"
#include <vector>
#include <iostream>
#include <deque>
#include <map>

std::ostream& operator<<(std::ostream& os, const Numbers& numbers) {
    std::size_t i = 0;

     os << "[ ";
    for ( const auto &value: numbers ) {
        os << " " << value <<  ( (i  == numbers.size() - 1)? "" : "," ) ;
        i++;
    }
     os << " ]\n";

    return os; 

}

std::ostream& operator<<(std::ostream& os, const NumbersArray& numbers_2D) {
    
    for ( const auto &numbers: numbers_2D ) {
        os << numbers << "\n";
    }
    return os;

}

std::ostream& operator<<(std::ostream& os, const Node *node) {

     os << "[ ";
     
     os << node->prevnode->prevnode->value;
     
     os << ",";

     os << node->prevnode->value;
     
     os << ",";

     os << node->value;

     os << " ]\n";

     return os;

}

void read_three ( Numbers &data, Node *node  ) {
    data.push_back(node->prevnode->prevnode->value);
    data.push_back(node->prevnode->value);
    data.push_back(node->value);
}


std::vector<Numbers > Solution::threeSum(Numbers& nums) {
    std::map<std::vector<int>, bool> map;
    std::vector<Numbers > data_return;

    Tree tree{nullptr};

    for ( const auto &value : nums ) {

        if (!tree.root) {

            tree.root = new Node{ value, value, 1,  Children{}, nullptr };

        } else {

            std::deque< Node * > q;
            q.push_back(tree.root);

            while (!q.empty()) {
                Node *node = q.front();
                q.pop_front();

                // add children to queue if accumulation is < 3
                for (const auto &c : node->childnodes) {
                    if (c->count < 3) {
                        q.push_back(c);
                    }
                }

                // add value node to tree 
                Node * new_node = new Node {value, node->accumulator + value, node->count + 1, Children{}, node} ;
                node->childnodes.push_back(new_node);

                std::cout << new_node->value << " \t" << node->accumulator << " \t" <<  node->count << "\n";

                if (new_node->accumulator == 0 && new_node->count == N_SUM) {
                    std::cout << new_node;
                    Numbers data;
                    read_three(data, new_node);
                    if (map.count(data) == 0) {
                        data_return.push_back(data);
                        map[data] = true;
                    }

                }

            }

        }

    }

    return data_return;

}




