#ifndef EXPRESSIONTREE_H
#define EXPRESSIONTREE_H

#include "TreeNode.h"
#include "Stack.h"
#include <string>

class ExpressionTree {
private:
    TreeNode *root;
    Stack<TreeNode*> TreeNodeStack;  // Stack for treenode pointers
    Stack<char> opStack;  // Stack for operator char

public:
    // Constructor
    ExpressionTree();

    // Constructor that takes an expression string and constructs the tree
    ExpressionTree(const std::string &expression);

    // Method to build the tree from the expression
    bool buildTree(const std::string &expression);
    int precedence(char op);
    bool processOperator(char op, Stack<TreeNode*>& nodeStack);

    // Method to return the root of the tree
    TreeNode* getRoot();

    // Utility methods (like tree traversal for debugging or evaluation)
    void inOrderTraversal(TreeNode* node);
    void postOrderTraversal(TreeNode* node);
    void preOrderTraversal(TreeNode* node);

    
    ~ExpressionTree();

    void clearTree(TreeNode* node);

};

#endif