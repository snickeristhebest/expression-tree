#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include "Stack.h"
#include "TreeNode.h"
#include "ExpressionTree.h"
using namespace std;


int main(int argc, char* argv[]) {
    
    ifstream inputFile1("expressions.txt");
    ifstream inputFile2("expressions_op.txt");


    if(!inputFile1.is_open()){
        cerr << "Error opening file 1!" << endl;
        return 1;
    } 

    if(!inputFile2.is_open()){
        cerr << "Error opening file 2!" << endl;
        return 1;
    } 

    string line;

    
    // Read file line by line
    while (getline(inputFile1, line)) {
        ExpressionTree tree = ExpressionTree(line);
        tree.displayResults();

    }    
    while (getline(inputFile2, line)) {
        ExpressionTree tree = ExpressionTree(line);
        tree.displayResults();

    }  

    // Close the file
    inputFile1.close();
    inputFile2.close();

    return 0;


}