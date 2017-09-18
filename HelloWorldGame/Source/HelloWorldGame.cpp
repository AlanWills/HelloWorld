#include "stdafx.h"

#include "HelloWorldGame.h"
#include "Screens/SplashScreen.h"


namespace HW
{
  //------------------------------------------------------------------------------------------------
  void HelloWorldGame::onInitialize()
  {
    Inherited::onInitialize();

    createSplashScreen();
  }
}