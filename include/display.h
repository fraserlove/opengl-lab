#pragma once

#include <SDL2/SDL.h>
#include <string>

class Display {
private:
    SDL_Window* window;
    SDL_GLContext glcontext;

    bool isClosed;

public:
    Display(int width, int height, const std::string title);
    virtual ~Display();

    void Clear(float r, float g, float b, float a);
    void SwapBuffers();
    bool IsClosed();
};