#pragma once // Prevents the header from being included more than once

#include <vector>

/*
    Purpose: solve leetcode 3Sum problem

    Author: HW 

    URL: https://leetcode.com/problems/3sum/

*/


const int N_SUM = 3;
const int N_SAMPLES = 3000;
const bool EN_DEBUG = false; 

struct Node ;
struct CNode;

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

// sorted combination tree node 

struct Tree {
    Node *root;
};

struct CTree {
    CNode *root;
};
// sorted combination tree node 
struct CNode {
    int value; 
    int accumulator;
    int index;
    CNode * left;
    CNode * right;
    CNode * prevnode;
    int count;
};

class Solution {
public:
    std::vector<Numbers > threeSum( Numbers& nums);
    friend std::ostream& operator<<(std::ostream& os, const Numbers&  numbers );
    friend std::ostream& operator<<(std::ostream& os, const NumbersArray&  numbers_2D);
    friend std::ostream& operator<<(std::ostream& os, const CNode *node);
};


bool read_three ( Numbers &data, CNode *node  );
int  sum_window_three (Numbers &a, Numbers &b, Numbers &c);
