CC = g++
CFLAGS = -Wall -g

SRC = src
BUILD_DIR = build
BUILD_NAME = main
OBJ = $(BUILD_DIR)/obj
BIN = $(BUILD_DIR)/bin
LIB = $(BUILD_DIR)/lib

SRC_FILES = $(wildcard $(SRC)/*.cpp)
OBJ_FILES = $(patsubst $(SRC)/%.cpp, $(OBJ)/%.o, $(SRC_FILES))
OBJ_FILES += lib/objloader/objloader.o

INCLUDE_PATHS = -Ilib/stb -Ilib/objloader -Ilib/glm -Ilib/glfw/include -Ilib/glew/include -Ilib/SDL/include

UNAME_S = $(shell uname -s)

# Shared libraries locations when built using 'make libs'. (-L specifies location of libraries, -l is to link them to the binary)
LDLIBS = -Llib/glew/build/lib/ -Llib/glfw/src/ -Llib/SDL/build/.libs/ -lGLEW -lglfw -lSDL2
# Since libraries are compiled locally within the project the executable has to be told the location of the libraries
LDLIBS += -Wl,-rpath,lib/glew/build/lib/ -Wl,-rpath,lib/glfw/src/ -Wl,-rpath,lib/SDL/build/.libs/


ifeq ($(UNAME_S), Darwin)
	LDLIBS += -framework OpenGL
endif

all: main

main: $(OBJ_FILES)
	@mkdir -p $(BIN)
	$(CC) $(LDFLAGS) $(OBJ_FILES) $(LDLIBS) -o $(BIN)/$(BUILD_NAME)

	ifeq ($(UNAME_S), Darwin)
		install_name_tool -id @rpath/libGLEW.dylib lib/glew/buildlib/libGLEW.dylib
		install_name_tool -id @rpath/libglfw.dylib lib/glfw/src/libglfw.dylib
		install_name_tool -id @rpath/libSDL2.dylib lib/SDL/build/.libs/libSDL2.dylib

		mv lib/glew/build/lib/*.dylib build/lib && cd lib/glew && make clean
		mv lib/glfw/src/*.dylib build/lib && cd lib/glfw && make clean
		mv lib/SDL/build/.libs/*.dylib build/lib && cd lib/SDL && make clean
	endif

	ifeq ($(UNAME_S), Linux)
		mv lib/glew/build/lib/*.dylib build/lib && cd lib/glew && make clean
		mv lib/glfw/src/*.dylib build/lib && cd lib/glfw && make clean
		mv lib/SDL/build/.libs/*.dylib build/lib && cd lib/SDL && make clean
	endif

$(OBJ)/%.o: $(SRC)/%.cpp
	@mkdir -p $(OBJ)
	$(CC) $(CFLAGS) $(INCLUDE_PATHS) -c $< -o $@

libs:
	@mkdir -p $(LIB)
	cd lib/glew/build && cmake ./cmake && make glew
	cd lib/glfw && cmake . -D BUILD_SHARED_LIBS=ON && make
	cd lib/SDL && ./configure --disable-static && make
	cd lib/objloader && $(CC) -I../glm -o objloader.o -c objloader.cpp

clean:
	$(RM) -r $(BUILD_DIR)