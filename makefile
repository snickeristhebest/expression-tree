# Define variables
CXX = g++
CXXFLAGS = -Wall -std=c++17
TARGET = main
SRC = main.cpp ExpressionTree.cpp TreeNode.cpp
HEADERS = Stack.h TreeNode.h ExpressionTree.h

# Default rule to build the executable
$(TARGET): $(SRC) $(HEADERS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC)

# Clean rule to remove generated files
clean:
	rm -f $(TARGET)