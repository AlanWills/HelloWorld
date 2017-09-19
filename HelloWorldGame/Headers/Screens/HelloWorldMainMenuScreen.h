#pragma once

#include "Screens/ScreenCreator.h"


namespace HW
{
  
class HelloWorldMainMenuScreen : public CelesteEngine::ScreenCreator
{
  public:
    HelloWorldMainMenuScreen(const Handle<Screen>& screen);

    static void create();

  private:
    typedef ScreenCreator Inherited;
};

}