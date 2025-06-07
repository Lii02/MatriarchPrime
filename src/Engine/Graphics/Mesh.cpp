#include "pch.h"
#include "Mesh.h"

liMesh::liMesh() {
    glGenVertexArrays(1, &vao);
    glGenBuffers(2, &vbo);
}

liMesh::~liMesh() {
    glDeleteBuffers(2, &vbo);
    glDeleteVertexArrays(1, &vao);
}

void liMesh::Upload(liVertexList* vertices, liUIntBuffer* indices) {
    this->drawCount = indices->size();
    glBindVertexArray(vao);
    
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, vertices->size() * sizeof(liVertex), vertices->data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(liVertex), (void*)0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(liVertex), (void*)offsetof(liVertex, texCoord));
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(liVertex), (void*)offsetof(liVertex, normal));
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices->size() * sizeof(uint_t), indices->data(), GL_STATIC_DRAW);
    glBindVertexArray(0);
}

void liMesh::Draw(topology_t topology, ulong_t start, long_t count) {
    ulong_t c = count;
    if(count < 0) {
        c = drawCount;
    }
    glBindVertexArray(vao);
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);
    glDrawElements((uint_t)topology, drawCount, GL_UNSIGNED_INT, (void*)(start * sizeof(uint_t)));
    glBindVertexArray(0);
}