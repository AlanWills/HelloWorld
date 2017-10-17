#include "stdafx.h"

#include "Physics/PlayerMoveable.h"
#include "Input/InputManager.h"
#include "Objects/GameObject.h"
#include "Physics/RectangleCollider.h"
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
      m_player(),
      m_moving(false),
      m_offset()
    {
    }

    //------------------------------------------------------------------------------------------------
    PlayerMoveable::~PlayerMoveable()
    {
    }

    //------------------------------------------------------------------------------------------------
    void PlayerMoveable::onSetGameObject(const Handle<GameObject>& gameObject)
    {
      Inherited::onSetGameObject(gameObject);

      m_player = gameObject->getOwnerScreen()->findGameObjectWithName("Player").as_const();
    }

    //------------------------------------------------------------------------------------------------
    void PlayerMoveable::onHandleInput()
    {
      Inherited::onHandleInput();

      // Check collision of player and this objects colliders
      // And then if shift is down, we set moving to true
      if (m_moving)
      {
        m_moving = isKeyDown(GLFW_KEY_LEFT_SHIFT) || isKeyDown(GLFW_KEY_RIGHT_SHIFT);
        if (!m_moving)
        {
          m_offset = glm::vec2();
          getGameObject()->findComponent<Collider>()->setActive(true);
        }
      }
      else if (m_player->findComponent<Collider>()->intersects(getGameObject()->findComponent<Collider>()))
      {
        m_moving = isKeyDown(GLFW_KEY_LEFT_SHIFT) || isKeyDown(GLFW_KEY_RIGHT_SHIFT);
        if (m_moving)
        {
          glm::vec3 diff = getTransform()->getWorldTranslation() - m_player->getTransform()->getWorldTranslation();
          m_offset.x = diff.x;
          m_offset.y = diff.y;

          getGameObject()->findComponent<Collider>()->setActive(false);
        }
      }
    }

    //------------------------------------------------------------------------------------------------
    void PlayerMoveable::onUpdate(GLfloat elapsedGameTime)
    {
      Inherited::onUpdate(elapsedGameTime);

      // Move object accordingly
      if (m_moving)
      {
        getTransform()->setWorldTranslation(m_player->getTransform()->getWorldTranslation() + glm::vec3(m_offset, 0));
      }
    }

    //------------------------------------------------------------------------------------------------
    void PlayerMoveable::onDeath()
    {
      Inherited::onDeath();

      m_player.reset();
      m_moving = false;
      m_offset = glm::vec2();
    }
  }
}