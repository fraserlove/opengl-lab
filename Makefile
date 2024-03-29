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

INCLUDE_PATHS = -Ilib/objloader -Ilib/stb

INCLUDE_PATHS += -Ilib/glm -Ilib/glfw/include -Ilib/glew/include -Ilib/SDL/include

LIB_EXT = .so
LDLIBS = -lGLEW -lglfw -lSDL2

LDLIBS += -Wl,-rpath,lib/glew/lib/ -Wl,-rpath,lib/glfw/src/ -Wl,-rpath,lib/SDL/build/.libs/
LDLIBS += -Llib/glew/lib/ -Llib/glfw/src/ -Llib/SDL/build/.libs/

UNAME_S = $(shell uname -s)


ifeq ($(UNAME_S), Darwin)
	# Showing the binary the location of the libraries
	LDLIBS += -framework OpenGL
	LIB_EXT = .dylib
endif

ifeq ($(UNAME_S), Linux)
	LDLIBS += -lGL
endif

all: main

main: $(OBJ_FILES)
	@mkdir -p $(BIN)
	cd lib/objloader && $(CC) -I../glm -o objloader.o -c objloader.cpp
	$(CC) $(LDFLAGS) $(OBJ_FILES) $(LDLIBS) -o $(BIN)/$(BUILD_NAME)

$(OBJ)/%.o: $(SRC)/%.cpp
	@mkdir -p $(OBJ)
	$(CC) $(CFLAGS) $(INCLUDE_PATHS) -c $< -o $@

libs:
	cd lib/glew/auto && make && cd .. && make glew.lib.shared
	cd lib/glfw && cmake . -D BUILD_SHARED_LIBS=ON && make
	cd lib/SDL && ./configure --disable-static && make && mkdir include/SDL2 && mv include/*.h include/SDL2

ifeq ($(UNAME_S), Darwin)
	install_name_tool -id @rpath/libGLEW.dylib lib/glew/lib/libGLEW.dylib
	install_name_tool -id @rpath/libglfw.dylib lib/glfw/src/libglfw.dylib
	install_name_tool -id @rpath/libSDL2.dylib lib/SDL/build/.libs/libSDL2.dylib
endif

clean:
	$(RM) -r $(BUILD_DIR)