# executable name
TARGET = app

# sources
MAIN = ./main.cpp
SRCS = ./src/*.cpp

# headers
INCLUDE = ./include/*.hpp

# compiler
CXX = g++

# compilation flags
CXXFLAGS = -Wall -std=c++17

# libraries
LIBS = -lglfw -lGLEW -lGL -lassimp


$(TARGET): $(SRCS)
	$(CXX) $(CXXFLAGS) -o ./bin/$(TARGET) $(MAIN) $(SRCS) -I$(INCLUDE) $(LIBS)

# cleaning
clean:
	rm -f $(TARGET)