#pragma once
#include <string>

class Loadable
{

public:
    virtual void load(const std::string &fileName) = 0;
};