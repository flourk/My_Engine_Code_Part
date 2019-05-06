#include "texture_loader.h"
#include "../resource_mgr.h"


TextureLoader::TextureLoader()
{
    m_supportedTypes = {};
}


void TextureLoader::RegisterToMgr()
{
    TextureLoader* loader = new TextureLoader();
    ResourceMgr::AddLoader(LoadFileType::FT_Texture, loader);
}

Resource* TextureLoader::Load(const String& path, ILoadOption* loadOption)
{
    Resource* ret = nullptr;

    Image* image = ResourceMgr::Load<Image>(path);
    if(!image)
        return nullptr;

    TextureLoadOption option;

    if(loadOption)
        option = *((TextureLoadOption*)loadOption);

    if(option.eTextureUsage == TextureUsage_2D)
    {
        Texture2D* texture = new Texture2D();
        texture->SetImage(image);

        ret = texture;
    }

    return ret;         
}
