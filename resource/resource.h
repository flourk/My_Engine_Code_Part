#pragma once

class Resource
{
public:
    template<typename T>
    T* As()
    {
        return (T*)(this);
    }

};