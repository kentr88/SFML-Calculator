# Makefile

# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -std=c++11 -Wall 

# Executable name
TARGET = run.exe

# Source files
SRCS = main.cpp

# Build and run tests
.PHONY: all
all:
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRCS) -lsfml-graphics -lsfml-window -lsfml-system
	./$(TARGET)

# Clean rule
.PHONY: clean
clean:
	rm -f $(TARGET)