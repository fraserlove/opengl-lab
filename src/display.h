#pragma once

#include <SDL.h>
#include <string>

class Display {
private:
    SDL_Window* window;
    SDL_GLContext glcontext;

    bool isClosed;
    bool width;
    bool height;

public:
    Display(int width, int height, const std::string title);
    virtual ~Display();

    void Clear(float r, float g, float b, float a);
    void SwapBuffers();
    bool IsClosed();

    inline int getWidth() { return width; }
    inline int getHeight() { return height; }
    inline float getAspectRatio() { return (float) width / (float) height; }
};