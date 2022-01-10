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

# Shared libraries locations when built using 'make libs'. (-L specifies location of libraries, -l is to link them to the binary)
LDLIBS = -Llib/glew/lib/ -Llib/glfw/src/ -Llib/SDL/build/.libs/ -lGLEW -lglfw -lSDL2
# Since libraries are compiled locally within the project the executable has to be told the location of the libraries
LDLIBS += -Wl,-rpath,lib/glew/lib/ -Wl,-rpath,lib/glfw/src/ -Wl,-rpath,lib/SDL/build/.libs/
#LDLIBS += -Wl,-rpath,build/bin/

ifeq ($(UNAME_S), Linux)
	# pass
endif

ifeq ($(UNAME_S), Darwin)
	LDLIBS += -framework OpenGL
endif

all: main

main: $(OBJ_FILES)
	@mkdir -p $(BIN)
	cp lib/glew/lib/libGLEW.2.2.0.dylib build/bin/libGLEW.dylib
	cp lib/SDL/build/.libs/libSDL2-2.0.0.dylib build/bin/libSDL2.dylib
	cp lib/glfw/src/libglfw.3.4.dylib build/bin/libglfw.dylib
	install_name_tool -id @rpath/libSDL2.dylib lib/SDL/build/.libs/libSDL2.dylib
	install_name_tool -id @rpath/libglfw.dylib lib/glfw/src/libglfw.dylib
	install_name_tool -id @rpath/libGLEW.dylib lib/glew/lib/libGLEW.dylib
	$(CC) $(LDFLAGS) $(OBJ_FILES) $(LDLIBS) -o $(BIN)/$(BUILD_NAME)

$(OBJ)/%.o: $(SRC)/%.cpp
	@mkdir -p $(OBJ)
	$(CC) $(CFLAGS) $(INCLUDE_PATHS) -c $< -o $@

libs:
	cd lib/glew/auto && make && cd .. && make glew.lib.shared
	cd lib/SDL && ./configure && make
	cd lib/glfw && cmake . -D BUILD_SHARED_LIBS=ON && make
	cd lib/objloader && $(CC) -I../glm -o objloader.o -c objloader.cpp

clean:
	$(RM) -r $(BUILD_DIR)