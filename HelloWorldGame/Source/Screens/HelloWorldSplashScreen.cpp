#include "stdafx.h"

#include "Screens/HelloWorldSplashScreen.h"
#include "ObjectFX/LimitedLifeTime.h"
#include "Screens/MainMenuScreen.h"


namespace HW
{
  //------------------------------------------------------------------------------------------------
  HelloWorldSplashScreen::HelloWorldSplashScreen(const Handle<Screen>& screen) :
    Inherited(screen)
  {
  }

  //------------------------------------------------------------------------------------------------
  void HelloWorldSplashScreen::create()
  {
    const Handle<Screen>& screen = Screen::allocate();

    HelloWorldSplashScreen splashScreen(screen);
    splashScreen.createSplashImage(Path("Sprites", "UI", "CelesteGamesLogo.png"));
    const Handle<GameObject>& gameObject = splashScreen.createSplashImage(Path("Sprites", "UI", "CelesteEngineLogo.png"));
    gameObject->findComponent<LimitedLifeTime>()->subscribeOnDeathCallback([](const Handle<GameObject>&) -> void
    {
      createMainMenuScreen();
    });
  }
}