# OpenGL Experiments
Features experimental code using OpenGL via GLEW, GLM, SDL2 and GLFW to test basic aspects of OpenGL and shading via glsl. The test code currently features:
  - Window creation
  - Shader compilation
  - Mesh creation (hard coaded vertices or .obj file loading)
  - Support for textures
  - 3D motion (translation, rotation and scaling)
  - Camera system with perspective projection
  - Lambertian shading

A test object and texture are provided in the resources file, along with a basic vertex and fragment shader.

### Install Guide

#### MacOS
```
brew install glew glm glfw sdl2
git clone https://github.com/fraserlove/opengl-expr.git
cd opengl-expr
make
```

#### Debian / Ubuntu
```
sudo apt install libglew-dev libglm-dev libglfw-dev livsdl2-dev
git clone https://github.com/fraserlove/opengl-expr.git
cd opengl-expr
make
```

#### Building from Source
```
$ git clone --recurse-submodules https://github.com/fraserlove/opengl-expr.git
$ cd opengl-expr
$ sudo make libs
$ make
```

The following shared libraries under `lib/` must be built before the main project can be built:
 - SDL `lib/SDL/build/.libs/libSDL2.dylib`
 - GLFW `lib/glfw/src/libglfw3.dylib`
 - GLEW `lib/glew/lib/libGLEW.dylib`

 The binary, once built with `make` can be found in `./build/bin`

OpenGL experimental code preview:

![Experimental code preview](https://i.imgur.com/0Regwp5.png)