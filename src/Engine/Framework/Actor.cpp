#include "pch.h"
#include "Actor.h"

liActor::liActor(std::string name) {
    this->name = name;

    for(ulong_t i = 0; i < actorComponentType_t::COMPONENT_COUNT; i++) {
        components[i] = nullptr;
    }
}

liActor::~liActor() {
    for(ulong_t i = 0; i < actorComponentType_t::COMPONENT_COUNT; i++) {
        if(components[i] != nullptr) {
            delete components[i];
        }
    }
}

void liActor::Render() {
    for(ulong_t i = 0; i < actorComponentType_t::COMPONENT_COUNT; i++) {
        if(components[i] != nullptr) {
            components[i]->Render();
        }
    }
}

void liActor::Update(float deltaTime) {
    for(ulong_t i = 0; i < actorComponentType_t::COMPONENT_COUNT; i++) {
        if(components[i] != nullptr) {
            components[i]->Update(deltaTime);
        }
    }
}

void liActor::AddComponent(liActorComponent* compoment) {
    liActorComponent* dest = components[compoment->type];
    if(dest == nullptr) {
        delete dest;
    }
    components[compoment->type] = compoment;
}

void liActor::RemoveComponent(actorComponentType_t type) {
    assert(type < actorComponentType_t::COMPONENT_COUNT);
    liActorComponent* dest = components[type];
    if(dest != nullptr) {
        delete dest;
    }
    components[type] = nullptr;
}