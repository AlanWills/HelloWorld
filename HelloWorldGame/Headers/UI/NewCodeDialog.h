#pragma once

#include "Memory/Handle.h"
#include "Objects/GameObject.h"
#include "Screens/Creation/ScreenCreator.h"

#include <string>


namespace HW
{
  class LevelScreenCreator;

  namespace UI
  {
    class NewCodeDialog : CelesteEngine::ScreenCreator
    {
      DECLARE_SCREEN_CREATOR(NewCodeDialog)

      public:
        static void showModal(const std::string& text);

      private:
        typedef CelesteEngine::ScreenCreator Inherited;
    };
  }
}