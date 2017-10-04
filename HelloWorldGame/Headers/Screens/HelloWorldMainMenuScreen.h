#pragma once

#include "Screens/ScreenCreator.h"


namespace HW
{
  
class HelloWorldMainMenuScreen : public CelesteEngine::ScreenCreator
{
  DECLARE_SCREEN_CREATOR(HelloWorldMainMenuScreen)

  public:
    static void create();

  private:
    typedef ScreenCreator Inherited;
};

}