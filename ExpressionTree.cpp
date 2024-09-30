#include "ExpressionTree.h"
#include <cctype>
#include <iostream>
#include <string>


// Constructor
ExpressionTree::ExpressionTree() : root(nullptr) {}

// Constructor that builds the tree from an expression
ExpressionTree::ExpressionTree(const std::string &expression) {
    if(!buildTree(expression)){
        std::cout << "error building tree for: " << expression << std::endl;
    }
    else{
        std::cout << "built tree for: " << expression << std::endl;
    }
}

bool ExpressionTree::buildTree(const std::string &expression) {
    Stack<TreeNode*> TreeNodeStack;
    Stack<char> opStack;
    std::string temp = "";
    
    for (std::size_t i = 0; i < expression.length(); i++) {
        if (expression[i] == ' ') {
            continue;  // Ignore spaces
        }
        if (i == 0 && (expression[i] == '+' || expression[i] == '-' || 
                       expression[i] == '*' || expression[i] == '/')) {
            // Invalid expression starting with an operator
            std::cerr << "Error: Expression cannot start with an operator at position " << i << std::endl;
            return false;
        }
        

        // Handle operators and opening parentheses
        if (expression[i] == '+' || expression[i] == '-' || 
            expression[i] == '*' || expression[i] == '/' || 
            expression[i] == '(') {
            
            // If a number is accumulated in `temp`, convert and push it
            if (!temp.empty()) {
                double num = stod(temp);  // Convert string to double
                temp = "";  // Reset temp for the next number
                TreeNode* newNode = new TreeNode('#', num, true);  // Create a TreeNode for the number
                TreeNodeStack.push(newNode);  // Push the number node to the stack
            }
            
            // Handle operator precedence before pushing the new operator
            while (!opStack.isEmpty() && precedence(opStack.top()) >= precedence(expression[i]) && expression[i] != '(') {
                if (!processOperator(opStack.pop(), TreeNodeStack)) {
                    return false;  // Error in tree construction
                }
            }
            
            opStack.push(expression[i]);  // Push the current operator or '('
        
        // Handle digits and decimal point
        } else if (isdigit(expression[i]) || expression[i] == '.') {
            temp += expression[i];  // Accumulate number characters

        // Handle closing parentheses
        } else if (expression[i] == ')') {
            if (!temp.empty()) {
                double num = stod(temp);
                temp = "";
                TreeNode* newNode = new TreeNode('#', num, true);
                TreeNodeStack.push(newNode);
            }
            
            // Process all operators until an opening parenthesis is found
            while (!opStack.isEmpty() && opStack.top() != '(') {
                if (!processOperator(opStack.pop(), TreeNodeStack)) {
                    return false;
                }
            }
            
            if (!opStack.isEmpty() && opStack.top() == '(') {
                opStack.pop();  // Remove the '('
            }
        }
    }
    
    // Final number processing after the loop ends
    if (!temp.empty()) {
        double num = stod(temp);
        TreeNode* newNode = new TreeNode('#', num, true);
        TreeNodeStack.push(newNode);
    }

    // Process remaining operators
    while (!opStack.isEmpty()) {
        if (!processOperator(opStack.pop(), TreeNodeStack)) {
            return false;
        }
    }

    // The final node in the TreeNodeStack is the root
    if (!TreeNodeStack.isEmpty()) {
        root = TreeNodeStack.top();
    }

    return true;
}

// Helper function to handle operator precedence
int ExpressionTree::precedence(char op) {
    if (op == '+' || op == '-') {
        return 1;
    } else if (op == '*' || op == '/') {
        return 2;
    } else {
        return 0;  // '(' has the lowest precedence
    }
}

// Helper function to process operators and update the expression tree
bool ExpressionTree::processOperator(char op, Stack<TreeNode*>& nodeStack) {
    if (nodeStack.size() < 2) {
        return false;  // Error: not enough operands for the operator
    }
    
    TreeNode* rightNode = nodeStack.pop();
    TreeNode* leftNode = nodeStack.pop();

    TreeNode* opNode = new TreeNode(op, 0.0, false);  // Create operator node
    opNode->set_left(leftNode);
    opNode->set_right(rightNode);

    nodeStack.push(opNode);  // Push the operator node back to the stack
    return true;
}


// Destructor to free all dynamically allocated memory
ExpressionTree::~ExpressionTree() {
    clearTree(root);
}

void ExpressionTree::clearTree(TreeNode* node) {
    if (node) {
        clearTree(node->get_left());
        clearTree(node->get_right());
        delete node;
    }
}

// void ExpressionTree::inOrderTraversal(TreeNode* node) {
//     if (node == nullptr) return;
//     inOrderTraversal(node->get_left());
//     if (node->get_flag())  // If it's a number node
//         std::cout << node->get_num() << " ";
//     else
//         std::cout << node->get_op() << " ";
//     inOrderTraversal(node->get_right());
// }

// // Post-order traversal (if needed)
// void ExpressionTree::postOrderTraversal(TreeNode* node) {
//     if (node == nullptr) return;
//     postOrderTraversal(node->get_left());
//     postOrderTraversal(node->get_right());
//     if (node->get_flag())
//         std::cout << node->get_num() << " ";
//     else
//         std::cout << node->get_op() << " ";
// }

// // Pre-order traversal (if needed)
// void ExpressionTree::preOrderTraversal(TreeNode* node) {
//     if (node == nullptr) return;
//     if (node->get_flag())
//         std::cout << node->get_num() << " ";
//     else
//         std::cout << node->get_op() << " ";
//     preOrderTraversal(node->get_left());
//     preOrderTraversal(node->get_right());
// }