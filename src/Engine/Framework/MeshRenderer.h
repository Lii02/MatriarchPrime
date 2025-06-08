#ifndef MESHRENDERER_H
#define MESHRENDERER_H
#pragma once
#include "ActorComponent.h"
#include "Engine/Graphics/Mesh.h"

class liMeshRenderer : public liActorComponent {
public:
    liMeshRenderer(liMesh* mesh, topology_t topology = topology_t::TRIANGLES, ulong_t start = 0, ulong_t count = -1);
    ~liMeshRenderer();

    virtual void Render() override;
    virtual void Update(float deltaTime) override;
    
    inline void SetMesh(liMesh* mesh) { this->mesh = mesh; }
    inline liMesh* Mesh() { return mesh; }
private:
    liMesh* mesh;
    topology_t topology;
    ulong_t start, count;
};

#endif