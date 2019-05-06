#include "image.h"
#include <memory.h>

Image::Image() :
    m_width(0),
    m_height(0),
    m_component(0),
    m_data(nullptr)
{
}


Image::Image(int width, int height, int component) :
    m_width(width),
    m_height(height),
    m_component(component)
{
    m_data = new unsigned char[m_width * m_height * m_component];
}


void Image::SetData(int width, int height, int component, unsigned char* data)
{
    m_width = width;
    m_height = height;
    m_component = component;

    if(m_data)
    {
        delete[] m_data;
    }

    m_data = new unsigned char[m_width * m_height * m_component];
    memcpy(m_data, data, m_width * m_height * m_component * sizeof(unsigned char));
}
