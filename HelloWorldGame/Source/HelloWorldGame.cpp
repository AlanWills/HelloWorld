#include "stdafx.h"

#include "HelloWorldGame.h"
#include "Screens/SplashScreenCreator.h"


namespace HW
{
  //------------------------------------------------------------------------------------------------
  void HelloWorldGame::onInitialize()
  {
    Inherited::onInitialize();

    SplashScreenCreator::create();
  }
}