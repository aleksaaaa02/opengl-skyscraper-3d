#include <signature_renderer.h>

void SignatureRenderer::Draw(float wWidth, float wHeight) {
    shader -> use();
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textureId);
    glBindVertexArray(vao);
    shader -> setInt("uText", 0);
    glm::mat4 projection = glm::ortho(0.0f, (float)wWidth, 0.0f, (float)wHeight);
    shader -> setMat4("projection", projection);

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glBindTexture(GL_TEXTURE_2D,0);
    glBindVertexArray(0);
    glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);

}

SignatureRenderer::SignatureRenderer(const char *imageResPath)
{
    shader = new Shader("./shaders/text.vert", "./shaders/text.frag");
    // Setup signature quad in screen coordinates (bottom-right corner)
    float sigWidth = 300.0f;  // Width in pixels
    float sigHeight = 200.0f;  // Height in pixels
    float sigX = 0;  // 20 pixels from right edge
    float sigY = 0; // 20 pixels from bottom edge

    float signatureVertices[] = {
    // positions       // tex coords
    sigWidth - 20.0f, 0.0f, 1.0f, 0.0f,  // top right
    sigWidth - 20.0f, sigHeight - 20.0f, 1.0f, 1.0f,  // bottom right
    0.0f, sigHeight - 20.0f, 0.0f, 1.0f,  // bottom left
    0.0f, 0.0f, 0.0f, 0.0f   // top left
    };


    unsigned int signatureIndices[] = {
        0, 1, 3,
        1, 2, 3,
    };

    textureId = loadImageToTexture(imageResPath);
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    glGenBuffers(1, &ebo);

    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(signatureVertices), signatureVertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(signatureIndices), signatureIndices, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));

    glBindVertexArray(0);
}

unsigned SignatureRenderer::loadImageToTexture(const char* filePath) {
    int TextureWidth;
    int TextureHeight;
    int TextureChannels;
    stbi_set_flip_vertically_on_load(true);
    unsigned char* ImageData = stbi_load(filePath, &TextureWidth, &TextureHeight, &TextureChannels, 0);

    if (ImageData != NULL) {
        // stbi__vertical_flip(ImageData, TextureWidth, TextureHeight, TextureChannels);

        GLint InternalFormat = -1;
        switch (TextureChannels) {
            case 1: InternalFormat = GL_RED; break;
            case 2: InternalFormat = GL_RG; break;
            case 3: InternalFormat = GL_RGB; break;
            case 4: InternalFormat = GL_RGBA; break;
            default: InternalFormat = GL_RGB; break;
        }

        unsigned int Texture;
        glGenTextures(1, &Texture);
        glBindTexture(GL_TEXTURE_2D, Texture);
        glTexImage2D(GL_TEXTURE_2D, 0, InternalFormat, TextureWidth, TextureHeight, 0, InternalFormat, GL_UNSIGNED_BYTE, ImageData);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        glBindTexture(GL_TEXTURE_2D, 0);

        stbi_image_free(ImageData);
        return Texture;
    }
    std::cout << "Fail to load texture: " << filePath << std::endl;
    stbi_image_free(ImageData);
    return 0;
}