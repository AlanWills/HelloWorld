#pragma once

#include "Screens/ScreenCreator.h"


namespace HW
{

class LevelScreen : public CelesteEngine::ScreenCreator
{
  public:
    LevelScreen(const Handle<Screen>& screen, const std::string& name = "");

  protected:
    Handle<GameObject> createPlayer(const glm::vec2& size, const glm::vec3& translation);
    Handle<GameObject> createTerminal(const glm::vec2& size, const glm::vec3& translation);

  private:
    typedef ScreenCreator Inherited;
};

}