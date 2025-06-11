#ifndef ASSETMANAGER_H
#define ASSETMANAGER_H
#pragma once
#include "Asset.h"

class liAssetManager {
    friend class liAsset;
public:
    liAssetManager();
    liAssetManager(const liAssetManager&) = delete;
    ~liAssetManager();

    liAsset* LoadAsset(std::string name, liAsset* asset);
    void UnloadAsset(std::string name);
    void UnloadAssets();
    template <typename AssetType>
    AssetType* FindAssetByName(std::string name);
    template <typename AssetType>
    AssetType* FindAssetByGUID(guid_t guid);
private:
    std::map<std::string, liAsset*> assets;
};

template <typename AssetType>
AssetType* liAssetManager::FindAssetByName(std::string name) {
    return nullptr;
}

template <typename AssetType>
AssetType* liAssetManager::FindAssetByGUID(guid_t name) {
    return nullptr;
}

#endif