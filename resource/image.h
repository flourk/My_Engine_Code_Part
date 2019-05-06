#pragma once

#include "resource.h"

class Image : public Resource
{
public:
    Image();
    Image(int width, int height, int component);

    inline int GetWidth() { return m_width; }
    inline int GetHeight() { return m_height;}
    inline unsigned char* GetData() { return m_data; }

    void SetData(int width, int height, int component, unsigned char* data);

private:
    int m_width;
    int m_height;
    int m_component;
    unsigned char* m_data;
};