# OpenGL Experiments
Features experimental code using OpenGL via GLEW, GLM, SDL2 and GLFW. The test code currently features:
  - Window creation
  - Shader compilation
  - Mesh creation: either through hard coaded vertices or by loading from obj file
  - Support for textures
  - 3D motion (translation, rotation and scaling)
  - Camera system with perspective projection
  - Lambertian Shading
Since the purpose of this project is to experiment with OpenGL, 3rd party code for loading .obj files and images was used (stb_image.h, obj_loader.h and obj_loader.cpp). A test object and texture are provided in the resources file, along with a basic vertex and fragment shader.

OpenGL experimental code preview:
![](https://imgur.com/a/P97e60j)