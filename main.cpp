#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include "Stack.h"
#include "TreeNode.h"
using namespace std;


int main(int argc, char* argv[]) {
    
    ifstream inputFile("expressions.txt");
    Stack<TreeNode*> TreeNodeStack;  // Stack for treenode pointers
    Stack<char> opStack;  // Stack for operator char

    if(!inputFile.is_open()){
        cerr << "Error opening file!" << endl;
        return 1;
    } 

    string line;

    cout << "File Content: " << endl;
    while (getline(inputFile, line)) {
        cout << line << endl; // Print the current line
    }

    // Close the file
    inputFile.close();

    opStack.push('*');
    opStack.push('+');
    std::cout << "Top of opStack: " << opStack.top() << std::endl;  // Output: 20

    TreeNode *node1 = new TreeNode();
    TreeNode *node2 = new TreeNode('+',3.3,true);

    TreeNodeStack.push(node1);
    TreeNodeStack.push(node2);
   
    std::cout << "Top of TreeStack: " << TreeNodeStack.top()->get_num() << std::endl;  // Output: World

    TreeNodeStack.pop();
    std::cout << "Top of TreeStack after pop: " << TreeNodeStack.top()->get_num() << std::endl;  // Output: 10

    return 0;


}