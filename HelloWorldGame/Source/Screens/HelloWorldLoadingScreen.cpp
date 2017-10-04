#include "stdafx.h"

#include "Screens/HelloWorldLoadingScreen.h"


namespace HW
{
  REGISTER_SCREEN_CREATOR(HelloWorldLoadingScreen, "LoadingScreen")

  //------------------------------------------------------------------------------------------------
  HelloWorldLoadingScreen::HelloWorldLoadingScreen(const Handle<Screen>& screen, const std::string& name) :
    Inherited(screen, name)
  {
  }
}