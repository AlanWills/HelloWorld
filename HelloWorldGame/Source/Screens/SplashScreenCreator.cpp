#include "stdafx.h"

#include "Screens/SplashScreenCreator.h"
#include "Screens/ScreenManager.h"
#include "Resources/LoadResourcesAsyncScript.h"
#include "UI/Image.h"
#include "Screens/MainMenuScreen.h"
#include "GraphicalFX/OpacityLerper.h"
#include "ObjectFX/LimitedLifeTime.h"
#include "Events/EventTriggerer.h"


using namespace CelesteEngine;

namespace HW
{
  //------------------------------------------------------------------------------------------------
  SplashScreenCreator::SplashScreenCreator(const Handle<Screen>& screen) :
    Inherited(screen, "SplashScreen")
  {
  }

  //------------------------------------------------------------------------------------------------
  void SplashScreenCreator::create()
  {
    const Handle<Screen>& screen = Screen::allocate();

    SplashScreenCreator splashScreen(screen);

    // Attach the async resource loader to a game object
    const Handle<CelesteEngine::GameObject>& resourceLoader = screen->allocateGameObject(kWorld);

    // Add a background image
    const glm::vec2& screenDimensions = splashScreen.getViewportDimensions();

    {
      const Handle<GameObject>& firstImage = splashScreen.createGameObject(kGUI, screenDimensions * 0.5f, "FirstLogo");
      UI::Image::create(firstImage, Path("Sprites", "UI", "CelesteGamesLogo.png"), UI::Image::kPreserveAspectRatio, screenDimensions);
      //firstImage->findComponent<Renderer>()->setOpacity(0.001f);

      //const Handle<OpacityLerper>& opacityLerper = firstImage->addComponent<OpacityLerper>();
      //opacityLerper->setLerpingUp(true);
      //opacityLerper->setLerpPerSecond(1);

      const Handle<EventTriggerer>& triggerer = firstImage->addComponent<EventTriggerer>();
      triggerer->setTriggerMode(EventTriggerer::kOnce);
      triggerer->setCondition([](const Handle<GameObject>& gameObject) -> bool { return gameObject->findComponent<LimitedLifeTime>()->getCurrentTimeAlive() >= 1.9f; });
      triggerer->getEvent().subscribe([](const Handle<GameObject>& gameObject) -> void 
      { 
        const Handle<GameObject>& secondLogo = gameObject->getOwnerScreen()->findGameObjectWithName("SecondLogo");
        secondLogo->setShouldUpdate(true);
        secondLogo->setShouldRender(true);
      });

      const Handle<LimitedLifeTime>& lifeTime = createLimitedLifeTime(firstImage, 2);
    }

    {
      const Handle<GameObject>& secondImage = splashScreen.createGameObject(kGUI, screenDimensions * 0.5f, "SecondLogo");
      UI::Image::create(secondImage, Path("Sprites", "UI", "CelesteEngineLogo.png"), UI::Image::kPreserveAspectRatio, screenDimensions);
      secondImage->getTransform()->setTranslation(screenDimensions * 0.5f);
      /*secondImage->findComponent<Renderer>()->setOpacity(0);

      const Handle<OpacityLerper>& opacityLerper = secondImage->addComponent<OpacityLerper>();
      opacityLerper->setLerpingUp(true);
      opacityLerper->setLerpPerSecond(1);*/

      const Handle<EventTriggerer>& triggerer = secondImage->addComponent<EventTriggerer>();
      triggerer->setTriggerMode(EventTriggerer::kOnce);
      triggerer->setCondition([](const Handle<GameObject>& gameObject) -> bool { return gameObject->findComponent<LimitedLifeTime>()->getCurrentTimeAlive() == 2; });
      triggerer->getEvent().subscribe([](const Handle<GameObject>& gameObject) -> void 
      { 
        gameObject->getOwnerScreen()->die();
        createMainMenuScreen(); 
      });

      const Handle<LimitedLifeTime>& lifeTime = createLimitedLifeTime(secondImage, 2);

      secondImage->setShouldUpdate(false);
      secondImage->setShouldRender(false);
    }

    // Add resource loading whilst we display the splash screen
    //const Handle<LoadResourcesAsyncScript>& loadResourcesScript = resourceLoader->addComponent<LoadResourcesAsyncScript>();
    //loadResourcesScript->setWaitTime(1);
    //loadResourcesScript->getLoadCompleteEvent().subscribe(&createMainMenuScreen);
  }
}