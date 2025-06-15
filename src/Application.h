#pragma once
#ifndef APPLICATION_H
#define APPLICATION_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "mesh.h"
#include "shader.h"
#include "scene_node.h"
#include "camera.h"
#include <iostream>
#include "mesh_factory.h"
#include <vector>

class Application {
    Camera *mainCamera;
    float wWidth, wHeight;
    char *title;
    GLFWwindow *window;
    Shader *shader;
    float deltaTime = 0.0f, lastFrame = 0.0f;
    SceneNode *root;

    void framebuffer_size_callback(GLFWwindow* window, int width, int height);
    void processInput();
    void updateTime();
    void render();
    bool checkCollision();
public:
    Application(float wWidth, float wHeight, char* title);
    ~Application();
    void Run();
    int InitOpenGL();
    void InitScene();
};



#endif //APPLICATION_H
