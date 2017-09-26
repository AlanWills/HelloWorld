#pragma once

#include "Screens/LevelScreenCreator.h"


namespace HW
{
  
class Level1 : public LevelScreenCreator
{
  public:
    Level1(const Level1&) = delete;
    Level1 operator=(const Level1&) = delete;

    static void create();

  protected:
    Level1(const Handle<Screen>& screen);

  private:
    typedef LevelScreenCreator Inherited;
};

}