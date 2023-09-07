CXX = /opt/homebrew/bin/g++-13
CXXFLAGS = -std=c++20 -Wall -pedantic-errors

SRC_DIR = src
OBJ_DIR = obj
OUT_DIR = out

TARGET = entry

# List of source files
SOURCES = $(wildcard $(SRC_DIR)/*.cpp)

# List of object files
OBJECTS = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SOURCES))

# | $(OBJ_DIR) indicates the current target depend on the target $(OBJ_DIR)
$(OBJ_DIR)/globals.o: $(SRC_DIR)/globals.cpp $(SRC_DIR)/globals.hpp | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJ_DIR)/lib.o: $(SRC_DIR)/lib.cpp $(SRC_DIR)/lib.hpp | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJ_DIR)/main.o: $(SRC_DIR)/main.cpp $(SRC_DIR)/lib.hpp $(SRC_DIR)/globals.hpp | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OUT_DIR)/$(TARGET): $(OBJECTS) | $(OUT_DIR)
	$(CXX) $(CXXFLAGS) -o $@ $^

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(OUT_DIR):
	mkdir -p $(OUT_DIR)

.PHONY: clean
clean:
	rm -rf $(OBJ_DIR) $(TARGET)

all: $(OUT_DIR)/$(TARGET)
