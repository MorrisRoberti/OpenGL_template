# Nome dell'eseguibile finale
TARGET = ./bin/app

# Compilatore
CXX = g++

# Flags di compilazione (C++17 e avvertimenti abilitati)
CXXFLAGS = -Wall -std=c++17

# Cartelle degli header: include sia 'include' che 'src' e le sue sotto-cartelle
INCLUDE_FLAGS = -I./include \
                -I./src \
                -I./src/core \
                -I./src/graphics

# Librerie esterne da linkare
LIBS = -lglfw -lGLEW -lGL -lassimp

# Cartella per i file oggetto temporanei
BUILD_DIR = .build

# Trova AUTOMATICAMENTE tutti i file .cpp dentro 'src' e in QUALSIASI sua sotto-cartella (incluso main.cpp)
SRCS = $(shell find ./src -name "*.cpp")

# Genera la lista dei file .o speculare alla struttura dei file .cpp
OBJS = $(patsubst %.cpp, $(BUILD_DIR)/%.o, $(SRCS))

# Regola principale: Linker dell'eseguibile
$(TARGET): $(OBJS)
	@mkdir -p ./bin
	$(CXX) $(OBJS) -o $(TARGET) $(LIBS)

# Regola generica per compilare QUALSIASI file .cpp mantenendo la struttura delle cartelle
$(BUILD_DIR)/%.o: %.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) $(INCLUDE_FLAGS) -c $< -o $@

# Pulizia dei file generati
clean:
	rm -rf $(BUILD_DIR) ./bin

.PHONY: clean
