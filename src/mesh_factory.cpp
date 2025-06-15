#include "mesh_factory.h"

std::shared_ptr<Mesh> MeshFactory::CreateMesh(MeshType type) {
    switch (type) {
        case MeshType::CUBE:
            return CreateCube();
        case MeshType::SPHERE:
            return CreateSphere();
        case MeshType::PLANE:
            return CreatePlane();
        default:
            return nullptr;
    }
}
std::shared_ptr<Mesh> MeshFactory::CreateCube() {
    std::vector<Vertex> vertices = {
        // Unique vertices of a cube
        {{-0.5f, -0.5f, -0.5f}, {0.0f, 0.0f, 0.0f, 1.0f}}, // 0: back-bottom-left
        {{ 0.5f, -0.5f, -0.5f}, {1.0f, 0.0f, 0.0f, 1.0f}}, // 1: back-bottom-right
        {{ 0.5f,  0.5f, -0.5f}, {1.0f, 1.0f, 0.0f, 1.0f}}, // 2: back-top-right
        {{-0.5f,  0.5f, -0.5f}, {0.0f, 1.0f, 0.0f, 1.0f}}, // 3: back-top-left
        {{-0.5f, -0.5f,  0.5f}, {0.0f, 0.0f, 1.0f, 1.0f}}, // 4: front-bottom-left
        {{ 0.5f, -0.5f,  0.5f}, {1.0f, 0.0f, 1.0f, 1.0f}}, // 5: front-bottom-right
        {{ 0.5f,  0.5f,  0.5f}, {1.0f, 1.0f, 1.0f, 1.0f}}, // 6: front-top-right
        {{-0.5f,  0.5f,  0.5f}, {0.0f, 1.0f, 1.0f, 1.0f}}  // 7: front-top-left
    };

    std::vector<unsigned int> indices = {
        // Back face (z = -0.5)
        0, 1, 2,   2, 3, 0,
        // Front face (z = 0.5)
        4, 5, 6,   6, 7, 4,
        // Left face (x = -0.5)
        4, 0, 3,   3, 7, 4,
        // Right face (x = 0.5)
        1, 5, 6,   6, 2, 1,
        // Bottom face (y = -0.5)
        0, 1, 5,   5, 4, 0,
        // Top face (y = 0.5)
        3, 2, 6,   6, 7, 3
    };

    return std::make_unique<Mesh>(vertices, indices);
}

std::shared_ptr<Mesh> MeshFactory::CreateSphere(int segments) {
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;

    float radius = 0.5f;

    // Generate vertices
    for (int lat = 0; lat <= segments; ++lat) {
        float theta = lat * M_PI / segments;
        float sinTheta = sin(theta);
        float cosTheta = cos(theta);

        for (int lon = 0; lon <= segments; ++lon) {
            float phi = lon * 2 * M_PI / segments;
            float sinPhi = sin(phi);
            float cosPhi = cos(phi);

            float x = cosPhi * sinTheta;
            float y = cosTheta;
            float z = sinPhi * sinTheta;

            // Color based on position
            glm::vec4 color = {
                (x + 1.0f) * 0.5f,
                (y + 1.0f) * 0.5f,
                (z + 1.0f) * 0.5f,
                1.0f
            };

            vertices.push_back({{x * radius, y * radius, z * radius}, color});
        }
    }

    // Generate indices
    for (int lat = 0; lat < segments; ++lat) {
        for (int lon = 0; lon < segments; ++lon) {
            int first = lat * (segments + 1) + lon;
            int second = first + segments + 1;

            indices.push_back(first);
            indices.push_back(second);
            indices.push_back(first + 1);

            indices.push_back(second);
            indices.push_back(second + 1);
            indices.push_back(first + 1);
        }
    }

    return std::make_unique<Mesh>(vertices, indices);
}

std::shared_ptr<Mesh> MeshFactory::CreatePlane(float width, float height) {
    float halfWidth = width * 0.5f;
    float halfHeight = height * 0.5f;

    std::vector<Vertex> vertices = {
        {{-halfWidth, 0.0f, -halfHeight}, {0.0f, 1.0f, 0.0f, 1.0f}}, // bottom-left
        {{ halfWidth, 0.0f, -halfHeight}, {1.0f, 1.0f, 0.0f, 1.0f}}, // bottom-right
        {{ halfWidth, 0.0f,  halfHeight}, {1.0f, 1.0f, 1.0f, 1.0f}}, // top-right
        {{-halfWidth, 0.0f,  halfHeight}, {0.0f, 1.0f, 1.0f, 1.0f}}  // top-left
    };

    std::vector<unsigned int> indices = {
        0, 1, 2,   2, 3, 0
    };

    return std::make_unique<Mesh>(vertices, indices);
}
