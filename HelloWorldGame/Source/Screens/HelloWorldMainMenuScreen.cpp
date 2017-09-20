#include "stdafx.h"

#include "Screens/HelloWorldMainMenuScreen.h"
#include "Screens/ScreenManager.h"
#include "UI/Button.h"
#include "UI/StackPanel.h"
#include "Game/Game.h"
#include "Screens/Levels/Level1.h"
#include "Screens/TerminalScreen.h"
#include "UI/MainMenuTitleEffect.h"
#include "UI/TextBox.h"


using namespace CelesteEngine;

namespace HW
{
  //------------------------------------------------------------------------------------------------
  HelloWorldMainMenuScreen::HelloWorldMainMenuScreen(const Handle<Screen>& screen) :
    Inherited(screen, "MainMenu")
  {
  }

  //------------------------------------------------------------------------------------------------
  void HelloWorldMainMenuScreen::create()
  {
    HelloWorldMainMenuScreen mainMenu(Screen::allocate());

    const glm::vec2& viewportDimensions = mainMenu.getViewportDimensions();
    const Handle<GameObject>& title = mainMenu.createGameObject(kGUI, glm::vec2(viewportDimensions.x * 0.5f, viewportDimensions.y * 0.8f), "Title");
    UI::TextBox::create(title, "", 32);
    title->addComponent<MainMenuTitleEffect>();

    const Handle<GameObject>& playGameButton = mainMenu.createGameObject(kGUI, glm::vec2(), "PlayButton");
    UI::Button::create(playGameButton, "Play", 
      [](const Handle<GameObject>& caller) -> void
      {
        caller->getOwnerScreen()->die();
        Level1::create();
        TerminalScreen::create();
        deactivateScreen("Terminal");
      }
    );

    const Handle<GameObject>& exitGameButton = mainMenu.createGameObject(kGUI, glm::vec2(), "ExitButton");
    UI::Button::create(exitGameButton, "Exit", [](const Handle<GameObject>&) -> void { Game::current()->exit(); });

    const Handle<GameObject>& buttonStackPanel = mainMenu.createGameObject(kGUI, viewportDimensions * 0.5f, "ButtonStackPanel");
    UI::StackPanel::create(buttonStackPanel, Vertical::kCentre, playGameButton, exitGameButton);
  }
}