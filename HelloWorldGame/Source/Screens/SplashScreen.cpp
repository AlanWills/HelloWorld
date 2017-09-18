#include "stdafx.h"

#include "Screens/SplashScreen.h"
#include "Screens/ScreenManager.h"
#include "Resources/LoadResourcesAsyncScript.h"
#include "UI/Image.h"
#include "Screens/MainMenuScreen.h"


using namespace CelesteEngine;

namespace HW
{
  //------------------------------------------------------------------------------------------------
  void createSplashScreen()
  {
    const Handle<Screen>& screen = Screen::allocate();

    // Attach the async resource loader to a game object
    const Handle<CelesteEngine::GameObject>& resourceLoader = screen->allocateGameObject(kWorld);

    // Add a background image
    const glm::vec2& screenDimensions = getViewportDimensions();

    const Handle<GameObject>& image = screen->allocateGameObject(kGUI);
    UI::Image::create(image, Path("Sprites", "UI", "Logo.png"), UI::Image::kPreserveAspectRatio, screenDimensions);
    image->getTransform()->setTranslation(screenDimensions * 0.5f);

    // Add resource loading whilst we display the splash screen
    const Handle<LoadResourcesAsyncScript>& loadResourcesScript = resourceLoader->addComponent<LoadResourcesAsyncScript>();
    loadResourcesScript->setWaitTime(1);
    loadResourcesScript->getLoadCompleteEvent().subscribe(&createMainMenuScreen);
  }
}