#ifndef VERTEX_H
#define VERTEX_H
#pragma once
#include "Vectors.h"

class liVertex {
public:
    liVertex(liVec3 position, liVec2 texCoord, liVec3 normal);
    liVertex();

    void SetPosition(liVec3 position);
    liVec3 Position() const { return position; }
    
    void SetTexCoord(liVec2 texCoord);
    liVec2 TexCoord() const { return texCoord; }

    void SetNormal(liVec3 normal);
    liVec3 Normal() const { return normal; }
private:
    liVec3 position;
    liVec2 texCoord;
    liVec3 normal;
};

typedef std::vector<liVertex> liVertexList;

#endif