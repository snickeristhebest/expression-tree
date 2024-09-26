# Define variables
CXX = g++
CXXFLAGS = -Wall -std=c++17
TARGET = main
SRC = main.cpp  # Main source file
HEADERS = Stack.h  TreeNode.h# Header files (if needed for dependencies)

# Default rule to build the executable
$(TARGET): $(SRC) $(HEADERS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC)

# Clean rule to remove generated files
clean:
	rm -f $(TARGET)
