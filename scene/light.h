#pragma once

#include "scene_node.h"

enum LightType {
    Directional,
    Point,
    Spot,
};

class Light : public SceneNode {
public:
    Light();
    ~Light();

    inline const Vec4f GetColor()
    {
        return m_color;
    }

    LightType GetType()
    {
        return m_type;
    }


private:
    LightType m_type;
    Vec4f m_color;
    float m_intensity;
};