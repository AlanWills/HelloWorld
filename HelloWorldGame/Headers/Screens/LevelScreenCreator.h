#pragma once

#include "Screens/ScreenCreator.h"


namespace HW
{

class LevelScreenCreator : public CelesteEngine::ScreenCreator
{
  public:
    LevelScreenCreator(const LevelScreenCreator&) = delete;
    LevelScreenCreator& operator=(const LevelScreenCreator&) = delete;

  protected:
    LevelScreenCreator(const Handle<Screen>& screen, const std::string& name = "LevelScreen");
    
    Handle<GameObject> createPlayer(const glm::vec2& size, const glm::vec3& translation);
    Handle<GameObject> createTerminalUI();

  private:
    typedef ScreenCreator Inherited;
    
};

}