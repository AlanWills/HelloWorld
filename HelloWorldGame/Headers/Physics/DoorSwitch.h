#pragma once

#include "Objects/Script.h"
#include "Physics/RectangleCollider.h"

using namespace CelesteEngine::Physics;


namespace HW
{
  namespace Physics
  {
    class DoorSwitch : public CelesteEngine::Script
    {
      DECLARE_SCRIPT(DoorSwitch)

      public:
        const Handle<GameObject>& getDoor() const { return m_door; }
        void setDoor(const Handle<GameObject>& door) { m_door = door; }

        const glm::vec3& getShutPosition() const { return m_shutPosition; }
        void setShutPosition(const glm::vec3& shutPosition) { m_shutPosition = shutPosition; }

        const glm::vec3& getOpenPosition() const { return m_openPosition; }
        void setOpenPosition(const glm::vec3& openPosition) { m_openPosition = openPosition; }

      protected:
        void onSetGameObject(const Handle<GameObject>& gameObject) override;
        void onUpdate(GLfloat elapsedGameTime) override;
        void onDeath() override;

      private:
        typedef CelesteEngine::Script Inherited;

        Handle<RectangleCollider> m_collider;
        Handle<GameObject> m_door;

        glm::vec3 m_shutPosition;
        glm::vec3 m_openPosition;
    };
  }
}