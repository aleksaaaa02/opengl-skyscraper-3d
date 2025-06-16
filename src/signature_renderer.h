//
// Created by aleksa on 6/16/25.
//

#pragma once
#include <stb_image.h>
#ifndef SIGNATURE_RENDERER_H
#include <glm/vec2.hpp>
#include <shader.h>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

class SignatureRenderer {
    Shader* shader = nullptr;
    unsigned int textureId, vao, vbo, ebo;
    static unsigned loadImageToTexture(const char* filePath);
public:
    explicit SignatureRenderer(const char *imageResPath);
    SignatureRenderer() {

    }
    void Draw(float wWidth, float wHeight);
    glm::vec2 position = { 0.0f, 0.0f };
};

#endif //SIGNATURE_RENDERER_H
