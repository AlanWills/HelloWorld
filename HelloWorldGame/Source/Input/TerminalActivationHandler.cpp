#include "stdafx.h"

#include "Input/TerminalActivationHandler.h"
#include "Input/InputManager.h"
#include "Objects/GameObject.h"
#include "Screens/Screen.h"

using namespace CelesteEngine::Input;


namespace HW
{
  namespace Input
  {
    REGISTER_SCRIPT(TerminalActivationHandler, 1)

    //------------------------------------------------------------------------------------------------
    TerminalActivationHandler::TerminalActivationHandler() :
      m_activationKey(-1),
      m_deactivationKey(-1),
      m_levelRoot()
    {
    }

    //------------------------------------------------------------------------------------------------
    TerminalActivationHandler::~TerminalActivationHandler()
    {
    }

    //------------------------------------------------------------------------------------------------
    void TerminalActivationHandler::onSetGameObject(const Handle<GameObject>& gameObject)
    {
      Inherited::onSetGameObject(gameObject);

      m_levelRoot = gameObject->getOwnerScreen()->findGameObjectWithName("LevelRoot");
    }

    //------------------------------------------------------------------------------------------------
    void TerminalActivationHandler::onHandleInput()
    {
      Inherited::onHandleInput();

      const Handle<GameObject>& gameObject = getGameObject();
      if (gameObject.is_null() || m_levelRoot.is_null())
      {
        ASSERT_FAIL();
        return;
      }

      if (m_levelRoot->isActive() && isKeyDown(m_activationKey))
      {
        m_levelRoot->setActive(false);

        const Handle<Transform>& transform = gameObject->getTransform();
        for (size_t i = 0, n = transform->getChildCount(); i < n; ++i)
        {
          const Handle<GameObject>& child = transform->getChildGameObject(i);
          child->setActive(true);
          child->setShouldRender(true);
        }
      }
      else if (!m_levelRoot->isActive() && isKeyDown(m_deactivationKey))
      {
        m_levelRoot->setActive(true);

        const Handle<Transform>& transform = gameObject->getTransform();
        for (size_t i = 0, n = transform->getChildCount(); i < n; ++i)
        {
          const Handle<GameObject>& child = transform->getChildGameObject(i);
          child->setActive(false);
          child->setShouldRender(false);
        }
      }
    }

    //------------------------------------------------------------------------------------------------
    void TerminalActivationHandler::onDeath()
    {
      Inherited::onDeath();

      m_activationKey = -1;
      m_deactivationKey = -1;
      m_levelRoot.reset();
    }

    //------------------------------------------------------------------------------------------------
    Handle<TerminalActivationHandler> TerminalActivationHandler::create(
      const Handle<GameObject>& gameObject,
      int activationKey,
      int deactivationKey)
    {
      if (gameObject.is_null())
      {
        ASSERT_FAIL();
        return Handle<TerminalActivationHandler>();
      }

      const Handle<TerminalActivationHandler>& handler = gameObject->addComponent<TerminalActivationHandler>();
      handler->setActivationKey(activationKey);
      handler->setDeactivationKey(deactivationKey);

      return handler;
    }
  }
}