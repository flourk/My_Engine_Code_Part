#pragma once

#include <string>

class String : public std::basic_string<char> {
public:
    typedef std::basic_string<char> Base;
    using Base::Base;
};