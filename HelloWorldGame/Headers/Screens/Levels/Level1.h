#pragma once

#include "Screens/LevelScreen.h"


namespace HW
{
  
class Level1 : public LevelScreen
{
  public:
    Level1(const Handle<Screen>& screen);

    static void create();

  private:
    typedef LevelScreen Inherited;
};

}