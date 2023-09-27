#include "ScreensImpl.hpp"
#include "UI/CustomElement/ScrollablePage/ScrollingPageElement.hpp"

std::shared_ptr<Screen> LevelScreen(Resources resources){
    auto spriteHolder = resources.spriteManager;
    auto conductor = resources.screenConductor;
    auto audio = resources.soundPlayer;

    auto home = std::make_shared<Screen>();
    home->DrawUnder = false;
    home->UpdateUnder = false;
    home->PushCallback = [audio](){if(audio->GetCurrentMusic() != "Reverie Unfolds"){audio->PlayMusic("Reverie Unfolds");};};

    //builder for scrolling page
    auto builder = ScrollingPageBuilder(spriteHolder->AccessSprite("LevelScreenBackground"));

    //Back Button
    auto backButtonSprite = spriteHolder->AccessSprite("PointyArrowButton");
    backButtonSprite.setPosition(20,20);
    UI::Element<MemSprite> backButton = BasicButtonBuilder(backButtonSprite, [conductor](){conductor->PopScreen();}, 10, 100ms, 20);

    //Level Button 1
    auto level1Sprite = spriteHolder->AccessSprite("Level1Button");
    CenterOrigin(level1Sprite);
    level1Sprite.setPosition(35.0_perW, 55.0_perH);
    UI::Element<MemSprite> level1 = BasicButtonBuilder(level1Sprite, [conductor](){conductor->PopScreen();}, 10, 100ms, 20);

    //Level Button 2
    auto level2Sprite = spriteHolder->AccessSprite("Level2Button");
    CenterOrigin(level2Sprite);
    level2Sprite.setPosition(71.0_perW, 26.0_perH);
    UI::Element<MemSprite> level2 = BasicButtonBuilder(level2Sprite, [conductor](){conductor->PopScreen();}, 10, 100ms, 20);

    //Level Button 3
    auto level3Sprite = spriteHolder->AccessSprite("Level3Button");
    CenterOrigin(level3Sprite);
    level3Sprite.setPosition(50.0_perW, -30.0_perH);
    UI::Element<MemSprite> level3 = BasicButtonBuilder(level3Sprite, [conductor](){conductor->PopScreen();}, 10, 100ms, 20);

    //Level Button 4
    auto level4Sprite = spriteHolder->AccessSprite("Level4Button");
    CenterOrigin(level4Sprite);
    level4Sprite.setPosition(20.0_perW, -70.0_perH);
    UI::Element<MemSprite> level4 = BasicButtonBuilder(level4Sprite, [conductor](){conductor->PopScreen();}, 10, 100ms, 20);




    builder.addSubElement(level1);
    builder.addSubElement(level2);
    builder.addSubElement(level3);
    builder.addSubElement(level4);

    home->Elements.push_back(std::make_shared<UI::Element<ScrollingPageComponent>>(builder.getObject()));
    home->Elements.push_back(std::make_shared<UI::Element<MemSprite>>(backButton));

    return home;
}