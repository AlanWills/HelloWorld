#include "stdafx.h"

#include "HelloWorldGame.h"
#include "Screens/HelloWorldSplashScreen.h"


namespace HW
{
  //------------------------------------------------------------------------------------------------
  void HelloWorldGame::onInitialize()
  {
    Inherited::onInitialize();

    HelloWorldSplashScreen::create();
  }
}