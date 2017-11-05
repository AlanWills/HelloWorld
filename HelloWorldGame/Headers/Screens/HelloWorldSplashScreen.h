#pragma once

#include "Screens/Creation/SplashScreenCreator.h"


namespace HW
{

class HelloWorldSplashScreen : public CelesteEngine::SplashScreenCreator
{
  DECLARE_SCREEN_CREATOR(HelloWorldSplashScreen)

  public:
    static void create();
    
  private:
    typedef SplashScreenCreator Inherited;
};

}