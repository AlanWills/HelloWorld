#include "stdafx.h"

#include "Input/TerminalInputHandler.h"
#include "UI/TextBox.h"
#include "Rendering/TextRenderer.h"
#include "Objects/GameObject.h"
#include "Screens/Screen.h"
#include "Input/InputManager.h"
#include "Compiler/Compiler.h"

using namespace CelesteEngine;
using namespace CelesteEngine::UI;
using namespace CelesteEngine::Input;


namespace HW
{
  namespace Input
  {
    REGISTER_SCRIPT(TerminalInputHandler, 2)

    //------------------------------------------------------------------------------------------------
    TerminalInputHandler::TerminalInputHandler() :
      m_terminalTextBox(),
      m_eventName(0)
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
      m_eventName = getInputManager()->getKeyboard().getKeyDownEvent().subscribe(std::bind(&TerminalInputHandler::onKeyDown, *this, std::placeholders::_1));
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
    }

    //------------------------------------------------------------------------------------------------
    void TerminalInputHandler::onKeyDown(int key)
    {
      if (key == GLFW_KEY_ENTER)
      {
        // Textbox will have added an empty line so we have to get the second to last line (hence -2)
        std::vector<std::string> output;
        Compiler::run(m_terminalTextBox->getTextRenderer()->getLine(m_terminalTextBox->getTextRenderer()->getLineCount() - 2), output);

        m_terminalTextBox->getTextRenderer()->addLines(output);
        m_terminalTextBox->getTextRenderer()->addLine();
        m_terminalTextBox->getTextRenderer()->addLine("> ");
        m_terminalTextBox->setLineIndex(m_terminalTextBox->getTextRenderer()->getLineCount() - 1);
        m_terminalTextBox->setLetterIndex(2);
      }
    }

    //------------------------------------------------------------------------------------------------
    void TerminalInputHandler::onDeath()
    {
      Inherited::onDeath();

      m_terminalTextBox.reset();
      getInputManager()->getKeyboard().getKeyDownEvent().unsubscribe(m_eventName);
    }
  }
}