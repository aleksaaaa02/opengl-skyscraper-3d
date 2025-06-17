//
// Created by aleksa on 6/15/25.
//

#include "Application.h"
#include <random>
#include <bits/this_thread_sleep.h>


Application::Application(const float wWidth, const float wHeight, char* title)
    : mainCamera(nullptr), wWidth(wWidth), wHeight(wHeight),
    title(title), window(nullptr), shader(nullptr), root(nullptr)
{

}

int Application::InitOpenGL() {
    if (!glfwInit())
    {
        std::cout << "GLFW Biblioteka se nije ucitala";
        return 1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(wWidth, wHeight, title, NULL, NULL);

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
    shader = new Shader("shaders/basic.vert", "shaders/basic.frag");
    return 0;
}

void Application::Run() {
    const double TARGET_FPS = 60.0f;
    const double FRAME_TIME = 1.0f / TARGET_FPS;
    while(!glfwWindowShouldClose(window))
    {
        double currentTime = glfwGetTime();
        updateTime();
        processInput();
        render();

        if (checkCollision()) {
            std::cout << "Collision detected" << std::endl;
        }
        double renderTime = glfwGetTime() - currentTime;

        if (renderTime < FRAME_TIME) {
            std::this_thread::sleep_for(std::chrono::duration<double>(FRAME_TIME - renderTime));
        }

        glfwSwapBuffers(window);
        glfwPollEvents();

    }

}

void Application::InitScene() {
    mainCamera = new Camera({0.0f, 1.0f, 0.0f});

    std::random_device rd;
    std::mt19937 gen(rd());

    std::uniform_real_distribution<float> heightDist(3.0f, 15.0f);  // Building heights
    std::shared_ptr<Mesh> ground = MeshFactory::CreateMesh(MeshType::PLANE);

    std::shared_ptr<Mesh> cube = MeshFactory::CreateMesh(MeshType::CUBE);

    root = new SceneNode(ground);
    root -> setColor({0.0f, 1.0f, 0.0f});
    root->Trans.position = glm::vec3(0.0f, -0.01f, 0.0f);
    root->Trans.scale = {50.0f, 0.0f, 50.0f};

    for (int x = -20; x <= 20; x += 4) {
        for (int z = -20; z <= 20; z += 4) {
            if (abs(x) < 4 && abs(z) < 4) continue;
            float height = heightDist(gen);
            std::unique_ptr<SceneNode> building = std::make_unique<SceneNode>(cube);
            building.get() -> Trans.scale = { 2.0f, height, 2.0f } ;
            building->Trans.position = { x, height/2.0f, z };
            root->AddChild(std::move(building));
        }
    }

    signatureRenderer = new SignatureRenderer("./res/name.png");
}

void Application::processInput() {
    glm::vec3 oldPosition = mainCamera -> Position;

    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        mainCamera -> MoveCamera(FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        mainCamera -> MoveCamera(BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        mainCamera -> MoveCamera(LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        mainCamera -> MoveCamera(RIGHT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
        mainCamera -> MoveCamera(UP, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
        mainCamera -> MoveCamera(DOWN, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
        mainCamera -> RotateCamera(90.0f * deltaTime, 0.0f);
    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
        mainCamera -> RotateCamera(-90.0f * deltaTime, 0.0f);
    static bool key1Pressed = false, key2Pressed = false;
    if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS && !key1Pressed) {
        isDayTime = true;
        lightPos = glm::vec3(0.0f, 15.0f, 5.0f);
        lightColor = glm::vec3(1.0f, 1.0f, 0.9f);
        ambientLightStrength = 0.7f;

        key1Pressed = true;
    } else if (glfwGetKey(window, GLFW_KEY_1) == GLFW_RELEASE) {
        key1Pressed = false;
    }

    if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS && !key2Pressed) {
        isDayTime = false;
        ambientLightStrength = 0.2f;
        lightPos = glm::vec3(0.0f, 30.0f, 0.0f);
        lightColor = glm::vec3(0.8f, 0.8f, 1.0f);

        key2Pressed = true;
    } else if (glfwGetKey(window, GLFW_KEY_2) == GLFW_RELEASE) {
        key2Pressed = false;
    }

    if (checkCollision()) {
        mainCamera -> Position = oldPosition;
    }
}

void Application::render()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    if (isDayTime) {
        glClearColor(0.5f, 0.8f, 1.0f, 1.0f); // Day sky
    } else {
        glClearColor(0.1f, 0.1f, 0.2f, 1.0f); // Night sky
    }

    //shader enable
    shader->use();
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    // view / projection
    glm::mat4 view = mainCamera -> GetViewMatrix();
    glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float) wWidth / (float) wHeight, 0.01f, 100.0f);

    // set light colors
    shader->setVec3("lightColor", lightColor);
    shader->setVec3("lightPosition", lightPos);
    shader->setFloat("ambientStrength", ambientLightStrength);

    // draw scene graph
    shader -> setMat4("view", view);
    shader -> setMat4("projection", projection);

    root -> DrawSelfAndChild(*shader);
    signatureRenderer->Draw(wWidth, wHeight);
}


void Application::updateTime()
{
    float curFrame = glfwGetTime();
    deltaTime = curFrame - lastFrame;
    lastFrame = curFrame;
}

void Application::framebuffer_size_callback(GLFWwindow* window, int width, int height)
{

}

bool Application::checkCollision() {
    glm::vec3 newPos = mainCamera -> Position;

    for (auto&& building : root -> children) {
        float dx = abs(building -> Trans.position.x - newPos.x);
        float dz = abs(building -> Trans.position.z - newPos.z);
        float dy = abs(building -> Trans.position.y - newPos.y);

        float halfWidth = building -> Trans.scale.x / 2.0f;
        float halfDepth = building -> Trans.scale.z / 2.0f;
        float halfHeight = building -> Trans.scale.y / 2.0f;

        if (dx < halfWidth && dz < halfDepth && dy < halfHeight) {
            return true;
        }
    }
    return false;
}

Application::~Application() {
    delete shader;
    delete root;
    delete mainCamera;
    glfwTerminate();
}
