#pragma once // Prevents the header from being included more than once

#include <vector>
/*
    Purpose: solve leetcode 3Sum problem

    Author: HW 

    URL: https://leetcode.com/problems/3sum/

*/

const int N_SUM = 3;

struct Node ;


using Numbers = std::vector<int>; 
using NumbersArray = std::vector<Numbers>;
using Children = std::vector<Node*>;

struct Node {
    int value;
    int accumulator; 
    int count;
    Children childnodes;
    Node * prevnode;
};

struct Tree {
    Node *root;
};

class Solution {
public:
    std::vector<Numbers > threeSum( Numbers& nums);
    friend std::ostream& operator<<(std::ostream& os, const Numbers&  numbers );
    friend std::ostream& operator<<(std::ostream& os, const NumbersArray&  numbers_2D);
    friend std::ostream& operator<<(std::ostream& os, const Node *node);
};


void read_three ( Numbers &data, Node *node  );
