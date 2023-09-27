#pragma once

#include "Element.hpp"
#include "State.hpp"
#include <chrono>
#include "UI/CustomSprite/MemSprite.hpp"
#include "General/Constants.hpp"

template <class T>
Element<T> StaticImage(T Image);

sf::RectangleShape SolidColour(const sf::Color color, Vector2f size = static_cast<Vector2f>(Constants::ScreenSize));

using Percentage = double;
using namespace std::literals::chrono_literals;

Element<MemSprite> BasicButtonBuilder(MemSprite image, std::function<void()> ClickFunction = [](){}, Percentage hoverSizeIncrease = 0.0, std::chrono::milliseconds hoverDelay = 0ms, Percentage clickIndentDecrease =0.0);

#include "ElementBuilders.tpp"