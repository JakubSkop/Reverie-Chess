#include "SliderElement.hpp"

Element<IntSlider> BasicSliderBuilder(IntSlider image, int minValue, int maxValue, std::function<void(int)> UpdateFunction){
    CenterOrigin(image.handle);
    image.handle.setPosition(image.bar.getGlobalBounds().getPosition().x + image.bar.getGlobalBounds().width, image.bar.getPosition().y);
    image.value = maxValue;

    Element<IntSlider> slider;
    slider.DrawableComponent = image;

    auto StandardState = std::make_shared<State<Element<IntSlider>>>();
    auto DraggedState = std::make_shared<State<Element<IntSlider>>>();

    auto drawFunction = [](Element<IntSlider>* element, Resources appResources){appResources.globalTexture->draw(element->DrawableComponent.bar);appResources.globalTexture->draw(element->DrawableComponent.handle);};
    StandardState->DrawCallback = drawFunction;
    DraggedState->DrawCallback = drawFunction;

    StandardState->UpdateCallback = [DraggedState](Element<IntSlider>* slider ,Resources appResources) -> PotentialStatePtr{
        bool handleContainsMouse = slider->DrawableComponent.handle.getGlobalBounds().contains(sf::Mouse::getPosition(*appResources.window).x, sf::Mouse::getPosition(*appResources.window).y);
        auto event = appResources.eventList->MouseButtons.at("Left");

        if(event.Pressed && handleContainsMouse){
            return std::optional(DraggedState);
        } else {
            return std::nullopt;
        };
    };

    DraggedState->UpdateCallback = [StandardState, minValue, maxValue, UpdateFunction](Element<IntSlider>* slider ,Resources appResources) -> PotentialStatePtr{
        auto mousePos = sf::Mouse::getPosition(*appResources.window);
        bool handleContainsMouse = slider->DrawableComponent.handle.getGlobalBounds().contains(mousePos.x, mousePos.y);
        auto event = appResources.eventList->MouseButtons.at("Left");

        if(event.Released){
            return std::optional(StandardState);
        } else {
            if (slider->DrawableComponent.bar.getGlobalBounds().contains(mousePos.x, slider->DrawableComponent.bar.getPosition().y)){
                slider->DrawableComponent.handle.setPosition(mousePos.x, slider->DrawableComponent.handle.getPosition().y);
            }
            auto length = (slider->DrawableComponent.bar.getGlobalBounds().width);
            auto relativeXpos =  slider->DrawableComponent.handle.getPosition().x - slider->DrawableComponent.bar.getGlobalBounds().getPosition().x;
            slider->DrawableComponent.value = (maxValue-minValue) * (relativeXpos/length);

            UpdateFunction(slider->DrawableComponent.value);

            return std::nullopt;
        };
    };

    StandardState->EnterCallback = [](Element<IntSlider>* slider){};
    StandardState->ExitCallback = [](Element<IntSlider>* slider){};
    DraggedState->EnterCallback = [](Element<IntSlider>* slider){};
    DraggedState->ExitCallback = [](Element<IntSlider>* slider){};

    slider.StateStack = {};
    slider.StateStack.push(StandardState);
    return slider;

}