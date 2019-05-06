#pragma once

#include "../image.h"
#include "image_loader.h"
#include "texture_loader.h"

template<typename T>
struct LoaderTrait;

template<> struct LoaderTrait<Image>
{
    typedef ImageLoader Loader;
    typedef ImageLoadOption LoadOption;

    static ImageLoadOption GetDefaultOption()
    {
        return ImageLoadOption();
    }
};

template<> struct LoaderTrait<Texture>
{
    typedef TextureLoader Loader;
    typedef TextureLoadOption LoadOption;


    static TextureLoadOption GetDefaultOption()
    {
        TextureLoadOption option;
        option.eTextureUsage = TextureUsage_2D;

        return option;
    }
};

template<> struct LoaderTrait<Texture2D>
{
    typedef TextureLoader Loader;
    typedef TextureLoadOption LoadOption;

    static TextureLoadOption GetDefaultOption()
    {
        TextureLoadOption option;
        option.eTextureUsage = TextureUsage_2D;

        return option;
    }
};