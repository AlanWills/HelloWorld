#pragma once

#include "Screens/ScreenCreator.h"


namespace HW
{

class TerminalScreen : public CelesteEngine::ScreenCreator
{
  public:
    TerminalScreen(const Handle<Screen>& screen);

    static void create();

  private:
    typedef ScreenCreator Inherited;
};

}