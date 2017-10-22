#include "stdafx.h"

#include "Physics/PlayerMoveable.h"
#include "Input/InputManager.h"
#include "Objects/GameObject.h"
#include "Screens/Screen.h"

using namespace CelesteEngine::Input;
using namespace CelesteEngine::Physics;


namespace HW
{
  namespace Physics
  {
    REGISTER_SCRIPT(PlayerMoveable, 10)

    //------------------------------------------------------------------------------------------------
    PlayerMoveable::PlayerMoveable() :
      m_canBePickedUp(false),
      m_oldParent()
    {
    }

    //------------------------------------------------------------------------------------------------
    PlayerMoveable::~PlayerMoveable()
    {
    }

    //------------------------------------------------------------------------------------------------
    void PlayerMoveable::onHandleInput()
    {
      Inherited::onHandleInput();

      if (m_canBePickedUp)
      {
        const Handle<GameObject>& player = getGameObject()->getOwnerScreen()->findGameObjectWithName("Player");
        if (isKeyDown(GLFW_KEY_LEFT_SHIFT) || isKeyDown(GLFW_KEY_RIGHT_SHIFT))
        {
          if (getTransform()->getParent() != player->getTransform())
          {
            const glm::vec3& newTranslation = getTransform()->getWorldTranslation() - player->getTransform()->getWorldTranslation();
            m_oldParent = getTransform()->getParent();
            getTransform()->setParent(player->getTransform());
            getTransform()->setTranslation(newTranslation);
          }
        }
        else if (getTransform()->getParent() == player->getTransform())
        {
          ASSERT(!m_oldParent.is_null());

          const glm::vec3& newTranslation = getTransform()->getWorldTranslation();
          getTransform()->setParent(m_oldParent);
          getTransform()->setWorldTranslation(newTranslation);
        }
      }
    }

    //------------------------------------------------------------------------------------------------
    void PlayerMoveable::onCollisionEnter(const ConstHandle<Collider>& collider)
    {
      Inherited::onCollisionEnter(collider);

      // We can pick up if we can already pick up
      // Or we can't, but the collided object is the player
      m_canBePickedUp = m_canBePickedUp || (collider->getGameObject()->getName() == std::string("Player"));
    }

    //------------------------------------------------------------------------------------------------
    void PlayerMoveable::onCollisionExit(const ConstHandle<Collider>& collider)
    {
      Inherited::onCollisionExit(collider);

      // We can only pick up if we could before and the object leaving is not the player
      m_canBePickedUp = m_canBePickedUp && (collider->getGameObject()->getName() != std::string("Player"));
    }

    //------------------------------------------------------------------------------------------------
    void PlayerMoveable::onDeath()
    {
      Inherited::onDeath();

      m_canBePickedUp = false;
      m_oldParent.reset();
    }
  }
}