#include "display.h"

#include <GL/glew.h>

int main() {

    Display display(800, 600, "OpenGL Test");

    while (!display.IsClosed()) {
        display.Clear(0.0f, 0.1f, 0.3f, 1.0f);
        display.SwapBuffers();
    }

    return 0;
}