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

### Building

```
$ git clone --recurse-submodules https://github.com/jdah/minecraft-weekend.git
$ cd opengl-expr
$ sudo make
```

The following static libraries under `lib/` must be built before the main project can be built:
 - SDL ' 
 - GLFW `lib/glfw/src/libglfw3.a`
 - GLEW `lib/glew/lib/libGLEW.a`

OpenGL experimental code preview:

![Experimental code preview](https://i.imgur.com/0Regwp5.png)