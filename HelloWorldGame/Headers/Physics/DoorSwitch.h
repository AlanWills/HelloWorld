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

        const Handle<GameObject>& getDraggable() const { return m_draggable; }
        void setDraggable(const Handle<GameObject>& draggable) { m_draggable = draggable; }

        const glm::vec3& getShutPosition() const { return m_shutPosition; }
        void setShutPosition(const glm::vec3& shutPosition) { m_shutPosition = shutPosition; }

        const glm::vec3& getOpenPosition() const { return m_openPosition; }
        void setOpenPosition(const glm::vec3& openPosition) { m_openPosition = openPosition; }

      protected:
        void onCollisionEnter(const ConstHandle<CelesteEngine::Physics::Collider>& collider) override;
        void onTriggerEnter(const ConstHandle<CelesteEngine::Physics::Collider>& collider) override;
        void onCollisionExit(const ConstHandle<CelesteEngine::Physics::Collider>& collider) override;
        void onTriggerExit(const ConstHandle<CelesteEngine::Physics::Collider>& collider) override;
        void onDeath() override;

      private:
        typedef CelesteEngine::Script Inherited;

        void tryOpenDoor();
        void tryCloseDoor();

        Handle<GameObject> m_door;
        Handle<GameObject> m_draggable;

        glm::vec3 m_shutPosition;
        glm::vec3 m_openPosition;

        bool m_opening;
    };
  }
}