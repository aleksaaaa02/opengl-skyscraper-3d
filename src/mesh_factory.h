#pragma once
#ifndef MESH_FACTORY_H
#define MESH_FACTORY_H

#include "mesh.h"
#include <memory>

enum class MeshType {
    CUBE,
    SPHERE,
    PLANE,
};

class MeshFactory {
public:
    // Factory method - returns shared_ptr for automatic memory management
    static std::shared_ptr<Mesh> CreateMesh(MeshType type);

private:
    static std::shared_ptr<Mesh> CreateCube();
    static std::shared_ptr<Mesh> CreateSphere(int segments = 32);
    static std::shared_ptr<Mesh> CreatePlane(float width = 2.0f, float height = 2.0f);
};


#endif //MESH_FACTORY_H
