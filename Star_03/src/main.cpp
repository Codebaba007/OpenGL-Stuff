/*
=========================================================
Lab Assignment - OpenGL

Task:
- Draw ONE cyan colored 5-point star
- Star must be built ONLY with triangles
- Background color must be yellow
- Window title = full student name
- Press initial letter 'M' to close window
=========================================================
*/

#include "glad.h"
#include "glfw3.h"
#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

// Window size
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

// ================= Vertex Shader =================
const char *vertexShaderSource =
"#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos, 1.0);\n"
"}\0";

// ================= Fragment Shader (CYAN) =================
const char *fragmentShaderSource =
"#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(0.0f, 1.0f, 1.0f, 1.0f); // Cyan color\n"
"}\n\0";

int main()
{
    // Initialize GLFW
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Create window with your full name
    GLFWwindow* window =
        glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT,
        "Mehedi Hassan Bhuiyan", NULL, NULL);

    if (!window)
    {
        std::cout << "Failed to create window\n";
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // Load OpenGL functions
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD\n";
        return -1;
    }

    // ================= Build Shader Program =================
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    unsigned int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    // ================= 5-Point Star (Triangles Only) =================
    float starVertices[] = {

        // Top small triangle
    -0.60f, 0.77f, 0.0f,
    -0.42f, 0.77f, 0.0f,
    -0.58f, 0.68f, 0.0f,

    // Top spike triangle
    -0.64f, 1.00f, 0.0f,
    -0.68f, 0.77f, 0.0f,
    -0.60f, 0.77f, 0.0f,

    // Left spike
    -0.68f, 0.77f, 0.0f,
    -0.70f, 0.68f, 0.0f,
    -0.86f, 0.77f, 0.0f,

    // Bottom-left spike
    -0.64f, 0.63f, 0.0f,
    -0.70f, 0.68f, 0.0f,
    -0.82f, 0.43f, 0.0f,

    // Bottom-right spike
    -0.64f, 0.63f, 0.0f,
    -0.58f, 0.68f, 0.0f,
    -0.51f, 0.43f, 0.0f
    };

    unsigned int VAO, VBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(starVertices), starVertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,
                          3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // ================= Render Loop =================
    while (!glfwWindowShouldClose(window))
    {
        processInput(window);

        // Yellow background
        glClearColor(1.0f, 1.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);

        // 5 triangles = 15 vertices
        glDrawArrays(GL_TRIANGLES, 0, 15);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Cleanup
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(shaderProgram);
    glfwTerminate();
    return 0;
}

// Close window when pressing 'M'
void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_M) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

// Adjust viewport when resizing
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}