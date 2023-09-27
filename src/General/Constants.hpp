#pragma once

#include <SFML/Graphics.hpp>
#include <chrono>
#include <vector>

using namespace std::literals;

namespace Constants {

    constexpr std::chrono::milliseconds MS_PER_UPDATE = 10ms;
    constexpr sf::Vector2<uint8_t> MAX_BOARD_DIMENSIONS{16,16};
    constexpr unsigned int MAX_BOARD_SIZE{MAX_BOARD_DIMENSIONS.x * MAX_BOARD_DIMENSIONS.y};
    constexpr sf::Vector2u ScreenSize{1920,1080};

    namespace Palette {
        inline const sf::Color Transparent{0, 0, 0, 0};
        inline const sf::Color White{255, 255, 255, 255};
        inline const sf::Color Cyan{12, 230, 242, 255};
        inline const sf::Color Teal{0, 152, 219, 255};
        inline const sf::Color Blue{30, 87, 156, 255};
        inline const sf::Color Navy{32, 53, 98, 255};
        inline const sf::Color Grey{37, 36, 70, 255};
        inline const sf::Color Black{32, 21, 51, 255};
    }

};