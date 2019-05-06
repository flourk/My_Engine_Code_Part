#pragma once

#include <resource/resource.h>
#include <GL/glew.h>

class Image;

class Texture : public Resource {
public:
    Texture();
    virtual ~Texture();

    void SetImage(Image* image);

    void Use();

    GLuint GetHandler() const { return m_handler; }

private:
    GLuint m_handler;
};