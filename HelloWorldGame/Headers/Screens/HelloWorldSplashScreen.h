#pragma once

#include "Screens/SplashScreenCreator.h"


namespace HW
{

class HelloWorldSplashScreen : public CelesteEngine::SplashScreenCreator
{
  public:
    HelloWorldSplashScreen(const HelloWorldSplashScreen&) = delete;
    HelloWorldSplashScreen& operator=(const HelloWorldSplashScreen&) = delete;

    static void create();
    
  protected:
    HelloWorldSplashScreen(const Handle<Screen>& screen);

  private:
    typedef SplashScreenCreator Inherited;
};

}