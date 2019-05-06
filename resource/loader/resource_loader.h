#pragma once

#include <vector>
#include <core/string_ex.h>
#include "../resource.h"
#include "load_file_type.h"

struct ILoadOption {
    static const LoadFileType loadType = FT_Unkown;
};


class IResourceLoader {
public:
    virtual Resource* Load(const String& path, ILoadOption* loadOption = nullptr) = 0;
    virtual bool IsSupported(const String& ext);

protected:
    std::vector<String> m_supportedTypes;
};