#include "ScreensImpl.hpp"
#include "UI/CustomElement/Slider/SliderElement.hpp"

void Cycle(sf::Color& col){
    col.r = (col.r * 57) % 256;
    col.g = (col.g * 81) % 256;
    col.b = (col.b * 101) % 256;
}

void UnCycle(sf::Color& col){
    col.r = (col.r * 9) % 256;
    col.g = (col.g * 177) % 256;
    col.b = (col.b * 109) % 256;
}

std::shared_ptr<Screen> SettingsScreen(Resources resources){
    auto spriteHolder = resources.spriteManager;
    auto conductor = resources.screenConductor;
    auto settings = resources.settings;
    auto shader = resources.shader;
    auto audio = resources.soundPlayer;

    auto settingsScreen = std::make_shared<Screen>();
    settingsScreen->DrawUnder = true;
    settingsScreen->UpdateUnder = false;

    //Darkens out the background
    auto Background = StaticImage(SolidColour(Constants::Palette::Blue * Color(255,255,255,200)));

    //Box for settings to be shown in
    auto menuBox = SolidColour(Constants::Palette::Navy,{32.0_perW, 70.0_perH});
    CenterOrigin(menuBox);
    menuBox.setPosition(50.0_perW, 50.0_perH);
    menuBox.setOutlineColor(Constants::Palette::Grey);
    menuBox.setOutlineThickness(5.0f);
    auto Menu = StaticImage(menuBox);

    //Button for exiting Settings
    auto closeButtonSprite = spriteHolder->AccessSprite("CloseButton");
    CenterOrigin(closeButtonSprite);
    closeButtonSprite.setPosition(66.0_perW - 30, 15.0_perH + 30);
    UI::Element<MemSprite> closeButton = BasicButtonBuilder(closeButtonSprite, [conductor](){conductor->PopScreen();}, 10, 100ms, 20);

    //Buttons for Palette Switching
    auto ArrowButtonSprite = spriteHolder->AccessSprite("ArrowButton");
    CenterOrigin(ArrowButtonSprite );
    ArrowButtonSprite.setPosition(62.0_perW , 40.0_perH);
    UI::Element<MemSprite> arrowButton = BasicButtonBuilder(ArrowButtonSprite , [settings, shader](){Cycle(settings->TintColor1); shader->setUniform("tintColor1", sf::Glsl::Vec4(settings->TintColor1));}, 10, 100ms, 20);

    auto ArrowButtonSprite2 = spriteHolder->AccessSprite("ArrowButton");
    CenterOrigin(ArrowButtonSprite2);
    ArrowButtonSprite2.rotate(180.0f);
    ArrowButtonSprite2.setPosition(38.0_perW , 40.0_perH);
    UI::Element<MemSprite> arrowButton2 = BasicButtonBuilder(ArrowButtonSprite2 , [settings, shader](){UnCycle(settings->TintColor1); shader->setUniform("tintColor1", sf::Glsl::Vec4(settings->TintColor1));}, 10, 100ms, 20);
    
    //Example photo Initialization
    auto ExampleSprite = spriteHolder->AccessSprite("ExampleImage");
    CenterOrigin(ExampleSprite);
    ExampleSprite.setPosition(50.0_perW, 40.0_perH);
    auto example = StaticImage(ExampleSprite);

    //Text Initialization
    auto Text_Palette = sf::Text("Palette", resources.settings->fonts->PrimaryFont, 30);
    CenterOrigin(Text_Palette);
    Text_Palette.setPosition(50.0_perW, 27.0_perH);
    auto text_palette = StaticImage(Text_Palette);

    auto Text_Title = sf::Text("Settings", resources.settings->fonts->PrimaryFont, 50);
    CenterOrigin(Text_Title);
    Text_Title.setPosition(50.0_perW, 21.0_perH);
    auto text_title = StaticImage(Text_Title);

    auto Text_Sound = sf::Text("Sound", resources.settings->fonts->PrimaryFont, 30);
    CenterOrigin(Text_Sound);
    Text_Sound.setPosition(50.0_perW, 53.0_perH);
    auto text_sound = StaticImage(Text_Sound);

    auto Text_Volume = sf::Text("Volume", resources.settings->fonts->PrimaryFont, 20);
    CenterOrigin(Text_Volume);
    Text_Volume.setPosition(50.0_perW, 58.0_perH);
    auto text_volume = StaticImage(Text_Volume);

    //Slider for Volume
    auto sliderSprites = IntSlider();
    sliderSprites.bar = spriteHolder->AccessSprite("SliderBar");
    CenterOrigin(sliderSprites.bar);
    sliderSprites.bar.setPosition(50.0_perW, 62.0_perH);
    sliderSprites.handle = spriteHolder->AccessSprite("SliderHandle");
    auto slider = BasicSliderBuilder(sliderSprites, 0, 100, [audio](int volume){audio->SetVolume(volume);});

    settingsScreen->Elements.push_back(std::make_shared<UI::Element<sf::RectangleShape>>(Background));
    settingsScreen->Elements.push_back(std::make_shared<UI::Element<sf::RectangleShape>>(Menu));
    settingsScreen->Elements.push_back(std::make_shared<UI::Element<MemSprite>>(closeButton));
    settingsScreen->Elements.push_back(std::make_shared<UI::Element<MemSprite>>(example));
    settingsScreen->Elements.push_back(std::make_shared<UI::Element<MemSprite>>(arrowButton));
    settingsScreen->Elements.push_back(std::make_shared<UI::Element<MemSprite>>(arrowButton2));
    settingsScreen->Elements.push_back(std::make_shared<UI::Element<Text>>(text_palette));
    settingsScreen->Elements.push_back(std::make_shared<UI::Element<Text>>(text_title));
    settingsScreen->Elements.push_back(std::make_shared<UI::Element<Text>>(text_sound));
    settingsScreen->Elements.push_back(std::make_shared<UI::Element<Text>>(text_volume));
    settingsScreen->Elements.push_back(std::make_shared<UI::Element<IntSlider>>(slider));

    return settingsScreen;
}
