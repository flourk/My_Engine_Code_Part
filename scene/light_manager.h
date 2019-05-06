#pragma once
#include <vector>

class Light;
class Material;

class LightManager {
public:
    static void SetupLight(Material* material);

protected:
    friend class Light;

    static void AddLight(Light* light);
    static void RemoveLight(Light* light);

private:
    static std::vector<Light*> m_lights;
};