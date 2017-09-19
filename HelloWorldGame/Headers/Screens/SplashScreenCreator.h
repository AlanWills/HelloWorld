#pragma once

#include "Screens/ScreenCreator.h"


namespace HW
{

class SplashScreenCreator : CelesteEngine::ScreenCreator
{
  public:
    SplashScreenCreator(const Handle<Screen>& screen);

    static void create();

  private:
    typedef CelesteEngine::ScreenCreator Inherited;
};

}