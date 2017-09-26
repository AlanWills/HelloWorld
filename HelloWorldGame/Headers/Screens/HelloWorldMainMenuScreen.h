#pragma once

#include "Screens/ScreenCreator.h"


namespace HW
{
  
class HelloWorldMainMenuScreen : public CelesteEngine::ScreenCreator
{
  public:
    HelloWorldMainMenuScreen(const HelloWorldMainMenuScreen&) = delete;
    HelloWorldMainMenuScreen& operator=(const HelloWorldMainMenuScreen&) = delete;

    static void create();

  protected:
    HelloWorldMainMenuScreen(const Handle<Screen>& screen);

  private:
    typedef ScreenCreator Inherited;
};

}