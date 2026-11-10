#include <iostream>
#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include "render/shader.h"

float verticies[] = {
    0.5f,  0.5f, 0.0f,  
     0.5f, -0.5f, 0.0f,  
    -0.5f, -0.5f, 0.0f, 
    -0.5f,  0.5f, 0.0f   
};

unsigned int indices[] = {
    0, 1, 3,  
    1, 2, 3   
};  

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

int main()
{
    if (!glfwInit())
    {
        std::cerr << "Failed to init glfw" << "\n";
        return 0;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(800, 600, "Velox", nullptr, nullptr);
    if (!window)
    {
        std::cerr << "Cannot create GLFW window!" << "\n";
        glfwTerminate();
        return 0;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    
    if (!gladLoadGL(glfwGetProcAddress)) 
    {
        std::cerr << "Cannot initialize GLAD!" << "\n";
        return -1;
    }
    
    glViewport(0, 0, 800, 600);

    Shader shaderProg("shaders/default.vert", "shaders/default.frag");
    
    GLuint VBO, VAO, EBO;
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    glGenVertexArrays(1, &VAO);

    glBindVertexArray(VAO);
    
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(verticies), verticies, GL_STATIC_DRAW);
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);  

    glBindVertexArray(0);

    while (!glfwWindowShouldClose(window))
    {
        glClearColor(0.2f, 0.2f, 0.2f, 1.f);
        glClear(GL_COLOR_BUFFER_BIT);

        shaderProg.use();
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}