#pragma once

#include "Screens/LevelScreenCreator.h"


namespace HW
{

  class Level2 : public LevelScreenCreator
  {
    DECLARE_SCREEN_CREATOR(Level2)

    public:
      static void create();

    private:
      typedef LevelScreenCreator Inherited;
  };

}