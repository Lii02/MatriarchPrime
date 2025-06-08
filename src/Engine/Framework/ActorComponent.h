#ifndef ACTORCOMPONENT_H
#define ACTORCOMPONENT_H
#pragma once

class liActor;

enum actorComponentType_t {
    COMPONENT_MESHRENDERER,
    COMPONENT_COUNT
};

class liActorComponent {
    friend class liActor;
public:
    liActorComponent(actorComponentType_t type);
    virtual ~liActorComponent() { }

    virtual void Render() = 0;
    virtual void Update(float deltaTime) = 0;

    liActor* Owner() { return owner; }
protected:
    liActor* owner;
    actorComponentType_t type;
};

#endif