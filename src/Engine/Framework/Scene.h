#ifndef SCENE_H
#define SCENE_H
#pragma once
#include "Asset.h"
#include "Actor.h"

class liScene : public liAsset {
public:
    liScene();
    liScene(const liScene&) = delete;
    ~liScene();
private:
};

#endif