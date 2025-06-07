#ifndef MESH_H
#define MESH_H
#pragma once
#include "Engine/Math/Vertex.h"

enum class topology_t {
    POINTS = 0x0,
    LINES = 0x1,
    TRIANGLES = 0x4
};

class liMesh {
    friend class liVertex;
public:
    liMesh();
    liMesh(const liMesh&) = delete;
    ~liMesh();

    void Upload(liVertexList* vertices, liUIntBuffer* indices);
    void Draw(topology_t topology = topology_t::TRIANGLES, ulong_t start = 0, long_t count = -1);
private:
    ghandle_t vao, vbo, ibo;
    ulong_t drawCount;
};

#endif