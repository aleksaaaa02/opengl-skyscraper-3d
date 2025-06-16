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
        {{ -0.5f, -0.5f, -0.5f},  { 0.0f,  0.0f, -1.0f}},
        {{  0.5f,  0.5f, -0.5f},  { 0.0f,  0.0f, -1.0f}},
        {{  0.5f, -0.5f, -0.5f},  { 0.0f,  0.0f, -1.0f}},

        {{  0.5f,  0.5f, -0.5f},  { 0.0f,  0.0f, -1.0f}},
        {{ -0.5f, -0.5f, -0.5f},  { 0.0f,  0.0f, -1.0f}},
        {{ -0.5f,  0.5f, -0.5f},  { 0.0f,  0.0f, -1.0f}},

        {{ -0.5f, -0.5f,  0.5f},  { 0.0f,  0.0f,  1.0f}},
        {{  0.5f, -0.5f,  0.5f},  { 0.0f,  0.0f,  1.0f}},
        {{  0.5f,  0.5f,  0.5f},  { 0.0f,  0.0f,  1.0f}},

        {{  0.5f,  0.5f,  0.5f},  { 0.0f,  0.0f,  1.0f}},
        {{ -0.5f,  0.5f,  0.5f},  { 0.0f,  0.0f,  1.0f}},
        {{ -0.5f, -0.5f,  0.5f},  { 0.0f,  0.0f,  1.0f}},

        {{ -0.5f,  0.5f,  0.5f}, { -1.0f,  0.0f,  0.0f}},
        {{ -0.5f,  0.5f, -0.5f}, { -1.0f,  0.0f,  0.0f}},
        {{ -0.5f, -0.5f, -0.5f}, { -1.0f,  0.0f,  0.0f}},

        {{ -0.5f, -0.5f, -0.5f}, { -1.0f,  0.0f,  0.0f}},
        {{ -0.5f, -0.5f,  0.5f}, { -1.0f,  0.0f,  0.0f}},
        {{ -0.5f,  0.5f,  0.5f}, { -1.0f,  0.0f,  0.0f}},

        {{  0.5f,  0.5f,  0.5f},  { 1.0f,  0.0f,  0.0f}},
        {{  0.5f, -0.5f, -0.5f},  { 1.0f,  0.0f,  0.0f}},
        {{  0.5f,  0.5f, -0.5f},  { 1.0f,  0.0f,  0.0f}},

        {{  0.5f, -0.5f, -0.5f},  { 1.0f,  0.0f,  0.0f}},
        {{  0.5f,  0.5f,  0.5f},  { 1.0f,  0.0f,  0.0f}},
        {{  0.5f, -0.5f,  0.5f},  { 1.0f,  0.0f,  0.0f}},

        {{ -0.5f, -0.5f, -0.5f},  { 0.0f, -1.0f,  0.0f}},
        {{  0.5f, -0.5f, -0.5f},  { 0.0f, -1.0f,  0.0f}},
        {{  0.5f, -0.5f,  0.5f},  { 0.0f, -1.0f,  0.0f}},

        {{  0.5f, -0.5f,  0.5f},  { 0.0f, -1.0f,  0.0f}},
        {{ -0.5f, -0.5f,  0.5f},  { 0.0f, -1.0f,  0.0f}},
        {{ -0.5f, -0.5f, -0.5f},  { 0.0f, -1.0f,  0.0f}},

        {{ -0.5f,  0.5f, -0.5f},  { 0.0f,  1.0f,  0.0f}},
        {{  0.5f,  0.5f,  0.5f},  { 0.0f,  1.0f,  0.0f}},
        {{  0.5f,  0.5f, -0.5f},  { 0.0f,  1.0f,  0.0f}},

        {{  0.5f,  0.5f,  0.5f},  { 0.0f,  1.0f,  0.0f}},
        {{ -0.5f,  0.5f, -0.5f},  { 0.0f,  1.0f,  0.0f}},
        {{ -0.5f,  0.5f,  0.5f},  { 0.0f,  1.0f,  0.0f}},
    };

    return std::make_unique<Mesh>(vertices);
}

std::shared_ptr<Mesh> MeshFactory::CreateSphere(int segments) {
 std::vector<Vertex> vertices;

    float radius = 0.5f;

    // Precompute vertices positions and normals in a grid
    std::vector<Vertex> tempVertices;
    for (int lat = 0; lat <= segments; ++lat) {
        float theta = lat * M_PI / segments;
        float sinTheta = sin(theta);
        float cosTheta = cos(theta);

        for (int lon = 0; lon <= segments; ++lon) {
            float phi = lon * 2 * M_PI / segments;
            float sinPhi = sin(phi);
            float cosPhi = cos(phi);

            glm::vec3 normal = {
                cosPhi * sinTheta,
                cosTheta,
                sinPhi * sinTheta
            };
            glm::vec3 position = normal * radius;


            tempVertices.push_back({position, normal});
        }
    }

    // Create triangles explicitly (no indices)
    for (int lat = 0; lat < segments; ++lat) {
        for (int lon = 0; lon < segments; ++lon) {
            int first = lat * (segments + 1) + lon;
            int second = first + segments + 1;

            // Triangle 1
            vertices.push_back(tempVertices[first]);
            vertices.push_back(tempVertices[second]);
            vertices.push_back(tempVertices[first + 1]);

            // Triangle 2
            vertices.push_back(tempVertices[second]);
            vertices.push_back(tempVertices[second + 1]);
            vertices.push_back(tempVertices[first + 1]);
        }
    }

    return std::make_unique<Mesh>(vertices);
}

std::shared_ptr<Mesh> MeshFactory::CreatePlane(float width, float height) {
    float halfWidth = width * 0.5f;
    float halfHeight = height * 0.5f;

    glm::vec3 normal = {0.0f, 1.0f, 0.0f};

    // Define 6 vertices (2 triangles), each with position, normal, color
    std::vector<Vertex> vertices = {
        // First triangle
        {{-halfWidth, 0.0f, -halfHeight}, normal}, // bottom-left
        {{ halfWidth, 0.0f,  halfHeight}, normal}, // top-right
        {{ halfWidth, 0.0f, -halfHeight}, normal}, // bottom-right

        // Second triangle
        {{-halfWidth, 0.0f, -halfHeight}, normal}, // bottom-left
        {{-halfWidth, 0.0f,  halfHeight}, normal},  // top-left
        {{ halfWidth, 0.0f,  halfHeight}, normal}, // top-right
    };

    return std::make_unique<Mesh>(vertices);
}
