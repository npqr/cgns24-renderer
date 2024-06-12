#include <iostream>
#include "config.h"
#include "renderer.h"
#include "shader.h"

Renderer renderer;
VertexArray varray;

// Vertex Data

float vertices[] = {
    -0.5f, 0.5f, 0.0f,
    0.5f, 0.5f, 0.0f,
    0.5f, -0.5f, 0.0f,
    -0.5f, -0.5f, 0.0f };

unsigned int indices[] = {
    0, 1, 2,
    2, 3, 0 };

int main()
{
    // Initialise GLFW, and if it doesn't raise error
    renderer.initialise_glfw();
    if (!renderer.create_window())
    {
        return -1;
    }

    // Setup Window
    renderer.setup_window_data();

    // Import Shaders 
    Shader shader("../src/shaders/defaultVec.vs", "../src/shaders/defaultFrag.fs");

    // Generation and binding of buffers
    varray.generate_buffers();
    varray.bind_vao();

    // no. of vertices, stride, ptr to vertex data
    varray.bind_vbo(4, 3 * sizeof(float), vertices);

    // no. of indices, ptr to indices array
    varray.bind_ebo(6, indices);

    // set for layout 0 (position) with stride 3
    varray.set_attribute_array(0, 3, 3 * sizeof(float));

    // we can bind later when needed to render
    varray.unbind_vbo();
    varray.unbind_vao();

    // for time dependent stuff
    renderer.start_timer(); 

    while (!renderer.close_window())
    {
        renderer.new_frame();

        // current deltaTime & fps
        std::cout << renderer.deltaTime << " " << (int)(1.0f / renderer.deltaTime) << std::endl;

        if (renderer.check_key(GLFW_KEY_ESCAPE))
        {
            glfwSetWindowShouldClose(renderer.window, true);
        }
        if (renderer.check_key(GLFW_KEY_R))
        {
            glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
        }
        else {
            glClearColor(0.2f, 0.1f, 0.3f, 1.0f);
        }

        glClear(GL_COLOR_BUFFER_BIT);

        // Use the current shader program
        shader.use();

        varray.draw_indices(6);

        // End of Frame
        renderer.swap_buffers(false);
    }

    renderer.terminate_glfw();
    return 0;
}
