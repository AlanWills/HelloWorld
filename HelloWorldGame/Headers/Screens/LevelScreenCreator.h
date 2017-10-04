#pragma once

#include "Screens/ScreenCreator.h"


namespace HW
{

class LevelScreenCreator : public CelesteEngine::ScreenCreator
{
  DECLARE_BASE_SCREEN_CREATOR(LevelScreenCreator)

  protected:
    Handle<GameObject> createPlayer(const glm::vec2& size, const glm::vec3& translation);
    Handle<GameObject> createTerminalUI();

  private:
    typedef ScreenCreator Inherited;
    
};

}