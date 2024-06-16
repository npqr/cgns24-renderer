#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

// Define constants for window properties
const char* WINDOW_NAME = "OpenGL Window";

// Function to resize the viewport when the window is resized
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

// Class definition
class Renderer {
public:
    GLFWwindow* window;
    int major, minor;
    int width, height;
    double currentTime, previousTime, deltaTime;

    Renderer(int major_, int minor_, int width_, int height_);
    void initialise_glfw();
    bool create_window();
    void setup_window_data();
    void start_timer();
    bool close_window();
    void new_frame();
    bool check_key(int key);
    void swap_buffers(bool lockFrameRate);
    void terminate_glfw();
};

// Constructor
Renderer::Renderer(int major_, int minor_, int width_, int height_) {
    major = major_;
    minor = minor_;
    width = width_;
    height = height_;
}

// Initialize GLFW
void Renderer::initialise_glfw() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, major);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, minor);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#if __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
}

// Terminate GLFW
void Renderer::terminate_glfw() {
    glfwTerminate();
}

// Create a fullscreen window
bool Renderer::create_window() {
    // Get primary monitor and its video mode
    GLFWmonitor* primaryMonitor = glfwGetPrimaryMonitor();
    if (!primaryMonitor) {
        std::cout << "Failed to get primary monitor" << std::endl;
        terminate_glfw();
        return false;
    }
    const GLFWvidmode* mode = glfwGetVideoMode(primaryMonitor);

    // Create a fullscreen window
    window = glfwCreateWindow(mode->width, mode->height, WINDOW_NAME, primaryMonitor, NULL);

    if (window == NULL) {
        std::cout << "Failed to create GLFW window" << std::endl;
        terminate_glfw();
        return false;
    }

    glfwMakeContextCurrent(window);
    return true;
}

// Set up window data
void Renderer::setup_window_data() {
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
    }
}

// Check if window should close
bool Renderer::close_window() {
    return glfwWindowShouldClose(window);
}

// Swap buffers and poll events
void Renderer::swap_buffers(bool lockFrameRate) {
    glfwSwapBuffers(window);
    glfwPollEvents();

    if (!lockFrameRate) {
        glfwSwapInterval(0);
    }
    else {
        glfwSwapInterval(1);
    }
}

// Check if a key is pressed
bool Renderer::check_key(int key) {
    return (glfwGetKey(window, key) == GLFW_PRESS);
}

// Start the timer
void Renderer::start_timer() {
    currentTime = glfwGetTime();
    previousTime = currentTime;
    deltaTime = 0.0f;
}

// Calculate the time difference between frames
void Renderer::new_frame() {
    currentTime = glfwGetTime();
    deltaTime = currentTime - previousTime;
    previousTime = currentTime;
}

// VertexArray class for managing vertex arrays
class VertexArray {
public:
    unsigned int VAO, VBO, EBO;

    void generate_buffers();
    void bind_vao();
    void unbind_vao();
    void bind_vbo(int vertexCount, GLsizeiptr stride, void* pointer);
    void unbind_vbo();
    void bind_ebo(int indexCount, void* pointer);
    void unbind_ebo();
    void set_attribute_array(int layoutLayer, int count, GLsizeiptr stride, const void* pointer);
    void draw_triangle(int count, int startIndex);
    void draw_indices(int indexCount);
    void free_data();
};

void VertexArray::generate_buffers() {
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
}

void VertexArray::bind_vao() {
    glBindVertexArray(VAO);
}

void VertexArray::unbind_vao() {
    glBindVertexArray(0);
}

void VertexArray::bind_vbo(int vertexCount, GLsizeiptr stride, void* pointer) {
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertexCount * stride, pointer, GL_STATIC_DRAW);
}

void VertexArray::unbind_vbo() {
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VertexArray::bind_ebo(int indexCount, void* pointer) {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexCount * sizeof(unsigned int), pointer, GL_STATIC_DRAW);
}

void VertexArray::unbind_ebo() {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void VertexArray::set_attribute_array(int layoutLayer, int count, GLsizeiptr stride, const void* pointer) {
    glEnableVertexAttribArray(layoutLayer);
    glVertexAttribPointer(layoutLayer, count, GL_FLOAT, GL_FALSE, stride, pointer);
}

void VertexArray::draw_triangle(int count, int startIndex) {
    bind_vao();
    glDrawArrays(GL_TRIANGLES, startIndex, count);
    unbind_vao();
}

void VertexArray::draw_indices(int indexCount) {
    bind_vao();
    glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, 0);
    unbind_vao();
}

void VertexArray::free_data() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
}
