#pragma once

#include "Screens/LevelScreenCreator.h"


namespace HW
{

  class Level3 : public LevelScreenCreator
  {
    DECLARE_SCREEN_CREATOR(Level3)

  public:
    static void create();

  private:
    typedef LevelScreenCreator Inherited;
  };

}