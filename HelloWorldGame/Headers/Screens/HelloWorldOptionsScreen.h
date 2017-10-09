#pragma once

#include "Screens/OptionsScreenCreator.h"


namespace HW
{

class HelloWorldOptionsScreen : public CelesteEngine::OptionsScreenCreator
{
  DECLARE_SCREEN_CREATOR(HelloWorldOptionsScreen)

  public:
    static void create();

  private:
    typedef OptionsScreenCreator Inherited;
};

}