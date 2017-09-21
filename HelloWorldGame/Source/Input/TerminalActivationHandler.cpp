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
      m_deactivationKey(-1)
    {
    }

    //------------------------------------------------------------------------------------------------
    TerminalActivationHandler::~TerminalActivationHandler()
    {
    }

    //------------------------------------------------------------------------------------------------
    void TerminalActivationHandler::onHandleInput()
    {
      Inherited::onHandleInput();

      const Handle<GameObject>& gameObject = getGameObject();
      if (gameObject.is_null())
      {
        ASSERT_FAIL();
        return;
      }

      if (isKeyDown(m_activationKey))
      {
        gameObject->setActive(true);
        gameObject->setShouldRender(true);

        const Handle<GameObject>& terminalTextBox = gameObject->getOwnerScreen()->findGameObjectWithName("TerminalTextBox");
        terminalTextBox->setActive(true);
        terminalTextBox->setShouldRender(true);

        const Handle<GameObject>& terminalOutput = gameObject->getOwnerScreen()->findGameObjectWithName("TerminalOutput");
        terminalOutput->setActive(true);
        terminalOutput->setShouldRender(true);
      }
      else if (isKeyDown(m_deactivationKey))
      {
        gameObject->setActive(false);
        gameObject->setShouldRender(false);

        const Handle<GameObject>& terminalTextBox = gameObject->getOwnerScreen()->findGameObjectWithName("TerminalTextBox");
        terminalTextBox->setActive(false);
        terminalTextBox->setShouldRender(false);

        const Handle<GameObject>& terminalOutput = gameObject->getOwnerScreen()->findGameObjectWithName("TerminalOutput");
        terminalOutput->setActive(false);
        terminalOutput->setShouldRender(false);
      }
    }

    //------------------------------------------------------------------------------------------------
    void TerminalActivationHandler::onDeath()
    {
      Inherited::onDeath();

      m_activationKey = -1;
      m_deactivationKey = -1;
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