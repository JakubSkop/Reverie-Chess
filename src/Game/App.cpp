#include "App.hpp"
#include "General/Constants.hpp"
#include "UI/Screens/ScreensImpl.hpp"
#include <chrono>
#include <iostream>

void Application::GameLoop(){

    auto previous = std::chrono::steady_clock::now();
    auto lag = 0ns;

    Resources resources = {Conductor.get(), SpriteHolder.get(), audio.get(), &Window, &globalTexture, &Events, &settings, &shader};
    sf::Event event;
    bool hasAtLeastOneUpdateCycleHappenedLastFrame;

    // run the program as long as the window is open
    while (Window.isOpen())
    {

        auto current = std::chrono::steady_clock::now();
        auto elapsed = current - previous;
        previous = current;
        lag = lag + elapsed;

        // check all the window's events that were triggered since the last iteration of the loop
        //processing inputs into the EventList
        if (hasAtLeastOneUpdateCycleHappenedLastFrame){
            Events.reset();
        }
        hasAtLeastOneUpdateCycleHappenedLastFrame = false;

        // check all the window's events that were triggered since the last iteration of the loop
        //processing inputs into the EventList
        while (Window.pollEvent(event))
        {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed){
                Window.close();
            }
                
            Events.addEvent(event);
           
        };

        while(lag >= Constants::MS_PER_UPDATE){

            Conductor->UpdateScreens(resources);
            //Update lag
            lag -= Constants::MS_PER_UPDATE;
            hasAtLeastOneUpdateCycleHappenedLastFrame = true;
        };

        Window.clear(); //Clear the window and globalTexture of its contents onscreen
        globalTexture.clear();

        Conductor->DrawScreens(resources); // Draw elements to globalTexture
        
        globalTexture.display(); //update globalTexture with its contents

        sf::Sprite wholeScreen(globalTexture.getTexture());
        Window.draw(wholeScreen,  &shader); //draw the globalTexture to the screen
        Window.display(); //display screen

    }
}

void Application::Setup(){
    //Initialize RenderTarget
    globalTexture.create(Constants::ScreenSize.x, Constants::ScreenSize.y);
    
    //Package Resources
    Resources resources{Conductor.get(), SpriteHolder.get(), audio.get(), &Window, &globalTexture,&Events, &settings, &shader};

    //Initialize Audio
    audio->AddMusic("Reverie Unfolds", "D:/Development/C++/SFML_GUI3/src/Assets/Music/Reverie.wav");

    //Load Shader
    shader.loadFromFile("D:/Development/C++/SFML_GUI3/src/Assets/Shaders/Palettizer.frag", sf::Shader::Type::Fragment);
    shader.setUniform("texture", sf::Shader::CurrentTexture);
    shader.setUniform("tintColor1", sf::Glsl::Vec4(settings.TintColor1));

    //Load Fonts    
    if (!fonts.PrimaryFont.loadFromFile("D:/Development/C++/SFML_GUI3/src/Assets/Fonts/stencil_pixel-7.ttf")){
        std::cout << "Bad font initialization";
    }

    //Load in textures
    SpriteHolder->AddFolderOfTextures("D:/Development/C++/SFML_GUI3/src/Assets/Textures");

    //Add various sprites
    SpriteHolder->AddSprite("HomeSplashScreen", "HomeSplash", {0,0,0,0}, 3.0f);
    SpriteHolder->AddSprite("PlayButton", "ButtonTileSheet", {0,0,60,30}, 3.0f);
    SpriteHolder->AddSprite("SettingsButton", "ButtonTileSheet", {{0,30},{109,30}}, 3.0f);
    SpriteHolder->AddSprite("CloseButton", "ButtonTileSheet", {{109,30},{11,11}}, 4.0f);
    SpriteHolder->AddSprite("ArrowButton", "ButtonTileSheet", {{109,41},{11,19}}, 4.0f);
    SpriteHolder->AddSprite("PointyArrowButton", "ButtonTileSheet", {{88,60},{16,14}}, 4.0f);
    SpriteHolder->AddSprite("LevelButton", "ButtonTileSheet", {{0,60},{88,30}}, 3.0f);
    SpriteHolder->AddSprite("TeamButton", "ButtonTileSheet", {{60,0}, {60,30}}, 3.0f);
    SpriteHolder->AddSprite("ExampleImage", "example", {0,0,0,0}, 3.0f);
    SpriteHolder->AddSprite("SliderBar", "ButtonTileSheet", {{0,90},{120,7}}, 4.0f);
    SpriteHolder->AddSprite("SliderHandle", "ButtonTileSheet", {{109,60},{11,11}}, 4.0f);
    SpriteHolder->AddSprite("LevelScreenBackground", "LevelScreen", {0,0,0,0}, 3.0f);
    SpriteHolder->AddSprite("Level1Button", "ButtonTileSheet", {{0,97},{30,30}}, 4.0f);
    SpriteHolder->AddSprite("Level2Button", "ButtonTileSheet", {{30,97},{30,30}}, 4.0f);
    SpriteHolder->AddSprite("Level3Button", "ButtonTileSheet", {{60,97},{30,30}}, 4.0f);
    SpriteHolder->AddSprite("Level4Button", "ButtonTileSheet", {{90,97},{30,30}}, 4.0f);

    SpriteHolder->AddSprite("WhitePawn", "PieceSpriteSheet", {{0,32},{32,64}}, 3.0f);

    std::shared_ptr<Screen> home = HomeScreen(resources);
    std::shared_ptr<Screen> home2 = HomeScreen2(resources);
    std::shared_ptr<Screen> settingsMenu = SettingsScreen(resources);
    std::shared_ptr<Screen> levels = LevelScreen(resources);

    Conductor->AddPotentialScreens({{"Home", home}, {"Home2", home2}, {"Settings", settingsMenu}, {"Levels", levels}});

    Conductor->PushScreen("Home");
}