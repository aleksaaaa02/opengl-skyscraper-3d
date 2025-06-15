#include <glm/ext/matrix_clip_space.hpp>
#define _CRT_SECURE_NO_WARNINGS
#define wWidth 800
#define wHeight 600 

#include "mesh.h"
#include "shader.h"
#include "scene_node.h"
#include "camera.h"

#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <vector>

std::vector<Vertex> vertices = {
    // Bottom face vertices (z = -0.5)
    {{-0.5f, -0.5f, -0.5f}, {1.0f, 0.0f, 0.0f, 1.0f}}, // 0: Bottom-left-back
    {{ 0.5f, -0.5f, -0.5f}, {0.0f, 1.0f, 0.0f, 1.0f}}, // 1: Bottom-right-back
    {{ 0.5f,  0.5f, -0.5f}, {0.0f, 0.0f, 1.0f, 1.0f}}, // 2: Top-right-back
    {{-0.5f,  0.5f, -0.5f}, {1.0f, 1.0f, 0.0f, 1.0f}}, // 3: Top-left-back
    
    // Top face vertices (z = 0.5)
    {{-0.5f, -0.5f,  0.5f}, {1.0f, 0.0f, 1.0f, 1.0f}}, // 4: Bottom-left-front
    {{ 0.5f, -0.5f,  0.5f}, {0.0f, 1.0f, 1.0f, 1.0f}}, // 5: Bottom-right-front
    {{ 0.5f,  0.5f,  0.5f}, {0.5f, 0.5f, 0.5f, 1.0f}}, // 6: Top-right-front
    {{-0.5f,  0.5f,  0.5f}, {1.0f, 0.5f, 0.0f, 1.0f}}  // 7: Top-left-front
};

std::vector<unsigned int> indecies {
// Back face (z = -0.5)
0, 1, 2,  2, 3, 0,
// Front face (z = 0.5)
4, 5, 6,  6, 7, 4,
// Left face (x = -0.5)
4, 0, 3,  3, 7, 4,
// Right face (x = 0.5)
1, 5, 6,  6, 2, 1,
// Bottom face (y = -0.5)
4, 5, 1,  1, 0, 4,
// Top face (y = 0.5)
3, 2, 6,  6, 7, 3
};

Camera mainCamera({0.0f, 2.0f, 0.0f});
float deltaTime = 0.0f;
float lastFrame = 0.0f;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);


const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

int main()
{
    if (!glfwInit())
    {
        std::cout << "GLFW Biblioteka se nije ucitala";
        return 1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window;
    const char windowTitle[] = "[Skyscraper]";
    window = glfwCreateWindow(wWidth, wHeight, windowTitle, NULL, NULL);

    if (window == NULL)
    {
        std::cout << "Prozor nije napravljen! :(" << std::endl;
        glfwTerminate();
        return 2;
    }

    glfwMakeContextCurrent(window);

    if (glewInit() != GLEW_OK)
    {
        std::cout << "GLEW nije mogao da se ucita";
        return 3;
    }

    Shader basicShader("shaders/basic.vert", "shaders/basic.frag");

    Mesh mesh(vertices, indecies);
    SceneNode cube(mesh);


	glEnable(GL_DEPTH_TEST);

	while(!glfwWindowShouldClose(window))
	{
		// per-frame time logic
        float curFrame = glfwGetTime();
        deltaTime = curFrame - lastFrame;
        lastFrame = curFrame;
		
		// input
		processInput(window);

		// render
		glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		//shader enable
		basicShader.use();

		// view / projection
		glm::mat4 view = mainCamera.GetViewMatrix();	
		glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float) SCR_WIDTH / (float) SCR_HEIGHT, 0.1f, 100.0f);

		basicShader.setMat4("view", view);
		basicShader.setMat4("projection", projection);

        mesh.Draw(basicShader);
		// draw scene graph
		cube.Draw(basicShader);	

		// swap buffer and poll for events
        glfwSwapBuffers(window);
        glfwPollEvents();

    }
    glfwTerminate();

    return 0;
}

void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    {
		mainCamera.MoveCamera(FORWARD, deltaTime);
        std::cout << "camera position :" << mainCamera.Position.x << mainCamera.Position.y << mainCamera.Position.z;
    }
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		mainCamera.MoveCamera(BACKWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		mainCamera.MoveCamera(LEFT, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		mainCamera.MoveCamera(RIGHT, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
		mainCamera.RotateCamera(90.0f * deltaTime, 0.0f);
	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
		mainCamera.RotateCamera(-90.0f * deltaTime, 0.0f);
}
