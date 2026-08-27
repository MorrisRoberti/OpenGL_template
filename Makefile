# Nome dell'eseguibile
TARGET = app

# File sorgente
MAIN = ./main.cpp
SRCS = ./src/*.cpp

# Headers
INCLUDE = ./include/*.hpp

# Compilatore
CXX = g++

# Flag di compilazione
CXXFLAGS = -Wall -std=c++17

# Librerie da linkare
LIBS = -lglfw -lGLEW -lGL 


$(TARGET): $(SRCS)
	$(CXX) $(CXXFLAGS) -o ./bin/$(TARGET) $(MAIN) $(SRCS) -I$(INCLUDE) $(LIBS)

# Pulizia
clean:
	rm -f $(TARGET)