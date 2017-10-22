#pragma once

#include "Objects/Script.h"
#include "Physics/Collider.h"


namespace HW
{
  namespace Physics
  {
    class PlayerMoveable : public CelesteEngine::Script
    {
      DECLARE_SCRIPT(PlayerMoveable)

      protected:
        void onHandleInput() override;
        void onCollisionEnter(const ConstHandle<CelesteEngine::Physics::Collider>& collider) override;
        void onCollisionExit(const ConstHandle<CelesteEngine::Physics::Collider>& collider) override;
        void onDeath() override;

      private:
        typedef CelesteEngine::Script Inherited;

        bool m_canBePickedUp;

        Handle<Transform> m_oldParent;
    };
  }
}