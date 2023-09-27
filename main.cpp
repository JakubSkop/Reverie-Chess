#include "Game/App.hpp"
#include <iostream>

int main()
{

    Application App;
    App.Setup();
    App.GameLoop();

    return 0;
}