# Name of the final executable
TARGET = ./bin/app

# Compiler
CXX = g++

# Compilation flags (C++17 and warnings enabled)
CXXFLAGS = -Wall -std=c++17

# Header directories: includes 'include', 'src', and its subdirectories
INCLUDE_FLAGS = -I./include \
                -I./src \
                -I./src/core \
                -I./src/graphics

# External libraries to link
LIBS = -lglfw -lGLEW -lGL -lassimp

# Directory for temporary object files
BUILD_DIR = .build

# AUTOMATICALLY finds all .cpp files inside 'src' and ANY of its subdirectories (including main.cpp)
SRCS = $(shell find ./src -name "*.cpp")

# Generates the list of .o files mirroring the structure of the .cpp files
OBJS = $(patsubst %.cpp, $(BUILD_DIR)/%.o, $(SRCS))

# Main rule: Executable linker
$(TARGET): $(OBJS)
	@mkdir -p ./bin
	$(CXX) $(OBJS) -o $(TARGET) $(LIBS)

# Generic rule to compile ANY .cpp file while maintaining the directory structure
$(BUILD_DIR)/%.o: %.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) $(INCLUDE_FLAGS) -c $< -o $@

# Clean up generated files
clean:
	rm -rf $(BUILD_DIR) ./bin

.PHONY: clean
