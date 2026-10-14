# compiling target
TARGET = ./bin/app

# compiler
CXX = g++

# header files folder
INCLUDE = ./include

# compilation flags
CXXFLAGS = -Wall -std=c++17 -I$(INCLUDE)

# external libs
LIBS = -lglfw -lGLEW -lGL -lassimp

# folder where to put the object files
BUILD_DIR = .build

# entrypoint
MAIN = ./main.cpp

# source folder
SRC_DIR = ./src

# source files
SRCS = $(wildcard $(SRC_DIR)/*.cpp)

# building the object files
# $(patsubst pattern, substitution, text) 
# Finds words in text that match pattern and replaces them with replacement.
OBJS = $(BUILD_DIR)/main.o $(patsubst $(SRC_DIR)/%, $(BUILD_DIR)/src/%, $(SRCS:.cpp=.o))

# linking the built object files from BUILD_DIR
$(TARGET): $(OBJS)
	@mkdir -p ./bin
	$(CXX) $(OBJS) -o $(TARGET) $(LIBS)

# compiling main in BUILD_DIR
$(BUILD_DIR)/main.o: $(ENTRYPOINT)
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# compiling source files in BUILD_DIR
$(BUILD_DIR)/src/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf $(BUILD_DIR) $(TARGET)
