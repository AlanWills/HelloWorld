#pragma once


#include "Objects/Script.h"


namespace HW
{
  namespace Physics
  {
    class PlayerObstacle : public CelesteEngine::Script
    {
      DECLARE_SCRIPT(PlayerObstacle)

      public:
        const glm::vec2& getDimensions() const { return m_dimensions; }
        void setDimensions(const glm::vec2& dimensions) { m_dimensions = dimensions; }

      protected:
        void onSetGameObject(const Handle<GameObject>& gameObject);
        void onUpdate(GLfloat elapsedGameTime) override;
        void onDeath() override;

      private:
        typedef CelesteEngine::Script Inherited;

        Handle<GameObject> m_player;
        glm::vec2 m_dimensions;
    };
  }
}