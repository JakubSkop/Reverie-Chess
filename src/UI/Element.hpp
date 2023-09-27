#pragma once

#include <SFML/Graphics.hpp>
#include <memory>
#include <stack>
#include <concepts>
#include "Interface.hpp"
#include "State.hpp"
#include "Resources/ResourcePackage.hpp"

namespace UI{

    template <class T>
    class Element : public UpdatesAndDraws{

        public:
            std::stack<std::shared_ptr<State<Element<T>>>> StateStack;
            T DrawableComponent;

            void Draw(Resources appResources) override;
            void Update(Resources appResources) override;

            Element(T drawableComponent);
            Element() = default;

    };

    template <class T>
    class ElementContainer : public Element<T>{

        public:
            std::vector<std::shared_ptr<Element<T>>> SubElements;

            void Draw(Resources appResources) override;
            void Update(Resources appResources) override;

    };


};

#include "Element.tpp"