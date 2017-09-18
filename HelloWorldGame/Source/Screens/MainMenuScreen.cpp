#include "stdafx.h"

#include "Screens/MainMenuScreen.h"
#include "Screens/ScreenManager.h"
#include "UI/Button.h"
#include "UI/StackPanel.h"
#include "Game/Game.h"
#include "Screens/Levels/Level1.h"
#include "Screens/TerminalScreen.h"


using namespace CelesteEngine;

namespace HW
{
  //------------------------------------------------------------------------------------------------
  void createMainMenuScreen()
  {
    const Handle<Screen>& screen = Screen::allocate();

    const Handle<GameObject>& playGameButton = screen->allocateGameObject(kGUI);
    UI::Button::create(playGameButton, "Play", 
      [](const Handle<GameObject>& caller) -> void
      {
        caller->getOwnerScreen()->die();
        Level1::create();
        TerminalScreen::create();
        deactivateScreen("Terminal");
      }
    );

    const Handle<GameObject>& exitGameButton = screen->allocateGameObject(kGUI);
    UI::Button::create(exitGameButton, "Exit", std::bind(&Game::exitCallback, std::placeholders::_1));

    const Handle<GameObject>& buttonStackPanel = screen->allocateGameObject(kGUI);
    buttonStackPanel->getTransform()->setTranslation(getViewportDimensions() * 0.5f);
    UI::StackPanel::create(buttonStackPanel, Vertical::kCentre, playGameButton, exitGameButton);
  }
}