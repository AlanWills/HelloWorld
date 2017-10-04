#pragma once

#include "Screens/LevelScreenCreator.h"


namespace HW
{
  
class Level1 : public LevelScreenCreator
{
  DECLARE_SCREEN_CREATOR(Level1)

  public:
    static void create();

  private:
    typedef LevelScreenCreator Inherited;
};

}