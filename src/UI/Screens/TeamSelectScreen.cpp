#include "ScreensImpl.hpp"
#include "UI/CustomElement/Gameboard/BoardElement.hpp"
#include "Chess/Board/Board.hpp"

std::shared_ptr<Screen> TeamSelectScreen(Resources resources, unsigned int levelNum){
    auto spriteHolder = resources.spriteManager;
    auto conductor = resources.screenConductor;
    auto audio = resources.soundPlayer;

    auto home = std::make_shared<Screen>();
    home->DrawUnder = false;
    home->UpdateUnder = false;
    home->PushCallback = [audio](){if(audio->GetCurrentMusic() != "Reverie Unfolds"){audio->PlayMusic("Reverie Unfolds");};};

    UI::Element<MemSprite> Splash = StaticImage(spriteHolder->AccessSprite("GameBackground"));

    //Back Button
    auto backButtonSprite = spriteHolder->AccessSprite("PointyArrowButton");
    backButtonSprite.setPosition(20,20);
    UI::Element<MemSprite> backButton = BasicButtonBuilder(backButtonSprite, [conductor](){conductor->PopScreen();}, 10, 100ms, 20);

    //Level Title
    auto Text_Level = sf::Text("Level " + std::to_string(levelNum), resources.settings->fonts->PrimaryFont, 50);
    CenterOrigin(Text_Level);
    Text_Level.setPosition(82.0_perW, 6.5_perH);
    auto text_level = StaticImage(Text_Level);

    //Board
    ChessBoard board = Board_for_Level_N(levelNum);
    UI::Element<BoardComponent> chess = GameBoardBuilder(board, {159,159}, resources, 0).getObject();

    
    home->Elements.push_back(std::make_shared<UI::Element<MemSprite>>(Splash));
    home->Elements.push_back(std::make_shared<UI::Element<MemSprite>>(backButton));
    home->Elements.push_back(std::make_shared<UI::Element<Text>>(text_level));
    home->Elements.push_back(std::make_shared<UI::Element<BoardComponent>>(chess));

    return home;
}