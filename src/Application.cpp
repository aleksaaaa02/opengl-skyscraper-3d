//
// Created by aleksa on 6/15/25.
//

#include "Application.h"

#include <random>


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

    glEnable(GL_DEPTH_TEST);
    shader = new Shader("shaders/basic.vert", "shaders/basic.frag");
    return 0;
}

void Application::Run() {

    while(!glfwWindowShouldClose(window))
    {
        updateTime();
        processInput();
        render();

        if (checkCollision()) {
            std::cout << "Collision detected" << std::endl;
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

    std::shared_ptr<Mesh> cube = MeshFactory::CreateMesh(MeshType::CUBE);

    root = new SceneNode(cube);
    root->Trans.position = glm::vec3(0.0f, 0.0f, 0.0f);
    root->Trans.scale = {50.0f, 0.0f, 50.0f};

    // Create a grid of buildings with streets between them
    for (int x = -20; x <= 20; x += 4) {
        for (int z = -20; z <= 20; z += 4) {
            // Skip center area for spawn
            if (abs(x) < 4 && abs(z) < 4) continue;
            float height = heightDist(gen);
            std::unique_ptr<SceneNode> building = std::make_unique<SceneNode>(cube);
            building.get() -> Trans.scale = { 2.0f, height, 2.0f } ;
            building->Trans.position = { x, height/2.0f, z };
            root->AddChild(std::move(building));
        }
    }
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

    if (checkCollision()) {
        mainCamera -> Position = oldPosition;
    }
}

void Application::render()
{
    glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //shader enable
    shader->use();

    // view / projection
    glm::mat4 view = mainCamera -> GetViewMatrix();
    glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float) wWidth / (float) wHeight, 0.1f, 100.0f);

    // draw scene graph
    shader -> setMat4("view", view);
    shader -> setMat4("projection", projection);
    root -> DrawSelfAndChild(*shader);

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

        float halfWidth = building -> Trans.scale.x / 2.0f + 0.00001f;
        float halfDepth = building -> Trans.scale.z / 2.0f + 0.00001f;

        if (dx < halfWidth && dz < halfDepth) {
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


