#pragma once

#include <string>
#include <SDL2/SDL.h>

class Display {
private:
    SDL_Window* window;
    SDL_GLContext glcontext;

    bool isClosed;

public:
    Display(int width, int height, const char* title);
    virtual ~Display();

    void Clear(float r, float g, float b, float a);
    void SwapBuffers();
    bool IsClosed();
};