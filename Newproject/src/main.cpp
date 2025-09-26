#include <iostream>
#include<cmath>
#include <algorithm>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Shader.h"
#include "Camera.h"
#include "utils_gl.h"
#include "Texture.h"
#include "VAO.h"
#include"VBO.h"
#include"EBO.h"
//GLM setup
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
void mouse_callback(GLFWwindow* window, double xPos, double yPos);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window, float deltaTime);
// Vertex data (x, y, z, u, v)
// Vertex data (x, y, z, u, v)
// Vertex data (x, y, z, u, v)
GLfloat vertices[] = {
    // COORDINATES        TexCoord
    -0.5f, 0.0f,  0.5f,  0.0f, 0.0f,  // Bottom side
    -0.5f, 0.0f, -0.5f,  0.0f, 5.0f,  // Bottom side
     0.5f, 0.0f, -0.5f,  5.0f, 5.0f,  // Bottom side
     0.5f, 0.0f,  0.5f,  5.0f, 0.0f,  // Bottom side

    -0.5f, 0.0f,  0.5f,  0.0f, 0.0f,  // Left side
    -0.5f, 0.0f, -0.5f,  5.0f, 0.0f,  // Left side
     0.0f, 0.8f,  0.0f,  2.5f, 5.0f,  // Left side

    -0.5f, 0.0f, -0.5f,  5.0f, 0.0f,  // Non-facing side
     0.5f, 0.0f, -0.5f,  0.0f, 0.0f,  // Non-facing side
     0.0f, 0.8f,  0.0f,  2.5f, 5.0f,  // Non-facing side

     0.5f, 0.0f, -0.5f,  0.0f, 0.0f,  // Right side
     0.5f, 0.0f,  0.5f,  5.0f, 0.0f,  // Right side
     0.0f, 0.8f,  0.0f,  2.5f, 5.0f,  // Right side

     0.5f, 0.0f,  0.5f,  5.0f, 0.0f,  // Facing side
    -0.5f, 0.0f,  0.5f,  0.0f, 0.0f,  // Facing side
     0.0f, 0.8f,  0.0f,  2.5f, 5.0f   // Facing side
};

// Indices for vertices order
GLuint indices[] = {
    0, 1, 2,  // Bottom side
    0, 2, 3,  // Bottom side
    4, 6, 5,  // Left side
    7, 9, 8,  // Non-facing side
    10, 12, 11, // Right side
    13, 15, 14  // Facing side
};
// Vertex data (x, y, z, r, g, b)
GLfloat cubeVertices[] = {
    -0.5f, -0.5f,  0.5f,  1.0f, 0.65f, 0.0f,  // 0 - Front-bottom-left
     0.5f, -0.5f,  0.5f,  1.0f, 0.65f, 0.0f,  // 1 - Front-bottom-right
     0.5f,  0.5f,  0.5f,  1.0f, 0.65f, 0.0f,  // 2 - Front-top-right
    -0.5f,  0.5f,  0.5f,  1.0f, 0.65f, 0.0f,  // 3 - Front-top-left
    -0.5f, -0.5f, -0.5f,  1.0f, 0.65f, 0.0f,  // 4 - Back-bottom-left
     0.5f, -0.5f, -0.5f,  1.0f, 0.65f, 0.0f,  // 5 - Back-bottom-right
     0.5f,  0.5f, -0.5f,  1.0f, 0.65f, 0.0f,  // 6 - Back-top-right
    -0.5f,  0.5f, -0.5f,  1.0f, 0.65f, 0.0f   // 7 - Back-top-left
};

// Indices for edges (pairs for GL_LINES)
GLuint cubeIndices[] = {
    0, 1, 2, 0, 2, 3, // Front
    4, 5, 6, 4, 6, 7, // Back
    0, 4, 7, 0, 7, 3, // Left
    1, 5, 6, 1, 6, 2, // Right
    3, 2, 6, 3, 6, 7, // Top
    0, 1, 5, 0, 5, 4  // Bottom
};
//camera setup 
glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, 2.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
// set initial positions to the center
float lastX = 400;
float lastY = 300;
//initial entry to true
bool firstEntry = true;
//first camera offsets 
float yaw = -90.0f;
float pitch = 0.0f;
//
float lastFrame = 0.0f;
//camera class
Camera camera = Camera(cameraPos,cameraUp);

int main()
{
    

    if (!glfwInit())
    {
        std::cout << "Failed to initialize GLFW" << std::endl;
        return -1;
    }
    
    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    //cursor settings


    GLFWwindow* window;
    window = glfwCreateWindow(800, 600, "Hello_opengl", NULL, NULL);
    if (window == NULL)
    {
       std::cout << "Failed to open GLFW window" <<std::endl;
        return -1;
    }
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" <<std::endl;
        return -1;
    }
	std::cout <<"hello opengl"<<std::endl;
    glViewport(0, 0, 800, 600);
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f); // Set a blue-ish background
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    // cursor settings
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetCursorPosCallback(window, mouse_callback);
    glEnable(GL_DEPTH_TEST);
    //set up buffer object for pyramid 
    VAO VAO1;
    VAO1.bind();
    VBO VBO1(vertices, sizeof(vertices));
    EBO EBO1(indices, sizeof(indices));
    
    VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 5 * sizeof(float), (void*)0);
    VAO1.LinkAttrib(VBO1, 1, 2, GL_FLOAT, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    VAO1.disAbleLayout(2);
    VAO1.disAbleLayout(3);
    
    // Unbind all to prevent accidentally modifying them
    VAO1.unbind();
    VBO1.unbind();
    EBO1.unbind();
    //setup buffer objects for cube 
    VAO cubeVAO;
    cubeVAO.bind();
    VBO cubeVBO(cubeVertices,sizeof(cubeVertices));
    EBO cubeEBO(cubeIndices, sizeof(cubeIndices));
   
    cubeVAO.LinkAttrib(cubeVBO, 0, 3, GL_FLOAT, 6 * sizeof(float), (void*)0);
    cubeVAO.disAbleLayout(1);
    cubeVAO.LinkAttrib(cubeVBO, 2, 3, GL_FLOAT, 6 * sizeof(float), (void*)(3*sizeof(float)));
    cubeVAO.disAbleLayout(3);
   
    // unbind to prevent accidental modification 
    cubeVAO.unbind();
    cubeVBO.unbind();
    cubeEBO.unbind();

    //texture setup

    Texture asuka("C:\\Users\\hp\\Desktop\\code\\c++\\Newproject\\Newproject\\src\\bricks.jpg", GL_TEXTURE_2D, GL_TEXTURE0, GL_UNSIGNED_BYTE);


    Shader objShader("C:\\Users\\hp\\Desktop\\code\\c++\\Newproject\\Newproject\\src\\shader.vert",
                  "C:\\Users\\hp\\Desktop\\code\\c++\\Newproject\\Newproject\\src\\shader.frag");
    objShader.use();
    asuka.texUnit(objShader, "texture1", 0);
    glm::mat4 projection = glm::mat4(1.0f);
    projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.01f, 300.0f);
    objShader.setMat4("projection", projection);
    //
    Shader lightShader("C:\\Users\\hp\\Desktop\\code\\c++\\Newproject\\Newproject\\src\\lightObj.vert",
        "C:\\Users\\hp\\Desktop\\code\\c++\\Newproject\\Newproject\\src\\lightObj.frag");
    //
    lightShader.use();
    lightShader.setMat4("projection", projection);
    glm::vec3 lightColor = glm::vec3(3.0f*sin(glfwGetTime()), 0.0f, 0.0f);
    lightShader.setVec3("lightColor", lightColor);
    objShader.use();
    objShader.setVec3("lightColor", lightColor);
    

    while (!glfwWindowShouldClose(window))
    {  
        asuka.Bind();
        float deltaTime = 0.0f;
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        processInput(window,deltaTime);
        glm::mat4 view;
        view = camera.GetViewMatrix();
        objShader.use();
        objShader.setMat4("view", view);
        lightShader.use();
        lightShader.setMat4("view", view);
        glClear(GL_COLOR_BUFFER_BIT);// Clear the screen with the set color
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        //
        glm::mat4 model = glm::mat4(1.0f);
        VAO1.bind();
        asuka.Bind();
        asuka.texUnit(objShader, "texture1", 0);
        model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
        model = glm::rotate(model, glm::radians((float)(30*glfwGetTime())), glm::vec3(0.0f, 1.0f, 0.0f));
        objShader.setMat4("model", model);
        glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(int), GL_UNSIGNED_INT,0);
        VAO1.unbind();
        //
        lightShader.use();
        model = glm::mat4(1.0f);
        cubeVAO.bind();
        model = glm::translate(model, glm::vec3(1.0f, 1.0f, 0.0f));
        model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
        lightShader.setMat4("model", model);
        glDrawElements(GL_TRIANGLES,sizeof(cubeIndices)/sizeof(int), GL_UNSIGNED_INT, 0);
        cubeVAO.unbind();
        // for rendering the pyramid
    
      
       
        glfwSwapBuffers(window);          // Swap buffers
        glfwPollEvents();                 // Handle events
    }
    asuka.Delete();
    //
    VAO1.Delete();
    VBO1.Delete();
    EBO1.Delete();
    //
    cubeVBO.Delete();
    cubeVAO.Delete();
    cubeEBO.Delete();
    //
    glfwTerminate();
    return 0;
}
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}
void mouse_callback(GLFWwindow* window, double xPos, double yPos)
{
    const float sensitivity = 0.05f; // Reduced for touchpad
    if (firstEntry) {
        lastX = xPos;
        lastY = yPos;
        firstEntry = false;
        return;
    }
    float xChange = static_cast<float>(sensitivity * (xPos - lastX));
    float yChange = static_cast<float>(sensitivity * (lastY - yPos));
    lastX = xPos;
    lastY = yPos;
    //
    camera.ProcessMouseMovement(xChange, yChange);
    //
}
void processInput(GLFWwindow* window, float deltaTime) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    //movement in z axis 
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.ProcessKeyboard(FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    //movement in x axis
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.ProcessKeyboard(RIGHT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.ProcessKeyboard(LEFT, deltaTime);
}