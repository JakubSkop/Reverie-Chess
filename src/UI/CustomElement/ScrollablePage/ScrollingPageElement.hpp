#include "UI/ElementBuilders.hpp"
#include "UI/Element.hpp"
#include <optional>
#include <memory>
#include <iostream>
#include "General/Constants.hpp"
#include "General/Utilities.hpp"
#include "PageComponent.hpp"


using PotentialStatePtr = std::optional<std::shared_ptr<State<Element<ScrollingPageComponent>>>>;
using StatePtr = std::shared_ptr<State<Element<ScrollingPageComponent>>>;

class ScrollingPageBuilder{
    Element<ScrollingPageComponent> ScrollingPage;

    public:
        Element<ScrollingPageComponent> getObject();
        void addSubElement(Element<MemSprite> element);
        ScrollingPageBuilder(MemSprite PageImage);
};