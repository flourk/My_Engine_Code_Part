#pragma once

#include "resource_loader.h"
#include <render/texture.h>
#include <render/texture2D.h>

enum TextureUsage
{
    TextureUsage_2D,
    TextureUsage_CUBE,
};

struct TextureLoadOption : public ILoadOption
{
public:
    static const LoadFileType loadType = FT_Texture;


    TextureLoadOption()
    {
        eTextureUsage = TextureUsage_2D;
    }

    TextureUsage eTextureUsage;
};

class TextureLoader : public IResourceLoader {
public:
    TextureLoader();

    static void RegisterToMgr();

    virtual Resource* Load(const String& path, ILoadOption* loadOption = nullptr) override;
};