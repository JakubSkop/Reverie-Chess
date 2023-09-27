#include "ScrollingPageElement.hpp"

ScrollingPageBuilder::ScrollingPageBuilder(MemSprite PageImage){
    PageImage.setPosition({0,Constants::ScreenSize.y - PageImage.getGlobalBounds().height});
    ScrollingPage.DrawableComponent.page = PageImage;

    StatePtr state = std::make_shared<State<Element<ScrollingPageComponent>>>();

    class ScrollingUpdateFunctor{
        public:
            PotentialStatePtr operator()(Element<ScrollingPageComponent>* button , Resources appResources){
                auto delta = appResources.eventList->MouseWheels.at("Vertical").delta;
                auto rect = button->DrawableComponent.page.getGlobalBounds();

                overallWheelDelta += 8*delta;

                if (timeElapsed >= 40ms){
                    overallWheelDelta *= 0.95f;
                    timeElapsed -= 40ms;
                }

                if (rect.top + overallWheelDelta > 0 || rect.top + overallWheelDelta < Constants::ScreenSize.y - rect.height ){
                    overallWheelDelta=0;
                }

                //code for moving the page and all corresponding subelements by the right offset to create scrolling illusion
                auto scrollVector = Vector2f{0.0f, overallWheelDelta * static_cast<float>(Constants::MS_PER_UPDATE.count()/40.0)};
                button->DrawableComponent.page.move(scrollVector);
                for (auto i : button->DrawableComponent.SubElements.SubElements){
                    i->DrawableComponent.move(scrollVector);
                }

                //Delegate other updates of sublements
                button->DrawableComponent.SubElements.Update(appResources);

                timeElapsed += Constants::MS_PER_UPDATE;
                return std::nullopt;
            };

        private:
            float overallWheelDelta = 0;
            std::chrono::milliseconds timeElapsed = 0ms;
    };
    
    state->UpdateCallback = ScrollingUpdateFunctor();
    state->EnterCallback = [](Element<ScrollingPageComponent>* button){};
    state->ExitCallback = [](Element<ScrollingPageComponent>* button){};
    state->DrawCallback = [](Element<ScrollingPageComponent>* element, Resources appResources){appResources.globalTexture->draw(element->DrawableComponent.page); 
        element->DrawableComponent.SubElements.Draw(appResources);
    };

    ScrollingPage.StateStack = {};
    ScrollingPage.StateStack.push(state);

}



Element<ScrollingPageComponent> ScrollingPageBuilder::getObject(){
    return ScrollingPage;
}


void ScrollingPageBuilder::addSubElement(Element<MemSprite> element){
    ScrollingPage.DrawableComponent.SubElements.SubElements.push_back(std::make_shared<Element<MemSprite>>(element));
}