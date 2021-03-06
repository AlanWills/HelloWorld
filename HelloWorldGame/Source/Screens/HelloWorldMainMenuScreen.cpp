 #include "stdafx.h"

#include "Screens/HelloWorldMainMenuScreen.h"
#include "Screens/HelloWorldLoadingScreen.h"
#include "Screens/HelloWorldOptionsScreen.h"
#include "Screens/ScreenManager.h"
#include "UI/Button.h"
#include "UI/StackPanel.h"
#include "Game/Game.h"
#include "Screens/Levels/Level1.h"
#include "GraphicalFX/TypingTextEffect.h"
#include "UI/TextBox.h"


using namespace CelesteEngine;

namespace HW
{
  REGISTER_SCREEN_CREATOR(HelloWorldMainMenuScreen, "MainMenu")

  //------------------------------------------------------------------------------------------------
  HelloWorldMainMenuScreen::HelloWorldMainMenuScreen(const Handle<Screen>& screen, const std::string& name) :
    Inherited(screen, name)
  {
  }

  //------------------------------------------------------------------------------------------------
  void HelloWorldMainMenuScreen::create()
  {
    HelloWorldMainMenuScreen mainMenu(Screen::allocate());
    const glm::vec2& viewportDimensions = mainMenu.getViewportDimensions();

    const Handle<GameObject>& title = mainMenu.createGameObject(kGUI, glm::vec2(viewportDimensions.x * 0.5f, viewportDimensions.y * 0.8f), "Title");
    UI::TextBox::create(title, "", 32, Horizontal::kCentre);
    TypingTextEffect::create(title, "Hello World", 0.3f, 0.2f);

    const Handle<GameObject>& playGameButton = mainMenu.createGameObject(kGUI, glm::vec2(), "PlayButton");
    const Handle<Button>& playButton = UI::Button::create(playGameButton, "run()", 
      [](EventArgs& e, const Handle<GameObject>& caller) -> void
      {
        caller->getOwnerScreen()->die();
        getScreenManager()->findScreen("Persistent")->die();
        HelloWorldLoadingScreen::create<Level1>();
      }
    );
    playButton->getLabel()->findComponent<TextRenderer>()->setFontHeight(24);

    const Handle<GameObject>& optionsMenuButton = mainMenu.createGameObject(kGUI, glm::vec2(), "OptionsButton");
    const Handle<Button>& optionsButton = UI::Button::create(optionsMenuButton, "options()",
      [](EventArgs& e, const Handle<GameObject>& caller) -> void
      {
        caller->getOwnerScreen()->die();
        HelloWorldOptionsScreen::create();
      }
    );
    optionsButton->getLabel()->findComponent<TextRenderer>()->setFontHeight(24);

    const Handle<GameObject>& exitGameButton = mainMenu.createGameObject(kGUI, glm::vec2(), "ExitButton");
    const Handle<Button>& exitButton = UI::Button::create(exitGameButton, "quit()", [](EventArgs& e, const Handle<GameObject>&) -> void { Game::current()->exit(); });
    exitButton->getLabel()->findComponent<TextRenderer>()->setFontHeight(24);

    const Handle<GameObject>& buttonStackPanel = mainMenu.createGameObject(kGUI, viewportDimensions * 0.5f, "ButtonStackPanel");
    const Handle<StackPanel>& stackPanel = UI::StackPanel::create(buttonStackPanel, Vertical::kCentre, 20, playGameButton, optionsMenuButton, exitGameButton);
  }
}