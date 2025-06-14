#define _CRT_SECURE_NO_WARNINGS
#define wWidth 800
#define wHeight 600 


#include <iostream>
#include <fstream>
#include <sstream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>



unsigned int compileShader(GLenum type, const char* source);
unsigned int createShader(const char* vsSource, const char* fsSource);

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

    unsigned int basicShader = createShader("shaders/basic.vert", "shaders/basic.frag");

    float vertices[] =
    {
        0.25, 0.0, 1.0, 0.0, 0.0, 1.0,
        -0.25, 0.0, 0.0, 0.0, 1.0, 1.0,
        0.0, -0.5, 1.0, 1.0, 1.0, 1.0
    };

    unsigned int stride = (2 + 4) * sizeof(float);

    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    unsigned int VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, stride, (void*) 0);
    
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, stride, (void*)(2 * sizeof(float)));

    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    glClearColor(0.15, 0.15, 0.15, 1.0);


    while(!glfwWindowShouldClose(window))
    {
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        {
            glfwSetWindowShouldClose(window, GL_TRUE);
        }

        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(basicShader);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glBindVertexArray(0);
        glUseProgram(0);

        glfwSwapBuffers(window);

        glfwPollEvents();

    }

    glDeleteBuffers(1, &VBO);
    glDeleteVertexArrays(1, &VAO);
    glDeleteProgram(basicShader);

    glfwTerminate();

    return 0;
}

unsigned int createShader(const char* vsSource, const char* fsSource) {

    unsigned int program;
    unsigned int vertexShader;
    unsigned int fragmentShader;
    program = glCreateProgram();
    vertexShader = compileShader(GL_VERTEX_SHADER, vsSource);
    fragmentShader = compileShader(GL_FRAGMENT_SHADER, fsSource);

    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);

    glLinkProgram(program);
    glValidateProgram(program);

    int success;
    char infoLog[512];
    glGetProgramiv(program, GL_VALIDATE_STATUS, &success);
    if (success == GL_FALSE)
    {
        glGetShaderInfoLog(program, 512, NULL, infoLog);
        std::cout << "Shader error. Error: " << std::endl;
        std::cout << infoLog << std::endl;
    }

    glDetachShader(program, vertexShader);
    glDeleteShader(vertexShader);
    glDetachShader(program, fragmentShader);
    glDeleteShader(fragmentShader);

    return program;
}

unsigned int compileShader(GLenum type, const char* source) {
    std::string contenxt = "";
    std::ifstream file(source);
    std:: stringstream ss;
    if (file.is_open())
    {
        ss << file.rdbuf();
        file.close();
        std::cout << "Uspesno procitan file sa putanje " << source << "!" << std::endl;
    } else {
        ss << "";
        std::cout << "Greska pri citanju fajla sa putanje " << source << "!" << std::endl;
    }
    std::string tmp = ss.str();
    const char* sourceCode = tmp.c_str();

    int shader = glCreateShader(type);

    int success;
    char infoLog[512];

    glShaderSource(shader, 1, &sourceCode, NULL);
    glCompileShader(shader);

    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if(success == GL_FALSE) 
    {
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        if (type == GL_VERTEX_SHADER)
            std::cout << "VERTEX" << std::endl; 
        else if (type == GL_FRAGMENT_SHADER)
            std::cout << "FRAGMENT" << std::endl;
        std::cout << "Shader ima gresku" << std::endl;
    }
    return shader;
}
