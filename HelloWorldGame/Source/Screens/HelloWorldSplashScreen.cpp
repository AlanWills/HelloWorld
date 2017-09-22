#include "stdafx.h"

#include "Screens/HelloWorldSplashScreen.h"
#include "ObjectFX/LimitedLifeTime.h"
#include "Screens/HelloWorldMainMenuScreen.h"
#include "Input/SplashScreenLogoSkipper.h"


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
    const Handle<GameObject>& firstLogo = splashScreen.createSplashImage(Path("Sprites", "UI", "CelesteGamesLogo.png"));
    firstLogo->addComponent<Input::SplashScreenLogoSkipper>();
    
    const Handle<GameObject>& secondLogo = splashScreen.createSplashImage(Path("Sprites", "UI", "CelesteEngineLogo.png"));
    secondLogo->addComponent<Input::SplashScreenLogoSkipper>();
    secondLogo->findComponent<LimitedLifeTime>()->subscribeOnDeathCallback([](const Handle<GameObject>&) -> void
    {
      HelloWorldMainMenuScreen::create();
    });
  }
}