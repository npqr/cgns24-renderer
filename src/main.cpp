#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

float red = 0.2f;
float green = 0.0f;
float blue = 0.3f;

float redChange = 0.0f;
float greenChange = 0.0f;
float blueChange = 0.0f;

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }

    if (key == GLFW_KEY_R && action == GLFW_PRESS) {
        redChange = (redChange == 0.0f) ? 0.01f : 0.0f;  
    }
    if (key == GLFW_KEY_G && action == GLFW_PRESS) {
        greenChange = (greenChange == 0.0f) ? 0.01f : 0.0f;  
    }
    if (key == GLFW_KEY_B && action == GLFW_PRESS) {
        blueChange = (blueChange == 0.0f) ? 0.01f : 0.0f;  
    }

    if (key == GLFW_KEY_W && action == GLFW_PRESS) {
        if (glfwGetWindowMonitor(window) != NULL) {
            
            glfwSetWindowMonitor(window, nullptr, 100, 100, 800, 600, GLFW_DONT_CARE);
        }
        else {
           
            GLFWmonitor* primaryMonitor = glfwGetPrimaryMonitor();
            const GLFWvidmode* mode = glfwGetVideoMode(primaryMonitor);
            glfwSetWindowMonitor(window, primaryMonitor, 0, 0, mode->width, mode->height, mode->refreshRate);
        }
    }
}


void framebufferSizeCallback(GLFWwindow* window, int width, int height) {
   
    int minWidth = 640;
    int minHeight = 480;
    int maxWidth = 1280;
    int maxHeight = 720;

    width = (width < minWidth) ? minWidth : (width > maxWidth) ? maxWidth : width;
    height = (height < minHeight) ? minHeight : (height > maxHeight) ? maxHeight : height;

    glfwSetWindowSize(window, width, height);
    glViewport(0, 0, width, height);
}
//Vertex Shader source code. 
const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"layout (location = 1) in vec3 aColor;\n"
"out vec3 ourColor;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos, 1.0);\n"
"   ourColor = aColor;\n"
"}\0";
//Fragment Shader source code. 
const char* fragmentShaderSource = "#version 330 core\n"
"in vec3 ourColor;\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(ourColor, 1.0);\n"
"}\n\0";

int main() {
    glfwInit();
    GLFWmonitor* primaryMonitor = glfwGetPrimaryMonitor();
    if (!primaryMonitor) {
        std::cerr << "Failed to get primary monitor" << std::endl;
        return -1;
    }
    const GLFWvidmode* mode = glfwGetVideoMode(primaryMonitor);
    if (!mode) {
        std::cerr << "Failed to get video mode" << std::endl;
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(mode->width, mode->height, "Yash", primaryMonitor, nullptr);
    if (window == nullptr) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetKeyCallback(window, keyCallback);
    glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);

    gladLoadGL();

    int screenWidth, screenHeight;
    glfwGetFramebufferSize(window, &screenWidth, &screenHeight);
    glViewport(0, 0, screenWidth, screenHeight);

    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
    glCompileShader(vertexShader);

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
    glCompileShader(fragmentShader);

    GLuint shaderProgram = glCreateProgram();

    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    GLuint VAO, VBO, EBO;

    GLfloat vertices[] = {
        -0.5f, -0.5f, 0.0f,  0.8f, 0.3f, 0.02f, 
        -0.5f,  0.5f, 0.0f,  0.8f, 0.3f, 0.02f, 
         0.0f,  0.0f, 0.0f,  0.8f, 0.3f, 0.02f, 
         0.5f, -0.5f, 0.0f,  1.0f, 0.75f, 0.8f, 
         0.5f,  0.5f, 0.0f,  1.0f, 0.75f, 0.8f, 
         0.0f,  0.0f, 0.001f,  1.0f, 0.75f, 0.8f 
    };

    GLuint indices[] = {
        0, 1, 2,
        3, 4, 5,
    };

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    while (!glfwWindowShouldClose(window)) {
        
        red += redChange;
        green += greenChange;
        blue += blueChange;

        
        if (red > 1.0f) red = 0.0f;
        if (green > 1.0f) green = 0.0f;
        if (blue > 1.0f) blue = 0.0f;

        glClearColor(red, green, blue, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(window);
        glfwPollEvents();

        
        int newScreenWidth, newScreenHeight;
        glfwGetFramebufferSize(window, &newScreenWidth, &newScreenHeight);
        if (newScreenWidth != screenWidth || newScreenHeight != screenHeight) {
            screenWidth = newScreenWidth;
            screenHeight = newScreenHeight;
            glViewport(0, 0, screenWidth, screenHeight);
        }
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glDeleteProgram(shaderProgram);

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
