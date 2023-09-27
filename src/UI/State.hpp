#pragma once

#include "Element.hpp"
#include <functional>
#include <memory>
#include <optional>
#include "Resources/ResourcePackage.hpp"


namespace UI {

    //The State class contains 4 callbacks for each action the UI element needs to take
    template <class D>
    struct State{
        std::function<void(D* element)> EnterCallback;
        std::function<void(D* element)> ExitCallback;
        std::function<void(D* element, Resources appResources)> DrawCallback;
        std::function<std::optional<std::shared_ptr<State<D>>>(D* element, Resources appResources)> UpdateCallback;
    };

    //Simply draws the drawableComponent and doesn't do anything on update, exit or enter;
    template <class D>
    std::shared_ptr<State<D>> DefaultState(){
        auto s = std::make_shared<State<D>>();
        s->EnterCallback = [](D* element){};
        s->ExitCallback = [](D* element){};
        s->DrawCallback = [](D* element, Resources appResources){appResources.globalTexture->draw(element->DrawableComponent);};
        s->UpdateCallback = [](D* element, Resources appResources){return std::nullopt;};
        return s;
    };

};