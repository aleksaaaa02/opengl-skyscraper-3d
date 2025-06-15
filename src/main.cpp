#define _CRT_SECURE_NO_WARNINGS


#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Application.h"





void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);


int main()
{
	Application app(800, 600, "[Skyscraper]");

	if (app.InitOpenGL() != 0) {
	    return 1;
	}

	app.InitScene();

	app.Run();
    return 0;
}

void processInput(GLFWwindow* window)
{
}
