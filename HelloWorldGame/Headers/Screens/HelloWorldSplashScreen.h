#pragma once

#include "Screens/SplashScreenCreator.h"


namespace HW
{

class HelloWorldSplashScreen : public CelesteEngine::SplashScreenCreator
{
  public:
    HelloWorldSplashScreen(const Handle<Screen>& screen);

    static void create();

  private:
    typedef SplashScreenCreator Inherited;
};

}