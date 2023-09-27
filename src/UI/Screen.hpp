#pragma once

#include <memory>
#include <vector>
#include <functional>
#include "Interface.hpp"
#include "Resources/ResourcePackage.hpp"


struct Resources; 
class UpdatesAndDraws;
//Forward Declarations to remove cyclic dependency

struct Screen{
    void DrawElements(Resources appResources);
    void UpdateElements(Resources appResources);

    std::function<void()> PushCallback = [](){};
    std::vector<std::shared_ptr<UpdatesAndDraws>> Elements;
    bool DrawUnder = false;
    bool UpdateUnder = false;

};