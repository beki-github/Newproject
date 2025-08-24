#include <iostream>
#include<cmath>
#include <algorithm>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Shader.h"
#include "Camera.h"
#include "utils_gl.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
//GLM setup
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
void mouse_callback(GLFWwindow* window, double xPos, double yPos);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window, float deltaTime);
float vertices[] = {
    // Front face
    -0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f,  0.0f, 0.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  0.0f, 0.0f, 1.0f,  1.0f, 1.0f,
    -0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 0.0f,  0.0f, 1.0f,

    // Back face
    -0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 0.0f,  0.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  0.0f, 1.0f, 0.0f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 1.0f,  1.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 0.0f,  0.0f, 1.0f,

    // Left face
    -0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 0.0f,  0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0f,  1.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 0.0f, 1.0f,  1.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 0.0f,  0.0f, 1.0f,

    // Right face
     0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f,  0.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  0.0f, 1.0f, 0.0f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 1.0f,  1.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 0.0f,  0.0f, 1.0f,

     // Bottom face
     -0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f,  0.0f, 0.0f,
      0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0f,  1.0f, 0.0f,
      0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 1.0f,  1.0f, 1.0f,
     -0.5f, -0.5f,  0.5f,  1.0f, 1.0f, 0.0f,  0.0f, 1.0f,

     // Top face
     -0.5f,  0.5f, -0.5f,  1.0f, 0.0f, 0.0f,  0.0f, 0.0f,
      0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 0.0f,  1.0f, 0.0f,
      0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 1.0f,  1.0f, 1.0f,
     -0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 0.0f,  0.0f, 1.0f
};
unsigned int indices[] = {
    0, 1, 2,   0, 2, 3,    // Front
    4, 5, 6,   4, 6, 7,    // Back
    8, 9, 10,  8, 10, 11,  // Left
    12, 13, 14, 12, 14, 15,// Right
    16, 17, 18, 16, 18, 19,// Bottom
    20, 21, 22, 20, 22, 23 // Top
};
//camera setup 
glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, -7.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, 1.0f);
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

    //DRAW in wire frame mode
   /* glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);*/
    //VAO setup


    GLuint VAO, VBO, EBO;
    setBufferObjects(VAO, VBO, EBO, vertices, sizeof(vertices), indices, sizeof(indices));
    //texture setup
    unsigned int texture1, texture2;
    glGenTextures(1, &texture1);
    glGenTextures(1, &texture2);
    stbi_set_flip_vertically_on_load(true);
    //texture 1
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture1);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    int width, height, nrChannels;
    unsigned char* data = stbi_load("C:\\Users\\hp\\Desktop\\code\\c++\\Newproject\\Newproject\\src\\power.jpg",
                                    &width, &height, &nrChannels, 0);
    if (data)
    {      
        GLenum format = (nrChannels == 4) ? GL_RGBA : GL_RGB;
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0,format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, texture2);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    unsigned char* data2 = stbi_load("C:\\Users\\hp\\Desktop\\code\\c++\\Newproject\\Newproject\\src\\logo.jpg",
                           &width, &height, &nrChannels, 0);
    if (data2) {
        GLenum format = (nrChannels == 4) ? GL_RGBA : GL_RGB;
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height,0, format, GL_UNSIGNED_BYTE,data2);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else {
        std::cout << "flailed to load texture 2" << std::endl;
    }
    
    stbi_image_free(data2);

    
    Shader Shader("C:\\Users\\hp\\Desktop\\code\\c++\\Newproject\\Newproject\\src\\shader.vert",
                  "C:\\Users\\hp\\Desktop\\code\\c++\\Newproject\\Newproject\\src\\shader.frag");
    Shader.use();
    Shader.setInt("texture1", 0);
    Shader.setInt("texture2", 1);
   
    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 projection = glm::mat4(1.0f);
   
    model = glm::rotate(model, glm::radians(25.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 300.0f);
    //
    Shader.setMat4("projection", projection);
    const double PI = 3.141592653;
    while (!glfwWindowShouldClose(window))
    {
        
        float deltaTime = 0.0f;
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        processInput(window,deltaTime);
        glClear(GL_COLOR_BUFFER_BIT);// Clear the screen with the set color
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture1);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, texture2);
        glBindVertexArray(VAO);
        float time = glfwGetTime();
        //
        glm::mat4 view;
        view = camera.GetViewMatrix();
        Shader.setMat4("view", view);
        //
        const float radius = 10.0f;
        const float angle = 2.0f * asin(2.0f / (2.0f * radius));
        const int objectNum = static_cast<int>(2.0f * PI / angle );

        float currentX = 0.0f; // Initial X position
        float currentZ = 10.0f; // Initial Z position

        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, 7.0f, 0.0f));
        model = glm::scale(model, glm::vec3(5.0f,15.0f, 5.0f));
        Shader.setMat4("model", model);
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
       
        for (unsigned int i = 0;i < objectNum;i++) {
            
            float newX = currentX * cos(angle) - currentZ * sin(angle); // Rotate current position
            float newZ = currentX * sin(angle) + currentZ * cos(angle);


            for (unsigned int y = 0;y < 4;y++) {
                glm::mat4 model = glm::mat4(1.0f); // Reset model matrix for each object
                float angleDir;
                (y % 2 == 1) ?  angleDir = 5.0f :  angleDir = -3.0f;
                model = glm::rotate(model, angleDir*time * glm::radians(15.0f), glm::vec3(0.0f, 1.0f, 0.0f));
                model = glm::translate(model, glm::vec3(newX, static_cast<float>(y)*2.0f, newZ));
                Shader.setMat4("model", model);
                glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
            }
            // Update current position for the next iteration
            currentX = newX;
            currentZ = newZ;

            
        }
      
       
        glfwSwapBuffers(window);          // Swap buffers
        glfwPollEvents();                 // Handle events
    }
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glDeleteTextures(1, &texture1);
    glDeleteTextures(1, &texture2);

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