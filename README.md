# OpenGL Experiments
Features experimental code using OpenGL via GLEW, GLM, SDL2 and GLFW. The test code currently features:
  - Window creation
  - Shader compilation
  - Mesh creation (hard coaded vertices or .obj file loading)
  - Support for textures
  - 3D motion (translation, rotation and scaling)
  - Camera system with perspective projection
  - Lambertian shading
Since the purpose of this project is to experiment with OpenGL, 3rd party code for loading .obj files and images is used (stb_image.h, obj_loader.h and obj_loader.cpp). A test object and texture are provided in the resources file, along with a basic vertex and fragment shader.

OpenGL experimental code preview:
![Experimental code preview](https://i.imgur.com/0Regwp5.png)