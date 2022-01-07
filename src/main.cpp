#include "display.h"
#include "shader.h"
#include "mesh.h"
#include "texture.h"
#include "transform.h"

int main() {

    Display display(800, 600, "OpenGL Test");
    Shader shader("./res/shader");
    Vertex vertices[] = { Vertex(glm::vec3(-0.5, -0.5, 0), glm::vec2(0.0, 0.0)),
                          Vertex(glm::vec3(0, 0.5, 0), glm::vec2(0.5, 1.0)),
                          Vertex(glm::vec3(0.5, -0.5, 0), glm::vec2(1.0, 0.0)) };
    Mesh mesh(vertices, sizeof(vertices) / sizeof(vertices[0]));
    Texture texture("./res/texture.jpg");
    Transform transform;

    float i = 0.0f;

    while (!display.IsClosed()) {
        display.Clear(0.0f, 0.1f, 0.3f, 1.0f);

        transform.SetPos(glm::vec3(sinf(i), 0, 0));
        transform.SetRot(glm::vec3(0, 0, i));
        transform.SetScale(cosf(i));

        shader.Bind();
        texture.Bind(0);
        shader.Update(transform);
        mesh.Draw();

        display.SwapBuffers();
        i += 0.01f;
    }

    return 0;
}