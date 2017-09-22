#pragma once

#include "Objects/Script.h"


namespace HW
{
  namespace Input
  {
    class SplashScreenLogoSkipper : public CelesteEngine::Script
    {
      DECLARE_SCRIPT(SplashScreenLogoSkipper)

      protected:
        void onUpdate(GLfloat elapsedGameTime) override;

      private:
        typedef CelesteEngine::Script Inherited;
    };
  }
}