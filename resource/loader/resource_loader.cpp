#include "resource_loader.h"

bool IResourceLoader::IsSupported(const String& ext)
{
    auto it = std::find(m_supportedTypes.begin(), m_supportedTypes.end(), ext);
    return it != m_supportedTypes.end();
}
