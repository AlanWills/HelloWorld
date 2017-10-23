#include "stdafx.h"

#include "Physics/DoorSwitch.h"
#include "Objects/GameObject.h"
#include "Screens/Screen.h"
#include "Animation/Animators/MoveToPositionAnimator.h"
#include "Rendering/SpriteRenderer.h"

using namespace CelesteEngine::Animators;
using namespace CelesteEngine::Rendering;
using namespace CelesteEngine::Physics;


namespace HW
{
  namespace Physics
  {
    REGISTER_SCRIPT(DoorSwitch, 3)

    //------------------------------------------------------------------------------------------------
    DoorSwitch::DoorSwitch() :
      m_door(),
      m_draggable(),
      m_shutPosition(),
      m_openPosition(),
      m_opening(false)
    {
    }

    //------------------------------------------------------------------------------------------------
    DoorSwitch::~DoorSwitch()
    {
    }

    //------------------------------------------------------------------------------------------------
    void DoorSwitch::onCollisionEnter(const ConstHandle<Collider>& collider)
    {
      Inherited::onCollisionEnter(collider);

      tryOpenDoor();
    }

    //------------------------------------------------------------------------------------------------
    void DoorSwitch::onTriggerEnter(const ConstHandle<Collider>& collider)
    {
      Inherited::onTriggerEnter(collider);

      tryOpenDoor();
    }

    //------------------------------------------------------------------------------------------------
    void DoorSwitch::onCollisionExit(const ConstHandle<Collider>& collider)
    {
      Inherited::onCollisionEnter(collider);

      tryCloseDoor();
    }

    //------------------------------------------------------------------------------------------------
    void DoorSwitch::onTriggerExit(const ConstHandle<Collider>& collider)
    {
      Inherited::onTriggerExit(collider);

      tryCloseDoor();
    }

    //------------------------------------------------------------------------------------------------
    void DoorSwitch::tryOpenDoor()
    {
      if (!m_opening)
      {
        const Handle<MoveToPositionAnimator>& animator = m_door->findComponent<MoveToPositionAnimator>();
        animator->setTargetPosition(m_openPosition);
        // Scale time based on how much of the animation has already been completed
        animator->setTime(glm::distance(m_door->getTransform()->getTranslation(), m_openPosition) / glm::distance(m_shutPosition, m_openPosition));
        animator->setActive(true);
        m_opening = true;
      }
    }

    //------------------------------------------------------------------------------------------------
    void DoorSwitch::tryCloseDoor()
    {
      if (m_opening && !getGameObject()->findComponent<RectangleCollider>()->intersects(m_draggable->findComponent<RectangleCollider>()))
      {
        const Handle<MoveToPositionAnimator>& animator = m_door->findComponent<MoveToPositionAnimator>();
        animator->setTargetPosition(m_shutPosition);
        // Scale time based on how much of the animation has already been completed
        animator->setTime(glm::distance(m_door->getTransform()->getTranslation(), m_shutPosition) / glm::distance(m_shutPosition, m_openPosition));
        animator->setActive(true);
        m_opening = false;
      }
    }

    //------------------------------------------------------------------------------------------------
    void DoorSwitch::onDeath()
    {
      Inherited::onDeath();
    }
  }
}