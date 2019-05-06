#include "image_loader.h"
#include "../resource_mgr.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include "../image.h"

ImageLoader::ImageLoader()
{
    m_supportedTypes = { ".png", ".jpg"};
}

void ImageLoader::RegisterToMgr()
{
    ImageLoader* loader = new ImageLoader;
    ResourceMgr::AddLoader(LoadFileType::FT_Image, loader);
}

Resource* ImageLoader::Load(const String& path, ILoadOption* loadOption)
{

    Resource* ret = nullptr;

    int w, h, c;
    unsigned char* data = stbi_load(path.c_str(), &w, &h, &c, 0);

    Image* image = new Image();
    image->SetData(w, h, c, data);

    stbi_image_free(data);

    ret = image;
    
    return ret;
}