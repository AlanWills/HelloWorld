#include "stdafx.h"

#include "Physics/DoorSwitch.h"
#include "Objects/GameObject.h"
#include "Screens/Screen.h"
#include "Animation/Animators/MoveToPositionAnimator.h"
#include "Rendering/SpriteRenderer.h"

using namespace CelesteEngine::Animators;
using namespace CelesteEngine::Rendering;


namespace HW
{
  namespace Physics
  {
    REGISTER_SCRIPT(DoorSwitch, 3)

    //------------------------------------------------------------------------------------------------
    DoorSwitch::DoorSwitch() :
      m_collider(),
      m_door(),
      m_shutPosition(),
      m_openPosition()
    {
    }

    //------------------------------------------------------------------------------------------------
    DoorSwitch::~DoorSwitch()
    {
    }

    //------------------------------------------------------------------------------------------------
    void DoorSwitch::onSetGameObject(const Handle<GameObject>& gameObject)
    {
      Inherited::onSetGameObject(gameObject);

      m_collider = gameObject->findComponent<RectangleCollider>();
    }

    //------------------------------------------------------------------------------------------------
    void DoorSwitch::onUpdate(GLfloat elapsedGameTime)
    {
      Inherited::onUpdate(elapsedGameTime);

      // Need to store both start and end positions of door as variables
      // Then can manipulate both x and y if necessary

      const Handle<GameObject>& player = getGameObject()->getOwnerScreen()->findGameObjectWithName("Player");
      const Handle<MoveToPositionAnimator>& animator = m_door->findComponent<MoveToPositionAnimator>();
      animator->setTargetPosition(m_collider->intersects(player->findComponent<RectangleCollider>()) ? m_openPosition : m_shutPosition);
    }

    //------------------------------------------------------------------------------------------------
    void DoorSwitch::onDeath()
    {
      Inherited::onDeath();
    }
  }
}