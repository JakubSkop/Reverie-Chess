#include "ScreensImpl.hpp"

std::shared_ptr<Screen> HomeScreen(Resources resources){
    auto spriteHolder = resources.spriteManager;
    auto conductor = resources.screenConductor;
    auto audio = resources.soundPlayer;

    auto home = std::make_shared<Screen>();
    home->DrawUnder = false;
    home->UpdateUnder = false;
    home->PushCallback = [audio](){audio->PlayMusic("Reverie Unfolds");};

    UI::Element<MemSprite> Splash = StaticImage(spriteHolder->AccessSprite("HomeSplashScreen"));

    //Play Button Initiliazation
    auto ButtonSprite = spriteHolder->AccessSprite("PlayButton");
    ButtonSprite.setOrigin(ButtonSprite.getGlobalBounds().getSize()/2.0f);
    ButtonSprite.setPosition(50.0_perW, 45.0_perH);
    UI::Element<MemSprite> PlayButton = BasicButtonBuilder(ButtonSprite, [conductor](){conductor->PushScreen("Home2");}, 10, 100ms, 5);

    //Settings Button Initiliazation
    auto SettingsSprite = spriteHolder->AccessSprite("SettingsButton");
    SettingsSprite.setOrigin(SettingsSprite.getGlobalBounds().getSize()/2.0f);
    SettingsSprite.setPosition(50.0_perW, 57.0_perH);
    UI::Element<MemSprite> SettingsButton = BasicButtonBuilder(SettingsSprite, [conductor](){conductor->PushScreen("Settings");}, 10, 100ms, 5);
    
    home->Elements.push_back(std::make_shared<UI::Element<MemSprite>>(Splash));
    home->Elements.push_back(std::make_shared<UI::Element<MemSprite>>(PlayButton));
    home->Elements.push_back(std::make_shared<UI::Element<MemSprite>>(SettingsButton));

    return home;
}
