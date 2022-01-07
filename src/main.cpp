#include "display.h"
#include "shader.h"
#include "mesh.h"
#include "texture.h"
#include "transform.h"
#include "camera.h"

int main() {

    Display display(800, 600, "OpenGL Test");
    Shader shader("./res/shaders/shader");

    // Vertex vertices[] = { Vertex(glm::vec3(-0.5, -0.5, 0), glm::vec2(0.0, 0.0)),
    //                      Vertex(glm::vec3(0, 0.5, 0), glm::vec2(0.5, 1.0)),
    //                      Vertex(glm::vec3(0.5, -0.5, 0), glm::vec2(1.0, 0.0)) };

    // unsigned int indices[] = { 0, 1, 2 };
                          
    // Mesh mesh(vertices, sizeof(vertices) / sizeof(vertices[0]), indices, sizeof(indices) / sizeof(indices[0]));

    Mesh mesh("./res/models/object.obj");
    Texture texture("./res/textures/texture.jpg");

    glm::vec3 cameraPos = glm::vec3(0, 0, -5);
    Camera camera(cameraPos, 70.0f, display.getAspectRatio(), 0.01f, 1000.0f);
    Transform transform;

    float i = 0.0f;

    while (!display.IsClosed()) {
        display.Clear(0.1f, 0.1f, 0.1f, 1.0f);

        transform.SetRot(glm::vec3(0, i, 0));

        shader.Bind();
        texture.Bind(0);
        shader.Update(transform, camera);
        mesh.Draw();

        display.SwapBuffers();
        i += 0.01f;
    }

    return 0;
}