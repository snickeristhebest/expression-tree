#include "TreeNode.h"

// Default constructor
TreeNode::TreeNode() {
    left = nullptr;
    right = nullptr;
    op = '\0';
    num = 0.0;
    flag = false;
}

// Parameterized constructor
TreeNode::TreeNode(char op, double num, bool flag) {
    left = nullptr;
    right = nullptr;
    this->op = op;
    this->num = num;
    this->flag = flag;
}

// Set the left child node
void TreeNode::set_left(TreeNode *left) {
    this->left = left;
}

// Get the left child node
TreeNode TreeNode::get_left() {
    return *left;  // Return the dereferenced pointer
}

// Set the right child node
void TreeNode::set_right(TreeNode *right) {
    this->right = right;
}

// Get the right child node
TreeNode TreeNode::get_right() {
    return *right;  // Return the dereferenced pointer
}

// Set the operator value
void TreeNode::set_op(char op) {
    this->op = op;
}

// Get the operator value
char TreeNode::get_op() {
    return op;
}

// Set the numeric value
void TreeNode::set_num(double num) {
    this->num = num;
}

// Get the numeric value
double TreeNode::get_num() {
    return num;
}

// Set the flag value
void TreeNode::set_flag(bool flag) {
    this->flag = flag;
}

// Get the flag value
bool TreeNode::get_flag() {
    return flag;
}