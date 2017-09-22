#include "stdafx.h"

#include "Input/SplashScreenLogoSkipper.h"
#include "Input/InputManager.h"
#include "Objects/GameObject.h"
#include "ObjectFX/LimitedLifeTime.h"

using namespace CelesteEngine;
using namespace CelesteEngine::Input;


namespace HW
{
  namespace Input
  {
    REGISTER_SCRIPT(SplashScreenLogoSkipper, 3)

    //------------------------------------------------------------------------------------------------
    SplashScreenLogoSkipper::SplashScreenLogoSkipper()
    {
    }

    //------------------------------------------------------------------------------------------------
    SplashScreenLogoSkipper::~SplashScreenLogoSkipper()
    {
    }

    //------------------------------------------------------------------------------------------------
    void SplashScreenLogoSkipper::onUpdate(GLfloat elapsedGameTime)
    {
      Inherited::onUpdate(elapsedGameTime);

      if (isKeyPressed(GLFW_KEY_ESCAPE))
      {
        getGameObject()->findComponent<LimitedLifeTime>()->getOnDeathEvent().invoke(getGameObject());
        getGameObject()->die();
        getKeyboard().flush();
      }
    }
  }
}