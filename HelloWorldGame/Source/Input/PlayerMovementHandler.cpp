#include "stdafx.h"

#include "Input/PlayerMovementHandler.h"
#include "Objects/GameObject.h"
#include "Physics/Collider.h"

using namespace CelesteEngine::Physics;


namespace HW
{
  namespace Input
  {
    REGISTER_SCRIPT(PlayerMovementHandler, 2)

    //------------------------------------------------------------------------------------------------
    PlayerMovementHandler::PlayerMovementHandler()
    {
    }

    //------------------------------------------------------------------------------------------------
    PlayerMovementHandler::~PlayerMovementHandler()
    {
    }

    //------------------------------------------------------------------------------------------------
    void PlayerMovementHandler::onCollision(const ConstHandle<Collider>& collider)
    {
      Inherited::onCollision(collider);

      if (collider->getGameObject()->getTag() == std::string("PlayerObstacle"))
      {
        glm::vec2 newVelocity = getDirectionVector();

        if (collider->centre().x < getGameObject()->findComponent<Collider>()->centre().x)
        {
          // Body has moved left into a collider
          newVelocity.x = std::max(newVelocity.x, 0.0f);
        }
        else
        {
          // Body has moved right into a collider
          newVelocity.x = std::min(newVelocity.x, 0.0f);
        }

        setDirectionVector(newVelocity);
      }
    }

    //------------------------------------------------------------------------------------------------
    Handle<PlayerMovementHandler> PlayerMovementHandler::create(
      const Handle<GameObject>& gameObject,
      int moveLeftKey,
      int moveRightKey,
      int moveUpKey,
      int moveDownKey,
      float panSpeed)
    {
      if (gameObject.is_null())
      {
        return Handle<PlayerMovementHandler>();
      }

      const Handle<PlayerMovementHandler>& movement = gameObject->addComponent<PlayerMovementHandler>();
      movement->setMoveLeftKey(moveLeftKey);
      movement->setMoveRightKey(moveRightKey);
      movement->setMoveUpKey(moveUpKey);
      movement->setMoveDownKey(moveDownKey);
      movement->setPanSpeed(panSpeed);

      return movement;
    }
  }
}