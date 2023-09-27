#include "ScreensImpl.hpp"

std::shared_ptr<Screen> HomeScreen2(Resources resources){
    auto spriteHolder = resources.spriteManager;
    auto conductor = resources.screenConductor;
    auto audio = resources.soundPlayer;

    auto home = std::make_shared<Screen>();
    home->DrawUnder = false;
    home->UpdateUnder = false;
    home->PushCallback = [audio](){if(audio->GetCurrentMusic() != "Reverie Unfolds"){audio->PlayMusic("Reverie Unfolds");};};

    UI::Element<MemSprite> Splash = StaticImage(spriteHolder->AccessSprite("HomeSplashScreen"));

    //Level Button Initiliazation
    auto LevelButtonSprite = spriteHolder->AccessSprite("LevelButton");
    CenterOrigin(LevelButtonSprite);
    LevelButtonSprite.setPosition(50.0_perW, 45.0_perH);
    UI::Element<MemSprite> LevelButton = BasicButtonBuilder(LevelButtonSprite, [conductor](){conductor->PushScreen("Levels");}, 10, 100ms, 5);

    //Settings Button Initiliazation
    auto TeamSprite = spriteHolder->AccessSprite("TeamButton");
    CenterOrigin(TeamSprite);
    TeamSprite.setPosition(50.0_perW, 57.0_perH);
    UI::Element<MemSprite> TeamButton = BasicButtonBuilder(TeamSprite, [](){}, 10, 100ms, 5);

    //Back Button
    auto backButtonSprite = spriteHolder->AccessSprite("PointyArrowButton");
    backButtonSprite.setPosition(20, 20);
    UI::Element<MemSprite> backButton = BasicButtonBuilder(backButtonSprite, [conductor](){conductor->PopScreen();}, 10, 100ms, 20);
    
    home->Elements.push_back(std::make_shared<UI::Element<MemSprite>>(Splash));
    home->Elements.push_back(std::make_shared<UI::Element<MemSprite>>(LevelButton));
    home->Elements.push_back(std::make_shared<UI::Element<MemSprite>>(TeamButton));
    home->Elements.push_back(std::make_shared<UI::Element<MemSprite>>(backButton));

    return home;
}
