#pragma once

#include <map>
#include <string>
#include <set>
#include <core/string_ex.h>
#include "resource.h"
#include "loader/load_file_type.h"
#include "loader/loader_trait.h"
#include "loader/image_loader.h"
#include "loader/texture_loader.h"


class SceneNode;
class Shader;

class IResourceLoader;
struct ILoadOption;

class ResourceMgr final {
public:
    static void RegisterLoaders();

    static void AddLoader(LoadFileType fileType, IResourceLoader* loader);

    static void PreCacheShader();
    static SceneNode* LoadModel(const char* name);

    static Shader* GetShader(const char* name);

    static Resource* Load(const String& path, ILoadOption* option = nullptr);

    template<typename T>
    static T* Load(const String& path, ILoadOption* option = nullptr)
    {
        Resource* res = nullptr;
        if(option)
        {
            auto it = m_loaders.find(option->loadType);
            if(it != m_loaders.end())
               res = it->second->Load(path, option);
        }

        if(res)
        {
            return res->As<T>();
        }


        LoaderTrait<T>::Loader loader;

        LoaderTrait<T>::LoadOption loadOption;
        if(option)
        {
            loadOption = *((LoaderTrait<T>::LoadOption*) option);
        }
        else
        {
            loadOption = LoaderTrait<T>::GetDefaultOption();
        }

        res = loader.Load(path, &loadOption);

        if(!res)
            return nullptr;

        return res->As<T>();
    }


private:
    static std::map<std::string, Shader*> m_shaderCache;
    static std::map<LoadFileType, IResourceLoader*> m_loaders;
};