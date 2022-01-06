#include "display.h"

#include <GL/glew.h>
#include <iostream>

Display::Display(int width, int height, const std::string title) {

    SDL_Init(SDL_INIT_EVERYTHING);

    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);
    // Double buffering. Sepatate buffers for OpenGL draw and window display, these buffers swap. 
    // Hence window never displays something in the process of being drawn.
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

    window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL);
    glcontext = SDL_GL_CreateContext(window);

    glewExperimental = GL_TRUE; // Fixed issue with GLEW when calling glGenVertexArrays. Driver/GLEW version specific issue
    GLenum status = glewInit();

    if (status != GLEW_OK)
        std::cerr << "Glew failed to initialise." << std::endl;

    isClosed = false;
}

Display::~Display() {

    SDL_GL_DeleteContext(glcontext);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

bool Display::IsClosed() {

    return isClosed;
}

void Display::SwapBuffers() {
    
    SDL_GL_SwapWindow(window);

    SDL_Event e;

    while (SDL_PollEvent(&e)) {
        if (e.type == SDL_QUIT)
            isClosed = true;
    }
}

void Display::Clear(float r, float g, float b, float a) {

    glClearColor(r, g, b, a);
    glClear(GL_COLOR_BUFFER_BIT);
}