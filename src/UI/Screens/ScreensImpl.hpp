#pragma once

#include "../Screen.hpp"
#include "../ElementBuilders.hpp"
#include "General/Utilities.hpp"

std::shared_ptr<Screen> HomeScreen(Resources resources);
std::shared_ptr<Screen> HomeScreen2(Resources resources);
std::shared_ptr<Screen> LevelScreen(Resources resources);
std::shared_ptr<Screen> SettingsScreen(Resources resources);
std::shared_ptr<Screen> TeamSelectScreen(Resources resources, unsigned int levelNum);

