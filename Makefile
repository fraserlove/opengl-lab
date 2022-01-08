CC = g++
CFLAGS = -Wall -g

SRC = src
BUILD_DIR = build
BUILD_NAME = main
OBJ = $(BUILD_DIR)/obj
BIN = $(BUILD_DIR)/bin

SRC_FILES = $(wildcard $(SRC)/*.cpp)
OBJ_FILES = $(patsubst $(SRC)/%.cpp, $(OBJ)/%.o, $(SRC_FILES))
OBJ_FILES += lib/objloader/objloader.o

INCLUDE_PATHS = -Ilib/stb -Ilib/objloader -Ilib/glm -Ilib/glfw/include -Ilib/glew/include -Ilib/SDL/include

UNAME_S = $(shell uname -s)

# Dynamically linked libraries - locations when built using make libs
LDLIBS = lib/glew/lib/libGLEW.so lib/glfw/src/libglfw3.so lib/SDL/build/.libs/libSDL2.so

ifeq ($(UNAME_S), Linux)
	# pass
endif

ifeq ($(UNAME_S), Darwin)
	# Dynamically linked libraries - locations when built using make libs
	LDLIBS = lib/glew/lib/libGLEW.dylib lib/glfw/src/libglfw3.dylib lib/SDL/build/.libs/libSDL2.dylib
endif

all: main

main: $(OBJ_FILES)
	@mkdir -p $(BIN)
	$(CC) $(LDFLAGS) $(OBJ_FILES) $(LDLIBS) -o $(BIN)/$(BUILD_NAME)

$(OBJ)/%.o: $(SRC)/%.cpp
	@mkdir -p $(OBJ)
	$(CC) $(CFLAGS) $(INCLUDE_PATHS) -c $< -o $@

libs:
	cd lib/glew/auto && make glew.lib && cd .. && make
	cd lib/SDL && ./configure && make
	cd lib/glfw && cmake . -D BUILD_SHARED_LIBS=ON && make
	cd lib/objloader && $(CC) -I../glm -o objloader.o -c objloader.cpp

clean:
	$(RM) -r $(BUILD_DIR)