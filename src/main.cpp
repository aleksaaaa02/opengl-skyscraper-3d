#define _CRT_SECURE_NO_WARNINGS
#define wWidth 800
#define wHeight 600 

#include "mesh.h"
#include "shader.h"

#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <vector>


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
    const char windowTitle[] = "[Generic Title]";
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
	std::vector<Vertex> vertices = {
		{ { 0.25, 0.0, 0.0 }, { 0.0, 0.0, 1.0, 1.0 } },
		{ {-0.25, 0.0, 0.0 }, { 0.0, 1.0, 1.0, 1.0 } },
		{ { 0.0, 0.5, 0.0 }, { 1.0, 1.0, 1.0, 1.0 } }
	};
	std::vector<unsigned int> indecies = {0, 1, 2};
	Mesh mesh(vertices, indecies);

    glClearColor(0.15, 0.15, 0.15, 1.0);


	while(!glfwWindowShouldClose(window))
	{
		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        	{
			glfwSetWindowShouldClose(window, GL_TRUE);
        	}

		glClear(GL_COLOR_BUFFER_BIT);

		basicShader.use();
		mesh.Draw(basicShader);
        	glfwSwapBuffers(window);
        	glfwPollEvents();

    }
    glfwTerminate();

    return 0;
}
