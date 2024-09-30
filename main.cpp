#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include "Stack.h"
#include "TreeNode.h"
#include "ExpressionTree.h"
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

    
    // Read file line by line
    while (getline(inputFile, line)) {
        ExpressionTree tree = ExpressionTree(line);
    }    

    // Close the file
    inputFile.close();

    return 0;


}