#include <iostream>
#include "TextureManager.h"

shared_ptr<Texture> TextureManager::GetTexture(const string& _path)
{
    auto it = mLoadedTextures.find(_path);
    if (it != mLoadedTextures.end())
        return it->second;

    Texture texture;
    texture.loadFromFile(_path);
    shared_ptr<Texture> sharedTexture = make_shared<Texture>(texture);

    mLoadedTextures.insert(make_pair(_path, sharedTexture));

    return sharedTexture;
}