#include "ExpressionTree.h"
#include <cctype>
#include <iostream>
#include <string>

// Constructor
ExpressionTree::ExpressionTree() : root(nullptr), treeValid(false) {}

// Constructor that builds the tree from an expression
ExpressionTree::ExpressionTree(const std::string &expression) {
    std::cout << "_________________________________________________________" << std::endl;
    std::cout << "for expression: " << expression <<  std::endl;
    treeValid = buildTree(expression);  // Set treeValid based on buildTree result
    if (!treeValid) {
        std::cerr << "Error: Failed to build the tree" << std::endl;
    } else {
        std::cout << "Successfully built the tree" << std::endl;
    }
    std::cout << "_________________________________________________________" << std::endl;
}

// Function to build the tree from an expression
bool ExpressionTree::buildTree(const std::string &expression) {
    Stack<TreeNode*> TreeNodeStack;
    Stack<char> opStack;
    std::string temp = "";

    for (std::size_t i = 0; i < expression.length(); i++) {
        if (expression[i] == ' ') {
            continue;  // Ignore spaces
        }
        if (i == 0 && !(isdigit(expression[i]) || expression[i] == '(')) {
            std::cerr << "Error: Expression must start with a digit or '('. Invalid character at position " << i << ": " << expression[i] << std::endl;
            return false;
        }

        // Handle operators and opening parentheses
        if (expression[i] == '+' || expression[i] == '-' || 
            expression[i] == '*' || expression[i] == '/' || 
            expression[i] == '(') {
            
            // If a number is accumulated in `temp`, convert and push it
            if (!temp.empty()) {
                try {
                    double num = std::stod(temp);  // Convert string to double
                    temp = "";  // Reset temp for the next number
                    TreeNode* newNode = new TreeNode('#', num, true);  // Create a TreeNode for the number
                    TreeNodeStack.push(newNode);  // Push the number node to the stack
                } catch (...) {
                    std::cerr << "Error: Failed to convert number from string: " << temp << std::endl;
                    return false;
                }
            }
            
            // Handle operator precedence before pushing the new operator
            while (!opStack.isEmpty() && precedence(opStack.top()) >= precedence(expression[i]) && expression[i] != '(') {
                if (!processOperator(opStack.pop(), TreeNodeStack)) {
                    std::cerr << "Error: Failed to process operator: " << expression[i] << std::endl;
                    return false;
                }
            }
            
            opStack.push(expression[i]);  // Push the current operator or '('
        
        // Handle digits and decimal point
        } else if (isdigit(expression[i]) || expression[i] == '.') {
            temp += expression[i];  // Accumulate number characters

        // Handle closing parentheses
        } else if (expression[i] == ')') {
            if (!temp.empty()) {
                try {
                    double num = std::stod(temp);
                    temp = "";
                    TreeNode* newNode = new TreeNode('#', num, true);
                    TreeNodeStack.push(newNode);
                } catch (...) {
                    std::cerr << "Error: Failed to convert number from string: " << temp << std::endl;
                    return false;
                }
            }
            
            // Process all operators until an opening parenthesis is found
            while (!opStack.isEmpty() && opStack.top() != '(') {
                if (!processOperator(opStack.pop(), TreeNodeStack)) {
                    std::cerr << "Error: Failed to process operator inside parentheses." << std::endl;
                    return false;
                }
            }
            
            if (!opStack.isEmpty() && opStack.top() == '(') {
                opStack.pop();  // Remove the '('
            } else {
                std::cerr << "Error: Mismatched parentheses in expression." << std::endl;
                return false;
            }
        } else {
            std::cerr << "Error: Invalid character '" << expression[i] << "' in expression." << std::endl;
            return false;
        }
    }
    
    // Final number processing after the loop ends
    if (!temp.empty()) {
        try {
            double num = std::stod(temp);
            TreeNode* newNode = new TreeNode('#', num, true);
            TreeNodeStack.push(newNode);
        } catch (...) {
            std::cerr << "Error: Failed to convert number from string: " << temp << std::endl;
            return false;
        }
    }

    // Process remaining operators
    while (!opStack.isEmpty()) {
        if (!processOperator(opStack.pop(), TreeNodeStack)) {
            std::cerr << "Error: Failed to process remaining operators." << std::endl;
            return false;
        }
    }

    // The final node in the TreeNodeStack is the root
    if (!TreeNodeStack.isEmpty()) {
        root = TreeNodeStack.top();
    } else {
        std::cerr << "Error: Tree node stack is empty after processing." << std::endl;
        return false;
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
        std::cerr << "Error: Not enough operands for the operator '" << op << "'." << std::endl;
        return false;
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

double ExpressionTree::solve() {
    if (!treeValid) {
        std::cerr << "Error: Cannot solve an invalid expression tree." << std::endl;
        return 0;  // Return a default error value
    }
    return solve(root);  // Call the helper function starting from the root
}

// Helper function to recursively evaluate the expression tree
double ExpressionTree::solve(TreeNode* node) {
    if (node->get_flag()) {  // If it's a number node, return the number
        return node->get_num();
    }

    double leftValue = solve(node->get_left());
    double rightValue = solve(node->get_right());

    char op = node->get_op();
    switch (op) {
        case '+':
            return leftValue + rightValue;
        case '-':
            return leftValue - rightValue;
        case '*':
            return leftValue * rightValue;
        case '/':
            if (rightValue == 0) {
                std::cerr << "Error: Division by zero." << std::endl;
                return 0;  // Handle division by zero error
            }
            return leftValue / rightValue;
        default:
            std::cerr << "Error: Invalid operator '" << op << "' in expression tree." << std::endl;
            return 0;
    }
}

// Function to display the calculated value and traversal orders
void ExpressionTree::displayResults() {
    if (!treeValid) {
        std::cerr << "Error: Cannot display results for an invalid expression tree." << std::endl;
        return;
    }

    double result = solve();
    std::cout << "_______________________" << std::endl;
    std::cout << "Calculated value: " << result << std::endl;

    std::cout << "Infix (In-order) expression: ";
    inOrderTraversal(root);
    std::cout << std::endl;

    std::cout << "Prefix (Pre-order) expression: ";
    preOrderTraversal(root);
    std::cout << std::endl;

    std::cout << "Postfix (Post-order) expression: ";
    postOrderTraversal(root);
    std::cout << std::endl;
    std::cout << "_______________________" << std::endl;
}

// In-order traversal (infix expression)
void ExpressionTree::inOrderTraversal(TreeNode* node) {
    if (node == nullptr) return;

    inOrderTraversal(node->get_left());

    if (node->get_flag())  // If it's a number node
        std::cout << node->get_num() << " ";
    else
        std::cout << node->get_op() << " ";

    inOrderTraversal(node->get_right());
}

// Pre-order traversal (prefix expression)
void ExpressionTree::preOrderTraversal(TreeNode* node) {
    if (node == nullptr) return;

    if (node->get_flag())
        std::cout << node->get_num() << " ";
    else
        std::cout << node->get_op() << " ";

    preOrderTraversal(node->get_left());
    preOrderTraversal(node->get_right());
}

// Post-order traversal (postfix expression)
void ExpressionTree::postOrderTraversal(TreeNode* node) {
    if (node == nullptr) return;

    postOrderTraversal(node->get_left());
    postOrderTraversal(node->get_right());

    if (node->get_flag())
        std::cout << node->get_num() << " ";
    else
        std::cout << node->get_op() << " ";
}
