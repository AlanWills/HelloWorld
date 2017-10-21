#include "stdafx.h"

#include "Input/TerminalInputHandler.h"
#include "UI/TextBox.h"
#include "Rendering/TextRenderer.h"
#include "Rendering/SpriteRenderer.h"
#include "Objects/GameObject.h"
#include "Screens/Screen.h"
#include "Input/InputManager.h"
#include "Compiler/Compiler.h"
#include "GraphicalFX/OpacityLerper.h"

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
      m_textRenderer(),
      m_caret(),
      m_textInputtedEventHandle(0),
      m_keyDownEventHandle(0),
      m_letterIndex(0)
    {
    }

    //------------------------------------------------------------------------------------------------
    TerminalInputHandler::~TerminalInputHandler()
    {
    }

    //------------------------------------------------------------------------------------------------
    void TerminalInputHandler::onInitialize()
    {
      Inherited::onInitialize();

      m_textInputtedEventHandle = getKeyboard().getTextInputtedEvent().subscribe(std::bind(&TerminalInputHandler::onTextInputtedCallback, this, std::placeholders::_1));
      m_keyDownEventHandle = getKeyboard().getKeyDownEvent().subscribe(std::bind(&TerminalInputHandler::onKeyPressedCallback, this, std::placeholders::_1));
    }

    //------------------------------------------------------------------------------------------------
    void TerminalInputHandler::onSetGameObject(const Handle<GameObject>& gameObject)
    {
      Inherited::onSetGameObject(gameObject);

      m_textRenderer = gameObject->findComponent<TextRenderer>();
      if (m_textRenderer.is_null() || gameObject->getOwnerScreen().is_null())
      {
        ASSERT_FAIL();
        return;
      }

      m_caret = getGameObject()->allocateGameObjectInSameLayer(getTransform());
      m_caret->getTransform()->setTranslation(0, 0, 0.1f);
      SpriteRenderer::create(m_caret, Path("Sprites", "UI", "Rectangle.png"), glm::vec2(2, m_textRenderer->getFontHeight()));

      LerpData data;
      data.m_lerpUpTime = 0;
      data.m_lerpDownTime = 0;
      data.m_maxOpacityWaitTime = 0.5f;
      data.m_minOpacityWaitTime = 0.5f;
      OpacityLerper::create(m_caret, data);

      setLetterIndex(2);
    }

    //------------------------------------------------------------------------------------------------
    void TerminalInputHandler::setActive(bool isActive)
    {
      Inherited::setActive(isActive);

      if (isActive && !m_textRenderer.is_null())
      {
        m_textRenderer->resetLines("> ");
        setLetterIndex(2);
      }
    }

    //------------------------------------------------------------------------------------------------
    void TerminalInputHandler::onTextInputtedCallback(char character)
    {
      if (isActive() && !m_textRenderer.is_null())
      {
        m_textRenderer->addLetter(0, m_letterIndex, character);
        setLetterIndex(m_letterIndex + 1);
      }
    }

    //------------------------------------------------------------------------------------------------
    void TerminalInputHandler::onKeyPressedCallback(int keyPressed)
    {
      if (isActive() && !m_textRenderer.is_null())
      {
        switch (keyPressed)
        {
          case GLFW_KEY_ENTER:
          {
            std::vector<std::string> output;
            Compiler::run(m_textRenderer->getLine(0).substr(2));

            m_textRenderer->resetLines("> ");
            setLetterIndex(2);
          }

          case GLFW_KEY_BACKSPACE:
          {
            if (m_letterIndex > 2)
            {
              m_textRenderer->removeLetter(0, m_letterIndex - 1);
              setLetterIndex(m_letterIndex - 1);
            }
            break;
          }

          case GLFW_KEY_DELETE:
          {
            if (m_letterIndex > 1 && m_letterIndex < m_textRenderer->getLineLength(0))
            {
              m_textRenderer->removeLetter(0, m_letterIndex);
            }
            break;
          }

          case GLFW_KEY_LEFT:
          {
            if (m_letterIndex > 2)
            {
              setLetterIndex(m_letterIndex - 1);
            }
            break;
          }

          case GLFW_KEY_RIGHT:
          {
            if (m_letterIndex < (m_textRenderer->getLineLength(0)))
            {
              setLetterIndex(m_letterIndex + 1);
            }
            break;
          }

          case GLFW_KEY_HOME:
          {
            setLetterIndex(0);
            break;
          }

          case GLFW_KEY_END:
          {
            setLetterIndex(m_textRenderer->getLineLength(0));
            break;
          }
        }
      }
    }

    //------------------------------------------------------------------------------------------------
    void TerminalInputHandler::onDeath()
    {
      Inherited::onDeath();

      getKeyboard().getTextInputtedEvent().unsubscribe(m_textInputtedEventHandle);
      getKeyboard().getKeyDownEvent().unsubscribe(m_keyDownEventHandle);

      if (!m_caret.is_null())
      {
        m_caret->die();
        m_caret.reset();
      }

      m_textInputtedEventHandle = 0;
      m_keyDownEventHandle = 0;
      m_textRenderer.reset();
      m_letterIndex = 0;
    }

    //------------------------------------------------------------------------------------------------
    void TerminalInputHandler::setLetterIndex(size_t newIndex)
    {
      if (newIndex < 2)
      {
        // Cannot set index past the '> ' in the terminal line
        ASSERT_FAIL();
        return;
      }

      m_letterIndex = newIndex;

      if (!m_caret.is_null())
      {
        m_caret->getTransform()->setTranslation(m_textRenderer->getLetterOffset(0, m_letterIndex) - glm::vec2(0, 0.5f * m_textRenderer->getFontHeight()));
      }
    }
  }
}