#pragma once

#include "resource_loader.h"

struct ImageLoadOption : public ILoadOption
{
    static const LoadFileType loadType = FT_Image;
};


class ImageLoader : public IResourceLoader {
public:
    ImageLoader();

    static void RegisterToMgr();

    virtual Resource* Load(const String& path, ILoadOption* loadOption = nullptr) override;
};