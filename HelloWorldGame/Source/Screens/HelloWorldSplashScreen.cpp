#include "stdafx.h"

#include "Screens/HelloWorldSplashScreen.h"
#include "ObjectFX/LimitedLifeTime.h"
#include "Screens/HelloWorldMainMenuScreen.h"
#include "Input/SplashScreenLogoSkipper.h"
#include "Screens/Loading/ScreenLoader.h"
#include "Resources/ResourceManager.h"


namespace HW
{
  REGISTER_SCREEN_CREATOR(HelloWorldSplashScreen, "SplashScreen")

  //------------------------------------------------------------------------------------------------
  HelloWorldSplashScreen::HelloWorldSplashScreen(const Handle<Screen>& screen, const std::string& name) :
    Inherited(screen, name)
  {
  }

  //------------------------------------------------------------------------------------------------
  void HelloWorldSplashScreen::create()
  {
    const Handle<Screen>& screen = ScreenLoader::load(Path(getResourceManager()->getDataDirectoryPath(), "Screens", "SplashScreen2.xml"));
    HelloWorldSplashScreen splashScreen(screen);

    /*const Handle<GameObject>& firstLogo = screen->findGameObjectWithName("Logo0");
    splashScreen.createSplashImage(firstLogo, Path("Sprites", "UI", "CelesteGamesLogo.png"));
    firstLogo->addComponent<Input::SplashScreenLogoSkipper>();
    
    const Handle<GameObject>& secondLogo = screen->findGameObjectWithName("Logo1");
    splashScreen.createSplashImage(secondLogo, Path("Sprites", "UI", "CelesteEngineLogo.png"));
    secondLogo->addComponent<Input::SplashScreenLogoSkipper>();
    secondLogo->findComponent<LimitedLifeTime>()->subscribeOnDeathCallback([](const Handle<GameObject>&) -> void
    {
      HelloWorldMainMenuScreen::create();
    });*/
  }
}