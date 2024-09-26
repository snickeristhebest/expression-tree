#ifndef TREENODE_H
#define TREENODE_H

class TreeNode{
    private:
        TreeNode *left;
        TreeNode *right;
        char op;
        double num;
        bool flag;

    public:
        // Default constructor
        TreeNode();

    // Constructor with parameters
        TreeNode(char op, double num, bool flag);

        void set_left(TreeNode *left);
        TreeNode get_left();

        void set_right(TreeNode *right);
        TreeNode get_right();

        void set_op(char op);
        char get_op();

        void set_num(double num);
        double get_num();

        void set_flag(bool flag);
        bool get_flag();


};

#include "TreeNode.cpp"

#endif