CXX = clang++
CC  = clang

CXXFLAGS = -std=c++20 -Wall -Iglad/include -I./include
CFLAGS   = -Iglad/include
LIBS = -lGL -ldl -lglfw

SRC_DIR = src
OBJ_DIR = obj
BUILD_DIR = build
SHADERS_DIR = shaders

SRCS = $(shell find $(SRC_DIR) -name "*.cpp")
OBJS = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRCS))

GLAD_SRC = $(wildcard glad/src/*.c)
GLAD_OBJ = $(OBJ_DIR)/glad.o

TARGET = Velox

all: $(TARGET)

$(TARGET): $(OBJS) $(GLAD_OBJ)
	@echo "Linking objects $(TARGET)"
	$(CXX) $(OBJS) $(GLAD_OBJ) $(LIBS) -o $(TARGET)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(GLAD_OBJ): $(GLAD_SRC)
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

run: all
	./$(TARGET)

build: all
	@echo "Creating build directory..."
	mkdir -p $(BUILD_DIR)
	
	@echo "Copying resources..."
	cp $(TARGET) $(BUILD_DIR)/
	cp -r $(SHADERS_DIR) $(BUILD_DIR)/
	@echo "Build complete! Check the '$(BUILD_DIR)' folder."

clean:
	rm -rf $(OBJ_DIR) $(BUILD_DIR) $(TARGET)