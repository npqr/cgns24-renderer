#include <iostream>
#include <cmath>
#include "renderer.h"
#include "shader.h"

Renderer renderer;
VertexArray varray1, varray2;

float vertices1[] = {
    -0.75f,  0.25f, 0.0f,  1.0f, 0.0f, 0.0f, 1.0f,
     0.0f,  0.25f, 0.0f,   1.0f, 0.0f, 0.0f, 1.0f,
    -0.375f, -0.25f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f
};

unsigned int indices1[] = { 0, 1, 2 };

float vertices2[] = {
     0.0f,  0.25f, 0.0f,  1.0f, 0.5f, 0.0f, 1.0f,
     0.75f, 0.25f, 0.0f,  1.0f, 0.5f, 0.0f, 1.0f,
     0.375f, -0.25f, 0.0f,1.0f, 0.5f, 0.0f, 1.0f
};

unsigned int indices2[] = { 0, 1, 2 };

const char* vertexShaderSource = R"(
#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec4 aColor;

out vec4 vertexColor;

void main() {
    gl_Position = vec4(aPos, 1.0);
    vertexColor = aColor;
}
)";

const char* fragmentShaderSource = R"(
#version 330 core
in vec4 vertexColor;
out vec4 FragColor;

void main() {
    FragColor = vertexColor;
}
)";

int main() {
    renderer.initialise_glfw();
    if (!renderer.create_window()) {
        return -1;
    }

    renderer.setup_window_data();

    Shader shader(vertexShaderSource, fragmentShaderSource);

    varray1.generate_buffers();
    varray1.bind_vao();
    varray1.bind_vbo(3, 7 * sizeof(float), vertices1);
    varray1.bind_ebo(3, indices1);
    varray1.set_attribute_array(0, 3, 7 * sizeof(float), (void*)0);
    varray1.set_attribute_array(1, 4, 7 * sizeof(float), (void*)(3 * sizeof(float)));
    varray1.unbind_vbo();
    varray1.unbind_vao();

    varray2.generate_buffers();
    varray2.bind_vao();
    varray2.bind_vbo(3, 7 * sizeof(float), vertices2);
    varray2.bind_ebo(3, indices2);
    varray2.set_attribute_array(0, 3, 7 * sizeof(float), (void*)0);
    varray2.set_attribute_array(1, 4, 7 * sizeof(float), (void*)(3 * sizeof(float)));
    varray2.unbind_vbo();
    varray2.unbind_vao();

    renderer.start_timer();

    float bgColor[3] = { 0.2f, 0.1f, 0.3f };
    bool redPressed = false, greenPressed = false, bluePressed = false;

    while (!renderer.close_window()) {
        renderer.new_frame();
        std::cout << renderer.deltaTime << " " << (int)(1.0f / renderer.deltaTime) << std::endl;

        if (renderer.check_key(GLFW_KEY_ESCAPE)) {
            glfwSetWindowShouldClose(renderer.window, true);
        }

        if (renderer.check_key(GLFW_KEY_R) && !redPressed) {
            bgColor[0] = 1.0f;
            bgColor[1] = 0.0f;
            bgColor[2] = 0.0f;
            redPressed = true;
            greenPressed = false;
            bluePressed = false;
        } else if (renderer.check_key(GLFW_KEY_G) && !greenPressed) {
            bgColor[0] = 0.0f;
            bgColor[1] = 1.0f;
            bgColor[2] = 0.0f;
            redPressed = false;
            greenPressed = true;
            bluePressed = false;
        } else if (renderer.check_key(GLFW_KEY_B) && !bluePressed) {
            bgColor[0] = 0.0f;
            bgColor[1] = 0.0f;
            bgColor[2] = 1.0f;
            redPressed = false;
            greenPressed = false;
            bluePressed = true;
        }

        glClearColor(bgColor[0], bgColor[1], bgColor[2], 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        shader.use();

        varray1.bind_vao();
        varray1.draw_indices(3);
        varray1.unbind_vao();

        varray2.bind_vao();
        varray2.draw_indices(3);
        varray2.unbind_vao();

        renderer.swap_buffers(false);
    }

    renderer.terminate_glfw();
    return 0;
}
