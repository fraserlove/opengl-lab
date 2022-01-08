CC = g++
CFLAGS = -Wall -g

SRC = src
BUILD_DIR = build
BUILD_NAME = main
OBJ = $(BUILD_DIR)/obj
BIN = $(BUILD_DIR)/bin

SRC_FILES = $(wildcard $(SRC)/*.cpp)
OBJ_FILES = $(patsubst $(SRC)/%.cpp, $(OBJ)/%.o, $(SRC_FILES))

INCLUDE_PATHS = -Ilib/stb -Ilib/objloader -Ilib/glm -Ilib/glfw/include -Ilib/glew/include -Ilib/SDL/include
LFLAGS = -lsdl2 -lGLEW -framework OpenGL

all: libs main

main: $(OBJ_FILES)
	@mkdir -p $(BIN)
	$(CC) $(LFLAGS) $(OBJ_FILES) -o $(BIN)/$(BUILD_NAME)

$(OBJ)/%.o: $(SRC)/%.cpp
	@mkdir -p $(OBJ)
	$(CC) $(CFLAGS) $(INCLUDE_PATHS) -c $< -o $@

libs:
	cd lib/glew/auto && make && cd .. && make install
	cd lib/SDL && ./configure && make && make install
	cd lib/glfw && cmake . && make

clean:
	$(RM) -r $(BUILD_DIR)