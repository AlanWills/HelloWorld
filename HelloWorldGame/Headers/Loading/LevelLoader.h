#pragma once

#include "Objects/Script.h"
#include "Objects/GameObject.h"
#include "UI/ProgressBar.h"


namespace HW
{
  
class LevelLoader : public CelesteEngine::Script 
{
  DECLARE_SCRIPT(LevelLoader)

  protected:
    void onUpdate(GLfloat elapsedGameTime) override
    {
      CelesteEngine::Script::onUpdate(elapsedGameTime);

      m_total += elapsedGameTime;
      getGameObject()->findComponent<UI::ProgressBar>()->setProgress(m_total);
    }

  private:
    float m_total;
};

}