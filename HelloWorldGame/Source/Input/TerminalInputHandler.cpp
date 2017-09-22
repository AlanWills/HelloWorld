#include "stdafx.h"

#include "Input/TerminalInputHandler.h"
#include "UI/TextBox.h"
#include "Rendering/TextRenderer.h"
#include "Objects/GameObject.h"
#include "Screens/Screen.h"

using namespace CelesteEngine;
using namespace CelesteEngine::UI;


namespace HW
{
  namespace Input
  {
    REGISTER_SCRIPT(TerminalInputHandler, 1)

    //------------------------------------------------------------------------------------------------
    TerminalInputHandler::TerminalInputHandler() :
      m_terminalTextBox(),
      m_terminalOutput()
    {
    }

    //------------------------------------------------------------------------------------------------
    TerminalInputHandler::~TerminalInputHandler()
    {
    }

    //------------------------------------------------------------------------------------------------
    void TerminalInputHandler::onSetGameObject(const Handle<GameObject>& gameObject)
    {
      Inherited::onSetGameObject(gameObject);

      m_terminalTextBox = gameObject->findComponent<TextBox>();
      m_terminalOutput = gameObject->getOwnerScreen()->findGameObjectWithName("TerminalOutput")->findComponent<TextRenderer>();
    }

    //------------------------------------------------------------------------------------------------
    void TerminalInputHandler::setActive(bool isActive)
    {
      Inherited::setActive(isActive);

      if (isActive && !m_terminalTextBox.is_null())
      {
        m_terminalTextBox->getTextRenderer()->resetLines("> ");
        m_terminalTextBox->setLineIndex(0);
        m_terminalTextBox->setLetterIndex(2);
      }

      if (isActive && !m_terminalOutput.is_null())
      {
        m_terminalOutput->resetLines();
      }
    }

    //------------------------------------------------------------------------------------------------
    void TerminalInputHandler::onDeath()
    {
      Inherited::onDeath();

      m_terminalTextBox.reset();
      m_terminalOutput.reset();
    }
  }
}