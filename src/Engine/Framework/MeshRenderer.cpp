#include "pch.h"
#include "MeshRenderer.h"

liMeshRenderer::liMeshRenderer(liMesh* mesh, topology_t topology, ulong_t start, ulong_t count) 
    : liActorComponent(actorComponentType_t::COMPONENT_MESHRENDERER) {
        this->mesh = mesh;
        this->topology = topology;
        this->start = start;
        this->count = count;
}

liMeshRenderer::~liMeshRenderer() {
}

void liMeshRenderer::Render() {
    if(mesh != nullptr) { 
        mesh->Draw(topology, start, count);
    }
}

void liMeshRenderer::Update(float deltaTime) {
}