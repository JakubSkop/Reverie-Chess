#include "ElementBuilders.hpp"
#include <optional>
#include <memory>
#include <iostream>
#include "../General/Constants.hpp"

sf::RectangleShape SolidColour(const sf::Color color, Vector2f size){
    RectangleShape rect{size};
    rect.setFillColor(color);
    return rect;
};


using PotentialStatePtr = std::optional<std::shared_ptr<State<Element<MemSprite>>>>;
using StatePtr = std::shared_ptr<State<Element<MemSprite>>>;

Element<MemSprite> BasicButtonBuilder(MemSprite image, std::function<void()> ClickFunction, Percentage hoverSizeIncrease, std::chrono::milliseconds hoverDelay, Percentage clickIndentDecrease){
    Element<MemSprite> Button;
    Button.DrawableComponent = image;

    auto StandardState = DefaultState<Element<MemSprite>>();
    auto HoveredState = DefaultState<Element<MemSprite>>();
    auto ClickedState = DefaultState<Element<MemSprite>>();

    //Standard State only switches to hovered state when the mouse is over the image
    //Rest of StandardState Callbacks can stay the same
    StandardState->UpdateCallback = [HoveredState](Element<MemSprite>* button ,Resources appResources) -> PotentialStatePtr{
        if(button->DrawableComponent.getGlobalBounds().contains(sf::Mouse::getPosition(*appResources.window).x, sf::Mouse::getPosition(*appResources.window).y)){
            return std::optional(HoveredState);
        } else {
            return std::nullopt;
        }
    };

    StandardState->EnterCallback = [](Element<MemSprite>* button){
        button->DrawableComponent.setScale(1,1);
    };

    //Update Callback for the Hovered State
    //Makes a button bigger when hovered over, and moves to clickedState when clicked, and moves to StandardState when mouse moves off it
    class HoveredUpdateFunctor{
        public:
            PotentialStatePtr operator()(Element<MemSprite>* button , Resources appResources){
                bool contains = button->DrawableComponent.getGlobalBounds().contains(sf::Mouse::getPosition(*appResources.window).x, sf::Mouse::getPosition(*appResources.window).y);
                timeElapsed += Constants::MS_PER_UPDATE;
                Scale += ScaleIncreasePerUpdate;

                auto event = appResources.eventList->MouseButtons.at("Left");
                if (event.Pressed && contains){
                    return std::optional(clickState);
                } else if (!contains){
                    timeElapsed = 0ms;
                    Scale = 1;
                    return std::optional(standardState);
                } else if (timeElapsed < hoverDelay){
                    button->DrawableComponent.setScale(Scale, Scale);
                } else if (timeElapsed >= hoverDelay){
                    button->DrawableComponent.setScale(FinalScale, FinalScale);
                }
                return std::nullopt;

            };
        
            HoveredUpdateFunctor(StatePtr click, StatePtr stand, Percentage g_hoverSizeIncrease, std::chrono::milliseconds g_hoverDelay){
                clickState = click;
                standardState = stand;
                hoverDelay = g_hoverDelay;
                Scale = 1;
                ScaleIncreasePerUpdate = g_hoverSizeIncrease*(static_cast<double>(Constants::MS_PER_UPDATE.count()) / hoverDelay.count())/100.0;
                FinalScale = 1.0+g_hoverSizeIncrease/100.0;
                timeElapsed = 0ms;
            };

        private:
            double Scale;
            std::chrono::milliseconds hoverDelay;
            double ScaleIncreasePerUpdate;
            std::chrono::milliseconds timeElapsed;
            StatePtr clickState;
            StatePtr standardState;
            double FinalScale;

    };


    HoveredState->UpdateCallback = HoveredUpdateFunctor(ClickedState, StandardState, hoverSizeIncrease, hoverDelay);

    ClickedState->ExitCallback = [ClickFunction, hoverSizeIncrease](Element<MemSprite>* button){
        double HoveredSizeScale = 1 + hoverSizeIncrease/100.0;
        button->DrawableComponent.setScale(HoveredSizeScale,HoveredSizeScale);
        ClickFunction();
    };

    ClickedState->EnterCallback = [clickIndentDecrease](Element<MemSprite>* button){
        double scaleDecrease = 1-clickIndentDecrease/100.0;
        button->DrawableComponent.scale(scaleDecrease, scaleDecrease);
    };

    ClickedState->UpdateCallback = [HoveredState](Element<MemSprite>* button ,Resources appResources) -> PotentialStatePtr{
        auto event = appResources.eventList->MouseButtons.at("Left");
        if (event.Released){
            return std::optional(HoveredState);
        }
        return std::nullopt;
    };

    Button.StateStack = {};
    Button.StateStack.push(StandardState);
    return Button;

};