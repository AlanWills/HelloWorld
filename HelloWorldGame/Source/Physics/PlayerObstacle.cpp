#include "stdafx.h"

#include "Physics/PlayerObstacle.h"
#include "Objects/GameObject.h"
#include "Screens/Screen.h"
#include "Rendering/Renderer.h"
#include "Input/KeyboardRigidBody2DController.h"


namespace HW
{
  namespace Physics
  {
    REGISTER_SCRIPT(PlayerObstacle, 10)

    //------------------------------------------------------------------------------------------------
    PlayerObstacle::PlayerObstacle() :
      m_player(),
      m_dimensions()
    {
    }

    //------------------------------------------------------------------------------------------------
    PlayerObstacle::~PlayerObstacle()
    {
    }

    //------------------------------------------------------------------------------------------------
    void PlayerObstacle::onSetGameObject(const Handle<GameObject>& gameObject)
    {
      Inherited::onSetGameObject(gameObject);

      m_player = gameObject->getOwnerScreen()->findGameObjectWithName("Player");

      if (getGameObject()->hasComponent<Renderer>())
      {
        m_dimensions = getGameObject()->findComponent<Renderer>()->getScaledDimensions();
      }
    }

    //------------------------------------------------------------------------------------------------
    void PlayerObstacle::onUpdate(GLfloat elapsedGameTime)
    {
      Inherited::onUpdate(elapsedGameTime);

      if (m_dimensions == glm::vec2())
      {
        return;
      }

      const glm::vec3& playerTranslation = m_player->getTransform()->getTranslation();
      const glm::vec3& translation = getTransform()->getTranslation();
      float playerHalfWidth = m_player->findComponent<Renderer>()->getScaledDimensions().x * 0.5f;
      float halfWidth = m_dimensions.x * 0.5f;

      if (translation.x < playerTranslation.x)
      {
        // Coming in from the right
        if ((translation.x + halfWidth) >= (playerTranslation.x - playerHalfWidth))
        {
          // Player has collided
          m_player->getTransform()->setTranslation(translation.x + halfWidth + playerHalfWidth, playerTranslation.y, playerTranslation.z);
          m_player->findComponent<Input::KeyboardRigidBody2DController>()->setDecreaseXLinearVelocityKey(-1);
        }
        else
        {
          m_player->findComponent<Input::KeyboardRigidBody2DController>()->setDecreaseXLinearVelocityKey(GLFW_KEY_A);
        }
      }
      else
      {
        // Coming in from the left
        if ((translation.x - halfWidth) <= (playerTranslation.x + playerHalfWidth))
        {
          // Player has collided
          m_player->getTransform()->setTranslation(translation.x - halfWidth - playerHalfWidth, playerTranslation.y, playerTranslation.z);
          m_player->findComponent<Input::KeyboardRigidBody2DController>()->setIncreaseXLinearVelocityKey(-1);
        }
        else
        {
          m_player->findComponent<Input::KeyboardRigidBody2DController>()->setIncreaseXLinearVelocityKey(GLFW_KEY_D);
        }
      }
    }

    //------------------------------------------------------------------------------------------------
    void PlayerObstacle::onDeath()
    {
      Inherited::onDeath();

      if (!m_player.is_null() && m_player->hasComponent<Input::KeyboardRigidBody2DController>())
      {
        m_player->findComponent<Input::KeyboardRigidBody2DController>()->setDecreaseXLinearVelocityKey(GLFW_KEY_A);
        m_player->findComponent<Input::KeyboardRigidBody2DController>()->setIncreaseXLinearVelocityKey(GLFW_KEY_D);
      }

      m_player.reset();
      m_dimensions = glm::vec2();
    }
  }
}