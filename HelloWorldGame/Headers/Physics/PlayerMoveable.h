#pragma once

#include "Objects/Script.h"


namespace HW
{
  namespace Physics
  {
    class PlayerMoveable : public CelesteEngine::Script
    {
      DECLARE_SCRIPT(PlayerMoveable)

      protected:
        void onSetGameObject(const Handle<GameObject>& gameObject) override;
        void onHandleInput() override;
        void onUpdate(GLfloat elapsedGameTime) override;
        void onDeath() override;

      private:
        typedef CelesteEngine::Script Inherited;

        ConstHandle<GameObject> m_player;
        bool m_moving;
        glm::vec2 m_offset;
    };
  }
}