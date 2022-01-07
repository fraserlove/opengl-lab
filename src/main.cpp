#include "display.h"
#include "shader.h"
#include "mesh.h"
#include "texture.h"

int main() {

    Display display(800, 600, "OpenGL Test");
    Shader shader("./res/shader");
    Vertex vertices[] = { Vertex(glm::vec3(-0.5, -0.5, 0), glm::vec2(0.0, 0.0)),
                          Vertex(glm::vec3(0, 0.5, 0), glm::vec2(0.5, 1.0)),
                          Vertex(glm::vec3(0.5, -0.5, 0), glm::vec2(1.0, 0.0)) };
    Mesh mesh(vertices, sizeof(vertices)/ sizeof(vertices[0]));
    Texture texture("./res/texture.jpg");

    while (!display.IsClosed()) {
        display.Clear(0.0f, 0.1f, 0.3f, 1.0f);

        shader.Bind();
        texture.Bind(0);
        mesh.Draw();

        display.SwapBuffers();
    }

    return 0;
}