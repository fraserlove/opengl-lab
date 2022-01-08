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
LDFLAGS = 
LDLIBS = 

ifeq ($(UNAME_S),Linux)
		LDFLAGS += -Wl
        LDLIBS += -Lusr/local/lib64 -Lusr/local/lib64 --enable-new-dtags -lSLD2 -lm -ldl -lpthread -lrt -lGLEW -lGL -lX11 -lGLU -lm -lGL -lglfw -lrt -lm -ldl
    endif
    ifeq ($(UNAME_S),Darwin)
        LDFLAGS += -lsdl2 -lGLEW -framework OpenGL
		LDLIBS += 
    endif

all: main

main: $(OBJ_FILES)
	@mkdir -p $(BIN)
	$(CC) $(LDFLAGS) $(OBJ_FILES) $(LDLIBS) -o $(BIN)/$(BUILD_NAME)

$(OBJ)/%.o: $(SRC)/%.cpp
	@mkdir -p $(OBJ)
	$(CC) $(CFLAGS) $(INCLUDE_PATHS) -c $< -o $@

libs:
	cd lib/glew && make
	cd lib/SDL && ./configure && make && make install
	cd lib/glfw && cmake . && make

clean:
	$(RM) -r $(BUILD_DIR)