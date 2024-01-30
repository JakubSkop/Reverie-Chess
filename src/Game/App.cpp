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
    audio->AddMusic("Reverie Unfolds", "./src/Assets/Music/Reverie.wav");

    //Load Shader
    shader.loadFromFile("./src/Assets/Shaders/Palettizer.frag", sf::Shader::Type::Fragment);
    shader.setUniform("texture", sf::Shader::CurrentTexture);
    shader.setUniform("tintColor1", sf::Glsl::Vec4(settings.TintColor1));

    //Load Fonts    
    if (!fonts.PrimaryFont.loadFromFile("./src/Assets/Fonts/stencil_pixel-7.ttf")){
        std::cout << "Bad font initialization";
    }

    //Load in textures
    SpriteHolder->AddFolderOfTextures("./src/Assets/Textures");

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
    SpriteHolder->AddSprite("GameBackground", "BattleField", {0,0,0,0}, 3.0f);
    SpriteHolder->AddSprite("Level1Button", "ButtonTileSheet", {{0,97},{30,30}}, 4.0f);
    SpriteHolder->AddSprite("Level2Button", "ButtonTileSheet", {{30,97},{30,30}}, 4.0f);
    SpriteHolder->AddSprite("Level3Button", "ButtonTileSheet", {{60,97},{30,30}}, 4.0f);
    SpriteHolder->AddSprite("Level4Button", "ButtonTileSheet", {{90,97},{30,30}}, 4.0f);

    SpriteHolder->AddSprite("RegularTile1", "PieceSpriteSheet", {{0,0},{32,32}}, 1.5f);
    SpriteHolder->AddSprite("RegularTile2", "PieceSpriteSheet", {{32,0},{32,32}}, 1.5f);
    SpriteHolder->AddSprite("InactiveTile1", "PieceSpriteSheet", {{64,0},{32,32}}, 1.5f);
    SpriteHolder->AddSprite("InactiveTile2", "PieceSpriteSheet", {{96,0},{32,32}}, 1.5f);
    SpriteHolder->AddSprite("WhitePromotionOverlay", "PieceSpriteSheet", {{128,0},{32,32}}, 1.5f);
    SpriteHolder->AddSprite("BlackPromotionOverlay", "PieceSpriteSheet", {{160,0},{32,32}}, 1.5f);
    SpriteHolder->AddSprite("CurrentTileOverlay", "PieceSpriteSheet", {{192,0},{32,32}}, 1.5f);
    SpriteHolder->AddSprite("MixedPromotionOverlay", "PieceSpriteSheet", {{224,0},{32,32}}, 1.5f);
    SpriteHolder->AddSprite("Null", "PieceSpriteSheet", {{256,0},{32,32}}, 1.5f);
    SpriteHolder->AddSprite("MoveOverlay", "PieceSpriteSheet", {{288,0},{32,32}}, 1.5f);

    SpriteHolder->AddSprite("White_Basic_Pawn", "PieceSpriteSheet", {{0,32},{32,32}}, 1.5f);
    SpriteHolder->AddSprite("Black_Basic_Pawn", "PieceSpriteSheet", {{0,64},{32,32}}, 1.5f);

    SpriteHolder->AddSprite("White_Basic_Bishop", "PieceSpriteSheet", {{0,160},{32,32}}, 1.5f);
    SpriteHolder->AddSprite("Black_Basic_Bishop", "PieceSpriteSheet", {{0,192},{32,32}}, 1.5f);

    std::shared_ptr<Screen> home = HomeScreen(resources);
    std::shared_ptr<Screen> home2 = HomeScreen2(resources);
    std::shared_ptr<Screen> settingsMenu = SettingsScreen(resources);
    std::shared_ptr<Screen> levels = LevelScreen(resources);
    std::shared_ptr<Screen> level1 = TeamSelectScreen(resources, 1);
    std::shared_ptr<Screen> level2 = TeamSelectScreen(resources, 2);
    std::shared_ptr<Screen> level3 = TeamSelectScreen(resources, 3);
    std::shared_ptr<Screen> level4 = TeamSelectScreen(resources, 4);

    Conductor->AddPotentialScreens({{"Home", home}, {"Home2", home2}, {"Settings", settingsMenu}, {"Levels", levels}, {"Level1", level1}, {"Level2", level2}, {"Level3", level3}, {"Level4", level4}});

    Conductor->PushScreen("Home");
}