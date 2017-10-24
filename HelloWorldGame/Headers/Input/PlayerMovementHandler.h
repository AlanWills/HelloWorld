#pragma once

#include "Input/KeyboardTranslationScript.h"


namespace HW
{
  namespace Input
  {
    class PlayerMovementHandler : public CelesteEngine::Input::KeyboardTranslationScript
    {
      DECLARE_SCRIPT(PlayerMovementHandler)

      public:
        //------------------------------------------------------------------------------------------------
        static Handle<PlayerMovementHandler> create(
          const Handle<GameObject>& gameObject,
          int moveLeftKey,
          int moveRightKey,
          int moveUpKey,
          int moveDownKey,
          float panSpeed);

      protected:
        void onCollision(const ConstHandle<Physics::Collider>& collider) override;

      private:
        typedef CelesteEngine::Input::KeyboardTranslationScript Inherited;
    };
  }
}